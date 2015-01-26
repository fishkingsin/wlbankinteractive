//
//  MySceneFlow.h
//  wlbankinteractive
//
//  Created by James Kong on 25/1/15.
//
//

#pragma once

#include "ofMain.h"
//#include "ofxFlowTools.h"

//#define USE_PROGRAMMABLE_GL					// Maybe there is a reason you would want to
//#define USE_FASTER_INTERNAL_FORMATS			// about 15% faster but gives errors from ofGLUtils

//using namespace flowTools;

#include "BaseScene.h"

#include "Constants.h"
#include "CommonAssets.h"
class MySceneFlow : public BaseScene{
public:
    void setup();
    void init();
    void update(float dt);
    void draw();
    void keyPressed(int key);
    void mousePressed( int x, int y, int button );    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    void sceneDidAppear();
    void sceneDidDisappear(ofxScene *fromScreen);
    
};