#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxBox2d.h"
#include "ofxOpticalFlowLK.h"
#include "ofxGui.h"
#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480
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
    ofxPanel gui;
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    
};
