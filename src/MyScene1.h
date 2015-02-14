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
#include "BaseScene.h"
#include "Constants.h"

#include "CustomParticle.h"
#include "CommonAssets.h"

class MyScene1 : public BaseScene{
public:
    MyScene1();
    void setup();
    
    void update(float dt);
    
    void draw();
    
    void keyPressed(int key);
    void mousePressed( int x, int y, int button );
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneDidAppear();
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    
    void sceneDidDisappear( ofxScene * fromScreen );
    void eventsIn(customeOSCData & data);
    void createParticle(float x , float y , ofColor color);
    //sencing
    
    ofParameter<int> coolDown;
    
    
    
    float counter;
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<CustomParticle> >	circles;		  //	default box2d circles
    vector <ofPtr<ofxBox2dEdge> >       edges;
    void setupEdge();
#ifdef USE_TRIANGLE
    ofxDelaunay triangulation;
#endif
    vector< vector< ofPtr<ofImage> > > imagesSet;
    vector<ofImage> images;
    CommonAssets *commonAssets;
    ofParameterGroup paraGroup;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
    ofParameter<string>numParticle;
    ofParameter<int>maxParticle;
    bool isFireEvent;
    
    //coldown;
    ofPoint prevPoint;
    ofPoint currPoint;
    ofParameter<float >minDis;
        ofParameter<float >offSetPower;
    ofParameter<float >density;
    ofParameter<float >bounce;
    ofParameter<float >fiction;
    ofParameter<float >minAlpha;
    ofParameter<float> maxInputY;
    ofParameter<float> minInputY;
    ofParameter<float> maxInputX;
    ofParameter<float> minInputX;
    
    ofParameter<bool>bDebug;
    ofParameter<float> minObjectAppearLeft;
    ofParameter<float> maxObjectAppearLeft;
    ofParameter<float> minObjectAppearRight;
    ofParameter<float> maxObjectAppearRight;
    ofParameter<float> objectDecay;
    ofxTween objectX;
    ofxEasingLinear linearEasing;
    ofParameter<float> objectAge;
    ofParameter<float>objectDuration;
    ofRectangle objectAppearLeft;
    ofRectangle objectAppearRight;
    ofPoint textObject;
    ofxBox2dCircle dream;
    void objectAppearRegionUpdate(float &f);
    
    ofImage image;
    bool isStart;
    ofTrueTypeFont font;
    string theText;
};

#endif
