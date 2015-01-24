//
//  MyScene6.h
//  wlbankinteractive
//
//  Created by James Kong on 18/1/15.
//
//

#ifndef __wlbankinteractive__MyScene6__
#define __wlbankinteractive__MyScene6__


#include "BaseScene.h"
#include "ofxTween.h"
#include "CommonAssets.h"
#include "Constants.h"
class CustomParticle;
class MyScene6 : public BaseScene{
public:
    
    void setup();
    void init();
    void update(float dt);
    void draw();
//    void keyPressed(int key);
//    void mousePressed( int x, int y, int button );    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    void sceneDidAppear();
    void sceneDidDisappear(ofxScene *fromScreen);
    vector<ofPtr<ofxTween> > tweensX;
    vector<ofPtr<ofxTween> > tweensY;
    vector<ofPtr<ofVec3f> > start;
    vector<ofPtr<ofVec3f> > end;
    vector<ofPtr<ofVec3f> > particleSizes;
    vector<ofxEasing* >easings;
    ofxEasingExpo easingExpo;
    ofxEasingSine easingSine;
//    ofxEasingElastic easingElastic;
    ofxEasingLinear easingLinear;
    ofxEasingCubic easingCubic;
    
    CommonAssets *commonAssets;
    ofImage image;
    ofParameter<int>maxParitcle;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
    ofParameter<float>delay;
    ofParameter<float>duration;
    ofParameter<float>theStep;
    ofParameter<float>minStep;
    ofParameter<float>maxStep;
    ofParameter<bool>bDebug;
    ofParameter<float>maxR;
    ofParameter<float>maxOutterR;
    
    void tweenEnd(int &i);

    
    
    
};

#endif /* defined(__wlbankinteractive__MyScene6__) */
