//
//  MyScene2.h
//  wlbankinteractive
//
//  Created by Kong king sin on 8/12/14.
//
//

#ifndef __wlbankinteractive__MyScene2__
#define __wlbankinteractive__MyScene2__

#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "BaseScene.h"
#include "Constants.h"
#include "CommonAssets.h"

class CustomParticle;
class MyScene2 : public BaseScene{
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
//    ParticleSystem particleSystem;

    ofImage image;
    bool isStart;

    CommonAssets *commonAssets;
    
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    ofParameter<int>maxParitcle;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
    ofParameter<float>radius;
    ofParameter<int>timeOut;
    float counter;
    float prevElapse;
    ofParameter<string>counterString;
    ofParameter<float>minRScale;
        ofParameter<float>maxRScale;
    float counterForAlpha;
};


#endif /* defined(__wlbankinteractive__MyScene2__) */
