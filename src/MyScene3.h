//
//  MyScene3.h
//  wlbankinteractive
//
//  Created by Kong king sin on 8/12/14.
//
//

#ifndef __wlbankinteractive__MyScene3__
#define __wlbankinteractive__MyScene3__

#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "ofxScene.h"

#include "Constants.h"
#include "ParticleSystem.h"
#define USE_OFVBO 1
#if USE_OFVBO
#else
#include "VBOBillboard.h"
#endif
class MyScene3 : public ofxScene{
public:
    
    void setup();
    
    void update(float dt);
    void draw();
    void keyPressed(int key);
    void mousePressed( int x, int y, int button );    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    void sceneDidAppear();

    ParticleSystem particleSystem;
#if USE_OFVBO
    int kParticles;
    ofShader billboardShader;
    ofImage texture;
    
    ofVboMesh billboards;
    int                     cellRows;
    int                     cellColls;
    float           texW, texH;
    void setParticleTexCoords(int i, float columnID, float rowID);
    vector<float>divAtt;
    vector<float>offSetXAtt;
    vector<float>offSetYAtt;
    vector<float>angle;
    
#else
    VBOBillboard billboard;
#endif
    ofImage image;
    bool isStart;


    
};

#endif /* defined(__wlbankinteractive__MyScene3__) */
