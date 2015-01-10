#include "ofApp.h"
#include "MyScene2.h"
#include "MyScene3.h"
#include "MyScene4.h"
#define PORT 12345
//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(PORT);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofDisableArbTex();
    ofSetLogLevel(OF_LOG_VERBOSE);


    commonAssets.loadImage("particleGrid.png",4,4,8);
    commonAssets.setup();
    ///////////////////////////////////////
    
    sceneManager = ofxSceneManager::instance();
    scene1 = new MyScene1();
    sceneManager->addScene(scene1 , SCENE_1);
    ofAddListener(trackerEvent, scene1, &MyScene1::eventsIn);
    
    MyScene2* scene2 = new MyScene2();
    scene2->commonAssets = &commonAssets;
    sceneManager->addScene(scene2 , SCENE_2);
    
    MyScene3* scene3 = new MyScene3();
    scene3->commonAssets = &commonAssets;
    sceneManager->addScene(scene3 , SCENE_3);

    MyScene4* scene4 = new MyScene4();
    scene4->commonAssets = &commonAssets;
    sceneManager->addScene(scene4 , SCENE_4);

    sceneManager->setDrawDebug(true);
    sceneManager->setCurtainDropTime(1.0);
    sceneManager->setCurtainStayTime(0.0);
    sceneManager->setCurtainRiseTime(1.0);
    sceneManager->setOverlapUpdate(true);

    
    gui.setup("Settings");
    gui.add( scene1->coolDown.set("coolDown",0,0,100000));
//    gui.add( Mode.set("Mode",0,0,3));
    gui.add( timePriority.set("Toggle Time Prioirty",false));
    gui.add( maxIdleTime.set("Max Idle(min)",0.5,0,60.0f));
    
    gui.add(fps.set("fps",""));
    gui.add(currentIdleString.set("Idle",""));
    gui.loadFromFile("settings.xml");
    
    sceneManager->setDrawDebug(toggleDrawGUI);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // check for waiting messages

    while(receiver.hasWaitingMessages()){
        // get the next message
        ofParameterGroup pGroup;
        receiver.getParameter(pGroup);
//        string msg ;
//        msg += m.getAddress() + " : ";
//        for(int i = 0; i < m.getNumArgs(); i++){
//            // get the argument type
//            // display the argument - make sure we get the right type
//            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
//                msg += "int : "+ ofToString(m.getArgAsInt32(i)) +" | ";
//            }
//            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
//
//                msg += "float : "+ ofToString(m.getArgAsFloat(i)) +" | ";
//            }
//            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
//            
//                msg += "string : "+ m.getArgAsString(i) +" | ";
//            }
//           
//        }
//        if(m.getAddress()=="/contour" && m.getNumArgs() == 2)
//        {
//            ofVec2f v = ofVec2f(m.getArgAsFloat(0),m.getArgAsFloat(1));
//            ofNotifyEvent(trackerEvent,v,this);
//        }
//         ofLogVerbose() << msg;
        
    }
    if(timePriority)
    {
        int idle = ofGetElapsedTimef() - currentIdleTime;
        currentIdleString = ofToString(idle);
        if(idle>(maxIdleTime*60))
        {
            currentIdleTime = ofGetElapsedTimef();
            int sceneID = sceneManager->getCurrentSceneID();
            switch(sceneID)
            {
                case SCENE_1:
                    //go to next scene
                    sceneManager->goToScene(SCENE_2);
                    break;
                case SCENE_2:
                    //loop back
                    sceneManager->goToScene(SCENE_1);
                    break;
                
            }
        }
    }
    fps = ofToString(ofGetFrameRate());

    float dt = 0.016666666;
        sceneManager->update( dt );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    sceneManager->draw();
    if(toggleDrawGUI)gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') sceneManager->goToScene(SCENE_1, true); /* true >> regardless of curtain state (so u can change state while curtain is moving)*/
    if (key == '2') sceneManager->goToScene(SCENE_2);
    if (key == '3') sceneManager->goToScene(SCENE_3);
    if (key == '4') sceneManager->goToScene(SCENE_4);
    sceneManager->keyPressed(key);
    switch(key) 
    {
    
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ' :
            toggleDrawGUI = !toggleDrawGUI;
            sceneManager->setDrawDebug(toggleDrawGUI);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    sceneManager->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    sceneManager->windowResized(w,h); // in case your screens need to know, will forward to all of them
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


