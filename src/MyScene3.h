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
    vector<ofxTween> tweensX;
    vector<ofxTween> tweensY;
    ofxEasingElastic easingelastic;
    int count;
    int interval;
    int MAX_POINTS;
    ofImage image;
    int step;
    CommonAssets *commonAssets;

};
#endif /* defined(__wlbankinteractive__MeScene3__) */
