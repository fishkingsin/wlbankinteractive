//
//  MySceneLiquidfun.h
//  wlbankinteractive
//
//  Created by James Kong on 27/1/15.
//
//
#pragma once
#include "ofxLiquidFun.h"
#include "ofxOpenCv.h"
#include "BaseScene.h"

#include "Constants.h"
#include "CommonAssets.h"

class MySceneLiquidfun : public BaseScene{
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
    void setupEdge();
    vector<ofPolyline>  createOutlineFromImage();
    
    CommonAssets *commonAssets;
    
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector <ofPtr<ofxBox2dEdge> >       edges;
    ofImage image;
    int col , row ;
    
    
    ofParameter<int>maxParitcle;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
    ofParameter<bool>debugDraw;
    ofParameter<int>timeOut;
    ofParameter<float>minRScale;
    ofParameter<float>maxRScale;
    float counter;
    float prevElapse;
    ofParameter<string>counterString;
    
    bool isStart;
    
    //liquidfun
    ofxBox2dParticleSystem particles;
    
};
