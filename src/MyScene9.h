//
//  MyScene9.h
//  wlbankinteractive
//
//  Created by James Kong on 24/1/15.
//
//

#ifndef __wlbankinteractive__MyScene9__
#define __wlbankinteractive__MyScene9__
#include "BaseScene.h"
#include "ofxTween.h"
#include "CommonAssets.h"
#include "Constants.h"
#include "ofxOpenCv.h"
#include "ofxTriangleMesh.h"
class MyScene9 : public BaseScene {
public:
    void setup();
    void update(float dt);
    void draw();
    void sceneWillAppear(ofxScene *fromScreen);
    ofImage image;
    vector<ofxTriangleMesh> triangleMesh;
    vector<ofxTriangleMesh> tirangulateFromImage();
    CommonAssets *commonAssets;
};
#endif /* defined(__wlbankinteractive__MyScene9__) */
