#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSceneManager.h"
#include "MyScene1.h"
#include "MyScene2.h"
#include "CommonAssets.h"
#include "ofxOsc.h"

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
    
    
    ofParameter<string>fps;
    
    ofParameter<bool> timePriority;
    ofParameter<float> maxIdleTime;
    ofParameter<string> currentIdleString;
    float currentIdleTime;
    ofxPanel gui;
    bool toggleDrawGUI;
    
    enum Scenes{ SCENE_1 = 1, SCENE_2, SCENE_3 , SCENE_4 };
    ofxSceneManager *		sceneManager;
    MyScene1 *scene1;
    
    CommonAssets commonAssets;
    ofxOscReceiver receiver;
    
    ofEvent <ofVec2f> trackerEvent;
};
