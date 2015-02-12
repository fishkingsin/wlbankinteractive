//
//  MyScene4.h
//  wlbankinteractive
//
//  Created by James Kong on 4/1/15.
//
//

#ifndef __wlbankinteractive__MyScene4__
#define __wlbankinteractive__MyScene4__

#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "BaseScene.h"

#include "Constants.h"
#include "CommonAssets.h"
#include "ofxTween.h"
#include "ofxSvg.h"

class MyScene4 : public BaseScene{
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
    CommonAssets *commonAssets;
    
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    vector <ofPtr<ofxBox2dEdge> >       edges;
        ofImage image;
    int col , row ;
    
    vector<ofPolyline>  createOutlineFromImage(string path);

    ofParameter<int>maxParitcle;
    ofParameter<float>minRadius;
    ofParameter<float>maxRadius;
    ofParameter<bool>debugDraw;
    ofParameter<int>timeOut;
    ofParameter<float>minRScale;
    ofParameter<float>maxRScale;
    ofParameter<float>radius;
        ofParameter<float>pot_radius;
    float counter;
        ofxEasingLinear linear;
    ofxTween  counterForAlpha;
    float prevElapse;
    ofParameter<string>counterString;
    
    
    bool isStart;
    
    ofxSVG svg;

};


#endif /* defined(__wlbankinteractive__MyScene4__) */
