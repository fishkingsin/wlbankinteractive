//
//  MeScene3.h
//  wlbankinteractive
//
//  Created by Kong king sin on 25/12/14.
//
//

#ifndef __wlbankinteractive__MeScene3__
#define __wlbankinteractive__MeScene3__

#include <stdio.h>
#include "ofMain.h"
#include "ofxScene.h"
#include "ofxTween.h"
#include "CommonAssets.h"
#include "Constants.h"
#define INTERVAL_MILLS 1000

class MyScene3 : public ofxScene
{
public:
    void setup();
    void init();
    void update(float dt);
    void draw();
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneDidAppear();
    void sceneDidDisappear(ofxScene *fromScreen);
    vector<ofPtr<ofxTween> > tweensX;
    vector<ofPtr<ofxTween> > tweensY;
    ofxEasingElastic easingelastic;
    int count;
    int interval;
    int MAX_POINTS;
    ofImage image;
    int step;
    CommonAssets *commonAssets;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
};
#endif /* defined(__wlbankinteractive__MeScene3__) */
