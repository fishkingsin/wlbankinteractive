//
//  MyScene1.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 5/12/14.
//
//

#include "MyScene1.h"
MyScene1::MyScene1()
{
    
}
void MyScene1::setup(){  //load your scene 1 assets here...
    
    box2d.init();
    box2d.setGravity(0, -50);
    box2d.createBounds(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    counter = 0;
    images.resize(8);
    for(int i = 0; i < 8 ; i++)
    {
        images[i].loadImage("images/"+ofToString(i+1)+".png");
    }
    
};


void MyScene1::update(float dt){ //update scene 1 here
    
    
    
    box2d.update();
    while(circles.size()>5000)
    {
        circles.erase(circles.begin());
        
    }
    float diff = ofGetElapsedTimeMillis() - counter;
    if(diff > coolDown)
    {
        int n = ofRandom(1,10);
        if(n<circles.size())
        {
            for (int i = 0 ; i < n ; i++)
            {
                circles.erase(circles.begin());
            }
        }
        counter = ofGetElapsedTimeMillis();
    }
    
    for (int i = 0 ; i < circles.size() ; i++) {
        commonAssets->setParticleAngle(i, (circles[i]->getRotation()/360.0f)*TWO_PI);
        commonAssets->setParticleVertex(i, circles[i]->getPosition());
    }
    commonAssets->updateAttribtuteData();
        
};

void MyScene1::draw(){ //draw scene 1 here
    
    ofPopStyle();
    ofPushStyle();
    commonAssets->draw();
//    for(int i=0; i<circles.size(); i++) {
//        ofFill();
//        ofSetHexColor(0xf6c738);
//        circles[i].get()->draw();
#ifdef USE_TRIANGLE
        triangulation.addPoint(circles[i].get()->getPosition());
#endif
//    }
#ifdef USE_TRIANGLE
    triangulation.triangulate();
#endif
    // draw the ground
    box2d.drawGround();
    ofPopStyle();
    ofPushStyle();
    ofNoFill();
#ifdef USE_TRIANGLE
    triangulation.draw();
#endif
    ofPopStyle();
#ifdef USE_TRIANGLE
    triangulation.reset();
#endif
    
};

void MyScene1::keyPressed(int key)
{
    switch(key)
    {
        case 'b':
        {
            circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
            float r = ofRandom(4, 20);
            
            
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), CANVAS_WIDTH*0.5+ofRandom(-50, 50), CANVAS_HEIGHT*0.5+ofRandom(-50, 50), r);
            ofColor c = ofColor::white;
            circles.back().get()->setupTheCustomData(ofColor::fromHsb(c.getHue(),255,255),images[ofRandom(images.size())],r);
            
            commonAssets->setParticleTexCoords(circles.size()-1,(int)ofRandom(commonAssets->cellColls),(int)ofRandom(commonAssets->cellRows) );
            commonAssets->setParticleColor(circles.size()-1, ofColor::white);
            commonAssets->setParticleNormal(circles.size()-1,ofVec3f(circles.back().get()->getRadius()*2,0,0));
            
            commonAssets->divAtt[circles.size()-1] = 1.0f/commonAssets->cellColls;

        }
            break;
        case 's':
        {
        }
            break;
    }
    
}
void MyScene1::mousePressed( int x, int y, int button ){
    
}

//scene notifications
void MyScene1::sceneWillAppear( ofxScene * fromScreen ){  // reset our scene when we appear
    commonAssets->reset();
};


//scene notifications
void MyScene1::sceneWillDisappear( ofxScene * toScreen ){
    
}
void MyScene1::sceneDidDisappear( ofxScene * fromScreen )
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }
}

void MyScene1::eventsIn(customeOSCData & data)
{

    circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
    float r = ofRandom(4, 10);
    
    
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    circles.back().get()->setup(box2d.getWorld(), data.pos.x*CANVAS_WIDTH, data.pos.y*CANVAS_HEIGHT, r);
    ofColor c = ofColor::fromHsb(data.c.getHue(),MAX(data.c.getSaturation() ,200), MAX(data.c.getBrightness(),200));
    circles.back().get()->setupTheCustomData(c,images[ofRandom(images.size())],r);
    
}