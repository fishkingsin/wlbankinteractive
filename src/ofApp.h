#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAnimatable.h"
#include "ofxAnimatableOfPoint.h"

#include "ofxFaceTracker.h"
#include "ofxFilterLibrary.h"
#include "ofxMioFlowGLSL.h"
#include "ofxSceneManager.h"
#include "MyScene1.h"
#include "MyScene2.h"
//#include "MyScene3.h"

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
    ofVideoGrabber grabber;

    ofParameter<int>Mode;
    ofxPanel gui;
    bool toggleDrawGUI;

    
    vector    <ofPtr<FlowPoint> >	points;

    
    enum Scenes{ SCENE_1 = 1, SCENE_2, SCENE_3 };
    ofxSceneManager *		sceneManager;
    MyScene1 *scene1;
    MyScene2 *scene2;
};
