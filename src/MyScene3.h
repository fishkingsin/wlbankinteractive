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
#include "CommonAssets.h"
class MyScene3 : public ofxScene
{
public:
    void setup();
    
    void update(float dt);
    void draw();
    vector<ofVec3f>points;
    vector<ofVec3f>target;
    vector<int>radius;
    vector<ofVec3f> billboardVels;
    CommonAssets *commonAssets;
    int n ;
    int decay;

};
#endif /* defined(__wlbankinteractive__MeScene3__) */
