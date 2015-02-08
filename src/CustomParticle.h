//
//  CustomParticle.h
//  wlbankinteractive
//
//  Created by Kong king sin on 5/12/14.
//
//
#include "ofMain.h"
#include "ofxBox2d.h"
class Data {
public:
    ofColor color;
    int		id;
    ofImage *image;
    float r;
   
};
// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
    
public:
    
    void setupTheCustomData(ofColor color , ofImage &image , int size);
    void update();
    void draw();
    static bool shouldRemoveOffScreen(ofPtr<CustomParticle> shape);
     float targetR;
    int index;
    
    
};