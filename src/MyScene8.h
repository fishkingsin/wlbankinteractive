//
//  MyScene8.h
//  wlbankinteractive
//
//  Created by James Kong on 19/1/15.
//
//

#ifndef __wlbankinteractive__MyScene8__
#define __wlbankinteractive__MyScene8__

#include "ofMain.h"
#include "ofxScene.h"
#include "Particle.h"
#include "CommonAssets.h"
#include "Constants.h"
class CircularParticle {
public:
    
    void setup() {
        vel.x = 2*ofRandomf();
        vel.y = 2*ofRandomf();
        angle = ofRandomf()*TWO_PI;
        age = 0;
    }
    
    void draw() {
        ofPushStyle();
        ofSetLineWidth(2);
        ofSetColor(color,ofMap(age,0,20,255,0,true));
        ofLine(oldpos,pos);
        ofPopStyle();
    }
    
    void update() {
        angle += ofSignedNoise(pos.x, pos.y)*TWO_PI;
        vel.rotate(angle);
        oldpos = pos;
        pos += vel;
        age++;
    }

    
    ofVec2f pos,vel,acc,oldpos;
    float angle;
    ofColor color;
    int age;
};


class MyScene8 : public ofxScene {
public:
    void setup();
    void init();
    void update(float dt);
    void draw();
    void keyPressed(int key);
//    void mousePressed( int x, int y, int button );    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    void sceneDidAppear();
    void sceneDidDisappear(ofxScene *fromScreen);

    void createParticle();
    
    ofImage img;
    
    vector<CircularParticle> particles;
    CommonAssets *commonAssets;
    ofFbo fbo;
    
    float counter;
    float prevElapse;
        ofParameter<int>timeOut;
    ofParameter<string>counterString;
    ofEvent<toNextScene>toNextSceneEvent;
};


#endif /* defined(__wlbankinteractive__MyScene8__) */
