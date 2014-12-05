#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofSetLogLevel(OF_LOG_VERBOSE);
    grabber.setDesiredFrameRate(60);
    grabber.setDeviceID(0);
    grabber.initGrabber(VIDEO_WIDTH,VIDEO_HEIGHT);
    ///////////////////////////////////////
    
    sceneManager = ofxSceneManager::instance();
    scene1 = new MyScene1();
    scene1->grabber = &grabber;
    sceneManager->addScene(scene1 , SCENE_1);

    
    scene2 = new MyScene2();
    scene2->grabber = &grabber;
    sceneManager->addScene(scene2 , SCENE_1);

    sceneManager->addScene( scene2, SCENE_2);
    //    sceneManager->addScene( new MyScene3(), SCENE_3);
    
    sceneManager->setDrawDebug(true);
    sceneManager->setCurtainDropTime(1.0);
    sceneManager->setCurtainStayTime(0.0);
    sceneManager->setCurtainRiseTime(1.0);
    sceneManager->setOverlapUpdate(true);
   sceneManager->goToScene(SCENE_2);
    int step = 10;
    for(int y = 0 ;y < VIDEO_HEIGHT ; y+=step )
    {
        for(int x = 0 ;x < VIDEO_WIDTH ; x+=step )
        {
            points.push_back(ofPtr<FlowPoint>(new FlowPoint));
            points.back().
            get()->setPosition(ofPoint(x,y));
            points.back().get()->setup();
        }
    }
    
    gui.setup("Settings");
    gui.add(scene1->threshold.set("threashold",80,1,255));
    gui.add( scene1->minArea.set("minArea",20,20,VIDEO_WIDTH*VIDEO_HEIGHT));
    gui.add( scene1->maxArea.set("maxArea",80,20,VIDEO_WIDTH*VIDEO_HEIGHT));
    gui.add( scene1->nConsidered.set("nConsidered",10,1,100));
    gui.add( scene1->bFindHoles.set("bFindHoles",true));
    gui.add( scene1->bUseApproximation.set("bUseApproximation",true));
    gui.add( scene1->bBlur.set("bBlur",true));
    gui.add( scene1->debugDraw1.set("debugDraw1",false));
    gui.add( scene1->debugDraw2.set("debugDraw2",false));
    gui.add( scene1->debugDraw3.set("debugDraw3",false));
    gui.add( scene1->coolDown.set("coolDown",0,0,100000));
    gui.add( Mode.set("Mode",0,0,3));

    gui.loadFromFile("settings.xml");
    
    sceneManager->setDrawDebug(toggleDrawGUI);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = 0.016666666;
    sceneManager->update( dt );
    
    switch(Mode)
    {
        case 0:
        {
            
        }
            break;
        case 1:
        {
            float dt = 1.0f / ofGetFrameRate();
            for(int i=0; i<points.size(); i++) {
                points[i].get()->update(dt);
            }
        }
            break;
        case 2:
        {
//            mioFlow.update(grabber.getTextureReference());
        }
            break;
        case 3:
        {
            
        }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    sceneManager->draw();
    
    
    switch(Mode)
    {
        case 0:
        {
            
        }
            break;
        case 1:
        {
            for(int i=0; i<points.size(); i++) {
                points[i].get()->draw();
            }
        }
            break;
        case 2:
//            mioFlow.getFlowBlurTexture().draw(0,0);
            
            break;
        case 3:
            break;
    }
    
    
    if(toggleDrawGUI)gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') sceneManager->goToScene(SCENE_1, true); /* true >> regardless of curtain state (so u can change state while curtain is moving)*/
    if (key == '2') sceneManager->goToScene(SCENE_2);
//    if (key == '3') sceneManager->goToScene(SCENE_3);
    sceneManager->keyPressed(key);
    switch(key)
    {
    
        case 'f':
            ofToggleFullscreen();
            break;
//        case 'c':
//        {       float r = ofRandom(4, 20);
//            circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
//            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
//            circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
//        }
//            break;
//        case 's':
//        {
//            grabber.videoSettings();
//        }
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
