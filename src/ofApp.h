#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAnimatable.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxDelaunay.h"
#include "ofxOpenCV.h"
#include "ofxOpticalFlowLK.h"
#include "ofxFaceTracker.h"
#include "ofxFilterLibrary.h"
#include "ofxMioFlowGLSL.h"
#include "ofxSceneManager.h"
#include "MyScene1.h"
#include "MyScene2.h"
#include "CommonAssets.h"
class FlowPoint : public ofxAnimatableOfPoint
{
public:
    ofColor color;
    float _radius;
    
    void setup()
    {
        color = ofColor::fromHsb(ofRandom(255),100,100);
    }

    
    void draw()
    {
        ofPushMatrix();
        ofTranslate(ofxAnimatableOfPoint::getCurrentPosition());

        ofSetColor(color);
        ofFill();
        ofCircle(0, 0, _radius);
        
        ofPopMatrix();
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
    ofVideoPlayer videoPlayer;
    ofVideoGrabber grabber;
//scening
    ofxOpticalFlowLK opticalFlow;
    ofxCvColorImage cvImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvContourFinder 	contourFinder;
    
    ofFbo fbo;
    ofPixels pixels;
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
    ofParameter<int>Mode;
    ofParameter<string>fps;
    
    ofParameter<bool> timePriority;
    ofParameter<float> maxIdleTime;
    ofParameter<string> currentIdleString;
    float currentIdleTime;
    ofxPanel gui;
    bool toggleDrawGUI;

    
    vector    <ofPtr<FlowPoint> >	points;

    
    enum Scenes{ SCENE_1 = 1, SCENE_2, SCENE_3 };
    ofxSceneManager *		sceneManager;
    MyScene1 *scene1;
//    MyScene_2 *scene2;
    
    CommonAssets commonAssets;
};
