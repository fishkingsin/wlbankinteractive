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
    int kParticles;
    ParticleSystem particleSystem;
    
    ofShader billboardShader;
    ofImage texture;
    
    ofVboMesh billboards;
    ofImage image;
    bool isStart;
    void setParticleTexCoords(int i, float columnID, float rowID);
    int                     cellRows;
    int                     cellColls;
    float           texW, texH;
    
};

#endif /* defined(__wlbankinteractive__MyScene3__) */
