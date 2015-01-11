#include "ofApp.h"
#include "MyScene2.h"
#include "MyScene3.h"
#include "MyScene4.h"
#define PORT 12345
//--------------------------------------------------------------
void ofApp::setup(){
    info.version = (char*)glGetString(GL_VERSION);
    info.vendor = (char*)glGetString(GL_VENDOR);
    info.renderer = (char*)glGetString(GL_RENDERER);
    info.bVboSupported = false;
    info.bShadersSupported = false;
    info.bPointSpritesSupported = false;
    if(glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite")) {
        info.bPointSpritesSupported = true;
    }
    
    if(glewIsSupported("GL_ARB_vertex_buffer_object")) {
        info.bVboSupported = true;
    }
    
    if(glewIsSupported("GL_ARB_vertex_shader")) {
        info.bShadersSupported = true;
    }
    
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &info.maxTextureSize);
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, info.maxDimensions);
    glGetIntegerv(GL_MAX_LIGHTS, &info.maxLights);
    
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofDisableArbTex();
    ofSetLogLevel(OF_LOG_VERBOSE);
    player.loadMovie("movies/CNY theme.mov");
    player.setLoopState(OF_LOOP_NORMAL);
    player.play();
    
    
    receiver.setup(PORT);
    
    


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

    gui.loadFont("MONACO.TTF", 12);
    gui.setup("Settings", 0, 0, ofGetWidth(), ofGetHeight());
    
    gui.setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("General", 4, false);
    gui.setWhichPanel(0);
    gui.setWhichColumn(0);
    gui.addSlider( scene1->coolDown.set("coolDown",0,0,100000));
//    gui.add( Mode.set("Mode",0,0,3));
    gui.addToggle( timePriority.set("Toggle Time Prioirty",false));
    gui.addSlider( maxIdleTime.set("Max Idle(min)",0.5,0,60.0f));
    
    gui.addLabel(fps.set("fps",""));
    gui.addLabel(currentIdleString.set("Idle",""));
    string output = "";
    
    string pointSprites = ((info.bPointSpritesSupported == true) ? "yes" : "no");
    string shaders = ((info.bShadersSupported == true) ? "yes" : "no");
    string vbo = ((info.bVboSupported == true) ? "yes" : "no");
    
    
    output += "opengl version: " + info.version + "\n";
    output += "vendor: " + info.vendor + "\n";
    output += "renderer: " + info.renderer + "\n";
    output += "\n";
    output += "point sprites support: " + pointSprites + "\n";
    output += "shader support: " + shaders + "\n";
    output += "vbo support: " + vbo + "\n";
    output += "\n";
    output += "max texture size: " + ofToString(info.maxTextureSize) + "\n";
    output += "max viewport dimensions: " + ofToString(info.maxDimensions[0]) + "," +  ofToString(info.maxDimensions[1]) + "\n";
    output += "max lights: " + ofToString(info.maxLights) + "\n";
    status = "first frame";
    gui.setStatusMessage(status);
    gui.loadSettings("settings.xml");
    
    sceneManager->setDrawDebug(toggleDrawGUI);
    if(player.isLoaded())
    {
        ofSetWindowShape(player.getWidth(), player.getHeight());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    status = "App running at " + ofToString(ofGetFrameRate());
    player.update();
    gui.update();
    // check for waiting messages

    while(receiver.hasWaitingMessages()){
        // get the next message
        ofParameterGroup p;
        p.setName("cvtracker");
        ofParameter<ofColor>color;
        ofParameter<ofVec2f>v2;
        p.add(color.set("color", ofColor::white));
        p.add(v2.set("contour",ofVec2f::zero()));
        receiver.getParameter(p);
        customeOSCData data;
        data.pos = v2.get();
        data.c = color.get();
        ofNotifyEvent(trackerEvent,data,this);
        
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
    player.draw(0, 0);
    
    
    sceneManager->draw();
    if(toggleDrawGUI)
    {
        ofPushStyle();
        ofPushMatrix();
        gui.draw();
        ofPopMatrix();
        ofPopStyle();
    }
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


