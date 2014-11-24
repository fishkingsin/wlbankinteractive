#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxBox2d.h"
#include "ofxOpticalFlowLK.h"
#include "ofxGui.h"

#define VIDEO_WIDTH 160
#define VIDEO_HEIGHT 120
class Data {
public:
    ofColor color;
    int		id;
};
// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
    
public:
    
    void setupTheCustomData(ofColor color) {
        
        // we are using a Data pointer because
        // box2d needs to have a pointer not
        // a referance
        setData(new Data());
        Data * theData = (Data*)getData();
        
        theData->id = ofRandom(0, 100);
        
        theData->color = color;
        
    }
    
    void draw() {
        Data* theData = (Data*)getData();
        if(theData) {
            
            // Evan though we know the data object lets just
            // see how we can get the data out from box2d
            // you would use this when using a contact listener
            // or tapping into box2d's solver.
            
            float radius = getRadius();
            ofPushMatrix();
            ofTranslate(getPosition());
            ofRotateZ(getRotation());
            ofSetColor(theData->color);
            ofFill();
            ofCircle(0, 0, radius);
            
            ofPopMatrix();
        }
    }
    
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    //sencing
    ofxOpticalFlowLK opticalFlow;
    ofxCvColorImage cvImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvContourFinder 	contourFinder;
    ofFbo fbo;
    ofPixels pixels;
    
    ofVideoGrabber grabber;
    ofParameter<int>  threshold;
    ofParameter<int> minArea;
    ofParameter<int> maxArea;
    ofParameter<int> nConsidered;
    ofParameter<bool> bFindHoles;
    ofParameter<bool> bUseApproximation ;
    ofParameter<bool> bBlur;
    ofParameter<bool> debugDraw1;
    ofParameter<bool> debugDraw2;
    ofParameter<bool> debugDraw3;
    ofxPanel gui;
    float counter;
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<CustomParticle> >	circles;		  //	default box2d circles
    
    
};
