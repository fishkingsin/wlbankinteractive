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
#include "ofxAnimatable.h"
//#include "MySceneLiquidfun.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void exit();
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
//    ofParameter<string> currentIdleString;
    ofParameter<string> currentSceneIndex;
    ofParameter<string> currentSceneID;
    ofParameter <string> status;
    ofParameter<bool>bLogFile;
    
    ofParameter<bool> toggleDrawGUI;
    ofParameter<bool>toggleMinimize;
    ofParameter<int> windowPositionX;
    ofParameter<int> windowPositionY;
    ofParameter<bool>bAlwaysOnTop;
    

    
    float currentIdleTime;
    
    ofxControlPanel gui;
    void enableLogToFile(bool &b);
    void enableMinize(bool &b);
    void toggleDebug(bool& _value);
    void enableAlwaysOnTop(bool &b);
    
    void nextScene();
//    enum Scenes{ SCENE_1 = 1, SCENE_2, SCENE_3 , SCENE_4 ,SCENE_6, SCENE_7,SCENE_8, SCENE_LOGO };
    enum Scenes{ SCENE_1 = 0, SCENE_2=1, SCENE_4=2 ,SCENE_LOGO=3};
    ofxSceneManager *		sceneManager;
    MyScene1 *scene1;
    
    CommonAssets commonAssets;
    ofxOscReceiver receiver;
    
    ofEvent <customeOSCData> trackerEvent;
    ofVideoPlayer player;
    commonOpenGlInfo info;
    
    ofxXmlSettings settings;
    vector<ofColor>curtainColors;
    
    
    void handleToNextScene(toNextScene &tonextscene);
    //handle logo
//    void tweenEnd(int &i);
//    void tweenEasingOutEnd(int &i);
//    ofxEasingLinear easingeLinear;
//    ofxTween alphaTween;
    simpleFileLister videoFileLister;
    void eventsIn(guiCallbackData & data);
    //MySceneLiquidfun sceneLiquidfun;

//    ofDirectory dirVideo;
    vector<int>sceneSequence;
    int sceneIndex;
    
};
