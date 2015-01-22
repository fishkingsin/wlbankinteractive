#include "ofApp.h"
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
    glDisable(GL_DEPTH_TEST);
    
    settings.load("config.xml");
    if(settings.pushTag("XML"))
    {
        if (settings.pushTag("CURTAIN_COLORS")) {
            int nTags = settings.getNumTags("COLOR");
            for(int i = 0 ; i < nTags ; i++)
            {
                if(settings.pushTag("COLOR",i))
                {
                    ofColor c(settings.getValue("R", 255),settings.getValue("G", 255),settings.getValue("B", 255));
                    curtainColors.push_back(c);
                    settings.popTag();
                    
                }
                
            }
            settings.popTag();
        }
        if(settings.pushTag("SHAPE"))
        {
            ofSetWindowShape(settings.getValue("WIDTH", 422), settings.getValue("HEIGHT", 480));
            settings.popTag();
        }
        if(settings.pushTag("POSITION"))
        {
            ofSetWindowPosition(settings.getValue("X", 0), settings.getValue("Y", 0));
            settings.popTag();
        }
        settings.popTag();
    }
    for(int i = 0  ; i < curtainColors.size(); i++)
    {
        ofLogVerbose() << curtainColors[i];
    }
    
    player.loadMovie("movies/CNY theme.mov");
    player.setLoopState(OF_LOOP_NORMAL);
    player.play();
    
    
    receiver.setup(PORT);
    
    


    commonAssets.loadImage("particleGrid.png",4,4,8);
    commonAssets.setup();
    commonAssets.nextImage();
    ///////////////////////////////////////
    
    sceneManager = ofxSceneManager::instance();
    scene1 = new MyScene1();
    scene1->commonAssets = &commonAssets;
    sceneManager->addScene(scene1 , SCENE_1);
    ofAddListener(trackerEvent, scene1, &MyScene1::eventsIn);
    ofAddListener(scene1->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    MyScene2* scene2 = new MyScene2();
    scene2->commonAssets = &commonAssets;
    sceneManager->addScene(scene2 , SCENE_2);
    ofAddListener(scene2->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    MyScene3* scene3 = new MyScene3();
    scene3->commonAssets = &commonAssets;
    sceneManager->addScene(scene3 , SCENE_3);
    ofAddListener(scene3->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    MyScene4* scene4 = new MyScene4();
    scene4->commonAssets = &commonAssets;
    sceneManager->addScene(scene4 , SCENE_4);
    ofAddListener(scene4->toNextSceneEvent, this, &ofApp::handleToNextScene);

    /*MyScene6* scene6 = new MyScene6();
    scene6->commonAssets = &commonAssets;
    sceneManager->addScene(scene6 , SCENE_6);
    ofAddListener(scene6->toNextSceneEvent, this, &ofApp::handleToNextScene);

    
    MyScene7* scene7 = new MyScene7();
    scene7->commonAssets = &commonAssets;
    sceneManager->addScene(scene7 , SCENE_7);
    ofAddListener(scene7->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    MyScene8* scene8 = new MyScene8();
    scene8->commonAssets = &commonAssets;
    sceneManager->addScene(scene8 , SCENE_8);
    ofAddListener(scene8->toNextSceneEvent, this, &ofApp::handleToNextScene);

    LogoScene* logoScene = new LogoScene();
    logoScene->commonAssets = &commonAssets;
    sceneManager->addScene(logoScene , SCENE_LOGO);
    ofAddListener(logoScene->toNextSceneEvent, this, &ofApp::handleToNextScene);*/
    
    sceneManager->setDrawDebug(true);
    sceneManager->setCurtainDropTime(1.0);
    sceneManager->setCurtainStayTime(0.0);
    sceneManager->setCurtainRiseTime(1.0);
    sceneManager->setOverlapUpdate(true);
    
    gui.setBackgroundColor(0, 0, 0, 125);

    gui.loadFont("MONACO.TTF", 12);
    gui.setup("Settings", CANVAS_WIDTH, 0, ofGetWidth(), ofGetHeight());
    
    gui.addPanel("Scene1", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene2", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene3", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene4", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene5", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene6", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene7", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene8", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("SceneLogo", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.setWhichPanel(0);
    gui.setWhichColumn(0);
    gui.addToggle(toggleDrawGUI.set("DEBUG_TOGGLE", true));

    toggleDrawGUI.addListener(this, &ofApp::toggleDebug);

    gui.addLabel(fps.set("fps",""));
    gui.addLabel(currentIdleString.set("Idle",""));
    gui.addLabel("USAGE:\n\
                 1-5 :changing Scene\n\
                 right arrow:next scene\n\
                 space:toggle panel\n\
                 scene1 : 'b' :fire particle\n\
                 ");
    gui.addSlider(commonAssets.elementCenterX.set("COMMON_CENER_X",CANVAS_WIDTH*0.5,0,CANVAS_WIDTH));
    gui.addSlider(commonAssets.elementCenterY.set("COMMON_CENER_Y",CANVAS_HEIGHT*0.5,0,CANVAS_HEIGHT));
    gui.addSlider( scene1->coolDown.set("coolDown",0,0,100000));
//    gui.add( Mode.set("Mode",0,0,3));
    gui.addToggle( bAuto.set("AUTO_MODE",false));
    gui.addToggle( timePriority.set("Toggle Time Prioirty",false));
    gui.addSlider( maxIdleTime.set("Max Idle(min)",0.5,0,60.0f));
    
    //scene1
    gui.setWhichPanel(1);
    gui.setWhichColumn(0);
    gui.addLabel(scene1->numParticle.set("PARTICLE_SIZE",""));
    gui.addSlider(scene1->maxParticle.set("S1_MAX_PARTICLE",3000,1,10000));
    gui.addSlider(scene1->minRadius.set("S1_MIN_RADIUS",8,1,50));
    gui.addSlider(scene1->maxRadius.set("S1_MAX_RADIUS",20,1,50));
    //scene2
    gui.setWhichPanel(2);
    gui.setWhichColumn(0);
    gui.addSlider(scene2->maxParitcle.set("S2_MAX_PARTICLE",3000,1,10000));
    gui.addSlider(scene2->minRadius.set("S2_MIN_RADIUS",8,1,50));
    gui.addSlider(scene2->maxRadius.set("S2_MAX_RADIUS",20,1,50));
    gui.addLabel(scene2->counterString.set("S2_COUNTER",""));
    gui.addSlider(scene2->timeOut.set("S2_TIME_OUT",5,0,20));
    gui.setWhichPanel(3);
    gui.setWhichColumn(0);
    gui.addSlider(scene3->minRadius.set("S3_MIN_RADIUS", 8,1,50));
    gui.addSlider(scene3->maxRadius.set("S3_MAX_RADIUS", 20,1,50));
    
    gui.setWhichPanel(4);
    gui.setWhichColumn(0);
    gui.addSlider(scene4->maxParitcle.set("S4_MAX_PARTICLE",400,1,1000));
//    gui.addSlider(scene4->initX.set("INIT_X",CANVAS_WIDTH*0.5,0,CANVAS_WIDTH));
//    gui.addSlider(scene4->initY.set("INIT_Y",CANVAS_HEIGHT*0.5,0,CANVAS_HEIGHT));
    gui.addSlider(scene4->minRadius.set("S4_MIN_RADIUS",8,1,50));
    gui.addSlider(scene4->maxRadius.set("S4_MAX_RADIUS",20,1,50));
    gui.addToggle(scene4->debugDraw.set("DEBUG_DRAW",false));
    gui.addSlider(scene4->timeOut.set("S4_TIME_OUT",5,0,20));
    gui.addLabel(scene4->counterString.set("S4_COUNTER",""));
    
    /*gui.setWhichPanel(5);
    gui.setWhichColumn(0);
    gui.addSlider(scene6->maxParitcle.set("S6_MAX_PARTICLE",3000,1,10000));
    gui.addSlider(scene6->minRadius.set("S6_MIN_RADIUS", 8,1,50));
    gui.addSlider(scene6->maxRadius.set("S6_MAX_RADIUS", 20,1,50));
    gui.addSlider(scene6->maxR.set("S6_MAX_R",CANVAS_WIDTH*0.5, 0,CANVAS_WIDTH));
    gui.addSlider(scene6->maxOutterR.set("S6_MAX_OUTTER_R", CANVAS_WIDTH*2,0,CANVAS_WIDTH*5));
    gui.addSlider(scene6->delay.set("S6_DELAY", 1, 0,20));
    gui.addSlider(scene6->duration.set("S6_DURATION", 1000,1,50000));
    gui.addSlider(scene6->theStep.set("S6_STEP", 1,1.0f,1000));
    gui.addSlider(scene6->minStep.set("S6_MIN_STEP", 1,1.0f,1000));
    gui.addSlider(scene6->maxStep.set("S6_MAX_STEP", 1,1.0f,1000));

    gui.addToggle(scene6->bDebug.set("S6_DEBUG",false));

    
    gui.setWhichPanel(7);
    gui.setWhichColumn(0);
    gui.addSlider(scene7->maxParitcle.set("S7_MAX_PARTICLE",3000,1,10000));
    gui.addSlider(scene7->minRadius.set("S7_MIN_RADIUS", 8,1,50));
    gui.addSlider(scene7->maxRadius.set("S7_MAX_RADIUS", 20,1,50));
    gui.addSlider(scene7->maxR.set("S7_MAX_R",CANVAS_WIDTH*0.5, 0,CANVAS_WIDTH));
    gui.addSlider(scene7->maxOutterR.set("S7_MAX_OUTTER_R", CANVAS_WIDTH*2,0,CANVAS_WIDTH*5));
    gui.addSlider(scene7->delay.set("S7_DELAY", 1, 0,20));
    gui.addSlider(scene7->duration.set("S7_DURATION", 1000,1,50000));
    gui.addSlider(scene7->theStep.set("S7_STEP", 1,50.0f,100));
    gui.addSlider(scene7->minStep.set("S7_MIN_STEP", 1,0.0f,100));
    gui.addSlider(scene7->maxStep.set("S7_MAX_STEP", 50,0.0f,100));
    gui.addSlider(scene7->minDelay.set("S7_MIN_DELAY", 0,0.0f,100));
    gui.addSlider(scene7->maxDelay.set("S7_MAX_DELAY", 50,0.0f,100));
    
    gui.addToggle(scene7->bDebug.set("S7_DEBUG",false));
    
    gui.setWhichPanel(8);
    gui.setWhichColumn(0);
    gui.addSlider(scene8->timeOut.set("S8_TIME_OUT",5,0,20));
    gui.addLabel(scene8->counterString.set("S8_COUNTER",""));
    
    gui.setWhichPanel(9);
    gui.setWhichColumn(0);
    gui.addSlider(logoScene->timeOut.set("SLOGO_TIME_OUT",5,0,20));
    gui.addLabel(logoScene->counterString.set("SLOGO_COUNTER",""));*/

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
    gui.setStatusMessage(status.set("glStatus",output));
    gui.loadSettings("settings.xml");
    
    sceneManager->setDrawDebug(toggleDrawGUI);
//    if(player.isLoaded())
//    {
//        ofSetWindowShape(player.getWidth(), player.getHeight());
//    }
    ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);

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
            nextScene();
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
    if(sceneManager->getCurrentSceneID()!=SCENE_1)
    {
        ofPushStyle();
        ofSetColor(255,alphaTween.update());
        commonAssets.logo.draw(0,0);
        ofPopStyle();
    }
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
    switch (key)
    {
        case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
           case '7':
           case '8':
//            commonAssets.nextImage();
        {
            ofColor cColor = ofColor::fromHsb(ofRandom(360), 255, 255);
            if(curtainColors.size()>0)
            {
                cColor = curtainColors[int(ofRandom(curtainColors.size()))];
            }
            sceneManager->setCurtainColor(cColor.r,cColor.g,cColor.b);
            if (key == '1') sceneManager->goToScene(SCENE_1, true); /* true >> regardless of curtain state (so u can change state while curtain is moving)*/
            if (key == '2') sceneManager->goToScene(SCENE_2);
            if (key == '3') sceneManager->goToScene(SCENE_3);
            if (key == '4') sceneManager->goToScene(SCENE_4);
//            if (key == '6') sceneManager->goToScene(SCENE_6);
//            if (key == '7') sceneManager->goToScene(SCENE_7);
//            if (key == '8') sceneManager->goToScene(SCENE_8);
//            if (key == '9') sceneManager->goToScene(SCENE_LOGO);

        }
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ' :
            
            toggleDrawGUI = !toggleDrawGUI;
            
            
            break;
        case OF_KEY_RIGHT:
            nextScene();
            break;
        default:
            sceneManager->keyPressed(key);
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


void ofApp::toggleDebug(bool& _value)
{
    if(_value)
    {
        ofShowCursor();
        ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else
    {
        ofHideCursor();
        ofSetLogLevel(OF_LOG_SILENT);
    }
    sceneManager->setDrawDebug(toggleDrawGUI);
}
void ofApp::nextScene()
{
    int sceneID = sceneManager->getCurrentSceneID();
    ofColor cColor = ofColor::fromHsb(ofRandom(360), 255, 255);
    if(curtainColors.size()>0)
    {
        cColor = curtainColors[int(ofRandom(curtainColors.size()))];
    }
    sceneManager->setCurtainColor(cColor.r,cColor.g,cColor.b);

    switch(sceneID)
    {
        case SCENE_1:
            //go to next scene 2-4
        {
            commonAssets.nextImage();
            float rand = ofRandom(SCENE_2,SCENE_4+1);
            ofLogVerbose () << " rand: " << rand;
            Scenes scene = (Scenes)rand;
            ofLogVerbose () << " scene: " << scene;
            sceneManager->goToScene(scene);
        }
            break;
        case SCENE_2:
        case SCENE_3:
        case SCENE_4:
//        case SCENE_7:
//        case SCENE_6:
//        case SCENE_8:

            sceneManager->goToScene(SCENE_1);
            break;
//        case SCENE_LOGO:
//            //loop back
//            sceneManager->goToScene(SCENE_1);
//            break;
            
    }
}
void ofApp::handleToNextScene(toNextScene &tonextscene)
{
    
    if(bAuto)
    {
        if(tonextscene.sceneID==1)
        {
            ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);
            ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
            nextScene();

        }
        else{
            
            alphaTween.setParameters(0,easingeLinear,ofxTween::easeIn,0,255,1000,0);
            ofAddListener(alphaTween.end_E, this, &ofApp::tweenEnd);
        }
        
    }
    else{
        ofLogWarning() << "Auto mode off has scene incoming";
    }
}

void ofApp::tweenEnd(int &i)
{
    if(bAuto)
    {
        ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);

        alphaTween.setParameters(0,easingeLinear,ofxTween::easeOut,255,0,1000,1000);
        ofAddListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
    }
    else{
        ofLogWarning() << "Auto mode off has scene incoming";
    }
}

void ofApp::tweenEasingOutEnd(int &i)
{
    if(bAuto)
    {
        ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
        nextScene();
    }
    else{
        ofLogWarning() << "Auto mode off has scene incoming";
    }

}