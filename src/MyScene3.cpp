//
//  MyScene3.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 8/12/14.
//
//

#include "MyScene3.h"
void MyScene3::setup()
{
    image.loadImage("bg.png");
    ofDisableArbTex();
    texture.loadImage("dot.png");
    ofEnableAlphaBlending();
    texW = texture.getWidth();
    texH = texture.getHeight();
    
    cellRows  = 2;
    cellColls = 2;
    ofSetWindowShape(image.getWidth(), image.getHeight());
    kParticles = 8;
    
    float padding = 256;
    float maxVelocity = 0;
    billboards.getVertices().resize(kParticles * 1024);
    billboards.getColors().resize(kParticles * 1024);
    billboards.getTexCoords().resize(kParticles * 1024);
    billboards.getNormals().resize(kParticles * 1024,ofVec3f(0));
    for(int i = 0; i < kParticles * 1024; i++) {
        float x,y,xv,yv;
        int n = ofRandom(0,3);
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
        billboards.setColor(i, ofColor::fromHsb(0, 0, 255));
        billboards.setNormal(i,ofVec3f(ofRandom(3, 12 ),0,0));
        billboards.setTexCoord(i,ofVec2f((int)ofRandom(0, 2 ), (int)ofRandom(0, 2)));
        //        setParticleTexCoords(i, (int)ofRandom(0, 2 ), (int)ofRandom(0, 2));
        
    }
    
    particleSystem.setTimeStep(1);
    
    
    
    
    ofBackground(0, 0, 0);
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    //    billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //    billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    if(ofGetGLProgrammableRenderer()){
        billboardShader.load("shadersGL3/Billboard");
    }else{
        billboardShader.load("shadersGL2/Billboard");
    }
    
    isStart = false;
}

void MyScene3::update(float dt)
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
        
        billboards.getVertices()[i] = particles[i];
        if(billboards.getVertices()[i].x>0 && billboards.getVertices()[i].x < image.getWidth() && billboards.getVertices()[i].y >0 && billboards.getVertices()[i].y < image.getHeight())
         {
         ofColor c = image.getColor(billboards.getVertices()[i].x, billboards.getVertices()[i].y);
         if(c.r > 0 && c.g > 0 && c.b > 0 )billboards.setColor(i, c);
         //            billboards.getNormals()[i].set(particles[i].xv*particles[i].yv, 0,0);
         }
    }
}
void MyScene3::draw()
{
    if(!isStart)
    {
        return;
    }
    ofSetColor(255, 255, 255);
    ofFill();
    //	particleSystem.draw();
    
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    ofDrawBitmapString(ofToString(kParticles) + "k particles", 32, 32);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
}
void MyScene3::keyPressed(int key)
{
    if(key == ' ')
    {
        isStart = !isStart;
    }
}
void MyScene3::mousePressed( int x, int y, int button )
{
}    //scene notifications
void MyScene3::sceneWillAppear( ofxScene * fromScreen )
{
}
//scene notifications
void MyScene3::sceneWillDisappear( ofxScene * toScreen )
{
    
}

void MyScene3::sceneDidAppear()
{
//    printf("ofxScene::sceneDidAppear() :: %d\n", sceneID);
    isStart = true;
}