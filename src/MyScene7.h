//
//  MyScene7.h
//  wlbankinteractive
//
//  Created by James Kong on 18/1/15.
//
//

#ifndef __wlbankinteractive__MyScene7__
#define __wlbankinteractive__MyScene7__

#include "BaseScene.h"
#include "ofxTween.h"
#include "CommonAssets.h"
#include "Constants.h"
#include "ofxOpenCv.h"
class CustomParticle;
class MyScene7 : public BaseScene{
public:
    
    void setup();
    void init();
    void update(float dt);
    void draw();
    void sceneWillAppear( ofxScene * fromScreen );

    void sceneWillDisappear( ofxScene * toScreen );
    void sceneDidAppear();
    void sceneDidDisappear(ofxScene *fromScreen);
    vector<ofPolyline>createOutlineFromImage();
    vector<ofPtr<ofxTween> > tweensX;
    vector<ofPtr<ofxTween> > tweensY;
    vector<ofPtr<ofVec3f> > start;
    vector<ofPtr<ofVec3f> > end;
    vector<ofPtr<ofVec3f> > particleSizes;
    vector<ofxEasing* >easings;
    ofxEasingExpo easingExpo;
    ofxEasingSine easingSine;
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
    ofParameter<bool>bDebug;
    ofParameter<float>maxR;
    ofParameter<float>maxOutterR;
    
    ofParameter<int>maxStep;
    ofParameter<int>minStep;
    
    ofParameter<int>maxDelay;
    ofParameter<int>minDelay;
    ofParameter<int>maxDensity;
    void tweenEnd(int &i);
    
    vector<ofPolyline> polylines;
    
    
    
};

#endif /* defined(__wlbankinteractive__MyScene7__) */
