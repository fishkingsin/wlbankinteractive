//
//  MyScene4.cpp
//  wlbankinteractive
//
//  Created by James Kong on 4/1/15.
//
//

#include "MyScene4.h"


void MyScene4::setup()
{
    image.loadImage("bg.png");
    box2d.init();
    box2d.setGravity(0, 30);
    box2d.createGround();
    box2d.setFPS(30.0);
    setupEdge();
}
void MyScene4::init()
{
    for(int i = 0 ; i < 200; i++)
    {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 0.5);
        c.get()->setup(box2d.getWorld(), ofGetWidth()*0.5+ofRandom(-5,5), ofGetHeight()*0.5, ofRandom(5,14));
        ofVec2f pos = c.get()->getPosition();
        float r = c.get()->getRadius();

        commonAssets->setParticleVertex(i, pos);
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleNormal(i,ofVec3f(r*2,0,0));

        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));

        circles.push_back(c);
    }
        commonAssets->updateAttribtuteData();
}
void MyScene4::update(float dt)
{
    
     box2d.update();
    for(int i=0; i<circles.size(); i++) {
        ofVec2f pos = circles[i].get()->getPosition();
        float r = circles[i].get()->getRadius();
        commonAssets->setParticleVertex(i, pos);
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleNormal(i,ofVec3f(r*2,0,0));
//        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));

        if(pos.x>0 && pos.x < image.getWidth() && pos.y >0 && pos.y < image.getHeight())
        {
            ofColor c = image.getColor(pos.x, pos.y);
            if(c.r > 0 && c.g > 0 && c.b > 0 )commonAssets->setParticleColor(i, c);
        }
        
    }
    commonAssets->updateAttribtuteData();
}
void MyScene4::draw()
{
    commonAssets->draw();
}
void MyScene4::keyPressed(int key)
{
    if(key == 'b') {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 0.5);
        c.get()->setup(box2d.getWorld(), ofGetWidth()*0.5, 0, ofRandom(5,14));
        circles.push_back(c);
    }
    if(key == 'c') {
        edges.clear();
    }
    if(key=='e')
    {
        setupEdge();
    }
}
void MyScene4::mousePressed( int x, int y, int button )
{
    
}
void MyScene4::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
    init();
}
//scene notifications
void MyScene4::sceneWillDisappear( ofxScene * toScreen )
{
    
}
void MyScene4::sceneDidAppear()
{
    
}
void MyScene4::sceneDidDisappear(ofxScene *fromScreen)
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }

}

void MyScene4::setupEdge()
{
    int density = 10;
    float radius =  ofGetHeight()*0.25;
    ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    for (int i=-180+density; i<180; i+=density) {
        float x = sin(TWO_PI*(i/360.0f))*radius+ofGetWidth()*0.5;
        float y = cos(TWO_PI*(i/360.0f))*radius+ofGetHeight()*0.5;
        edge.get()->addVertex(x, y);
        edge.get()->create(box2d.getWorld());
        
    }
    edges.push_back(edge);
}
