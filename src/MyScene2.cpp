//
//  MyScene2.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 8/12/14.
//
//

#include "MyScene2.h"
void MyScene2::setup()
{
    image.loadImage("bg.png");
    
    
    ofEnableAlphaBlending();

    ofSetWindowShape(image.getWidth(), image.getHeight());
    
    
    float padding = 256;
    float maxVelocity = 0;
    
    int n = commonAssets->kParticles * 1024;

    for(int i = 0; i < n; i++) {
        
        float x,y,xv,yv;
        int n = ofRandom(0,4);
        switch(n)
        {
            case 0:
                x = -ofRandom(0, padding);
                y = ofRandom(0, ofGetHeight() );
                
                break;
            case 1:
                x = ofGetWidth()+ofRandom(0, padding);
                y = ofRandom(0, ofGetHeight() );
                
                break;
            case 2:
                x = ofRandom(0, ofGetWidth() );
                y = -ofRandom(0, padding);
                
                break;
            case 3:
                x = ofRandom(0, ofGetWidth());
                y = ofGetHeight()+ofRandom(0, padding);
                
                break;
        }
        
        xv = ofRandom(-maxVelocity, maxVelocity);
        yv = ofRandom(-maxVelocity, maxVelocity);
        Particle particle(x, y, xv, yv);
        particleSystem.add(particle);
        
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleNormal(i,ofVec3f(ofRandom(4, 8 ),0,0));
        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
        commonAssets->angle[i] = ofRandom(-PI,PI);

        
    }
    
    
    
    particleSystem.setTimeStep(1);
    
    
    
    
    ofBackground(0, 0, 0);
    
    isStart = false;
}

void MyScene2::update(float dt)
{
    if(!isStart)
    {
        return;
    }
    particleSystem.setupForces();
    
    // apply per-particle forces
    for(int i = 0; i < particleSystem.size(); i++) {
        Particle& cur = particleSystem[i];
        // global force on other particles
        particleSystem.addRepulsionForce(cur, 3, 1);
        // forces on this particle
        //        cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());
        cur.addDampingForce();
    }
    // single global forces
    particleSystem.addAttractionForce(ofGetWidth() / 2, ofGetHeight() / 2, 1500, 0.01);
    //    particleSystem.addRepulsionForce(mouseX, mouseY, 100, 2);
    particleSystem.update();
    vector<Particle> &particles = particleSystem.getParticles();
    int n = particles.size();
    for(int i = 0; i < n; i++)
    {
        commonAssets->setParticleVertex(i, particles[i]);
        if(particles[i].x>0 && particles[i].x < image.getWidth() && particles[i].y >0 && particles[i].y < image.getHeight())
        {
            ofColor c = image.getColor(particles[i].x, particles[i].y);
            if(c.r > 0 && c.g > 0 && c.b > 0 )commonAssets->setParticleColor(i, c);
            //            billboards.getNormals()[i].set(particles[i].xv*particles[i].yv, 0,0);
        }
    }
}
void MyScene2::draw()
{
    if(!isStart)
    {
        return;
    }
    ofSetColor(255, 255, 255);
    ofFill();
    commonAssets->draw();
    ofDrawBitmapString(ofToString(commonAssets->kParticles*1024) + "k particles", 32, 32);
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
}
void MyScene2::keyPressed(int key)
{
    if(key == ' ')
    {
        isStart = !isStart;
    }
}
void MyScene2::mousePressed( int x, int y, int button )
{
}    //scene notifications
void MyScene2::sceneWillAppear( ofxScene * fromScreen )
{
}
//scene notifications
void MyScene2::sceneWillDisappear( ofxScene * toScreen )
{
    
}

void MyScene2::sceneDidAppear()
{
    //    printf("ofxScene::sceneDidAppear() :: %d\n", sceneID);
        isStart = true;
}