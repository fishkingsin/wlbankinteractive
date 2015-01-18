//
//  MyScene1.h
//  wlbankinteractive
//
//  Created by Kong king sin on 4/12/14.
//
//

#ifndef wlbankinteractive_MyScene1_h
#define wlbankinteractive_MyScene1_h
#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "ofxScene.h"

#include "Constants.h"

#include "CustomParticle.h"
#include "CommonAssets.h"

class MyScene1 : public ofxScene{
public:
    MyScene1();
    void setup();
    
    void update(float dt);
    
    void draw();
    
    void keyPressed(int key);
    void mousePressed( int x, int y, int button );
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    
    void sceneDidDisappear( ofxScene * fromScreen );
    void eventsIn(customeOSCData & data);
    //sencing
    
    ofParameter<int> coolDown;
    ofEvent<toNextScene>toNextSceneEvent;
    
    
    float counter;
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<CustomParticle> >	circles;		  //	default box2d circles
#ifdef USE_TRIANGLE
    ofxDelaunay triangulation;
#endif
    vector< vector< ofPtr<ofImage> > > imagesSet;
    vector<ofImage> images;
    CommonAssets *commonAssets;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
    ofParameter<string>numParticle;
    ofParameter<int>maxParticle;
};

#endif
