#pragma once
//#define USE_PROGRAMMABLE_GL					// Maybe there is a reason you would want to
#include "ofMain.h"
#include "ofxControlPanel.h"
#include "ofxSceneManager.h"
#include "MyScene1.h"
#include "MyScene2.h"
#include "MyScene3.h"
#include "MyScene4.h"
#include "MyScene6.h"
#include "MyScene7.h"
#include "MyScene8.h"
#include "LogoScene.h"
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
    ofParameter<bool> bAuto;
    ofParameter<bool> timePriority;
    ofParameter<float> maxIdleTime;
    ofParameter<string> currentIdleString;
    float currentIdleTime;
//    ofxPanel gui;
    ofxControlPanel gui;
    ofParameter<bool> toggleDrawGUI;
    void toggleDebug(bool& _value);
    
    void nextScene();
    enum Scenes{ SCENE_1 = 1, SCENE_2, SCENE_3 , SCENE_4 , SCENE_7,SCENE_8, SCENE_LOGO };
    ofxSceneManager *		sceneManager;
    MyScene1 *scene1;
    
    CommonAssets commonAssets;
    ofxOscReceiver receiver;
    
    ofEvent <customeOSCData> trackerEvent;
    ofVideoPlayer player;
    commonOpenGlInfo info;
    ofParameter <string> status;

    ofxXmlSettings settings;
    vector<ofColor>curtainColors;
    
    
    void handleToNextScene(toNextScene &tonextscene);
    
};
