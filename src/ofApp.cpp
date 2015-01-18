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
    
    MyScene2* scene2 = new MyScene2();
    scene2->commonAssets = &commonAssets;
    sceneManager->addScene(scene2 , SCENE_2);
    
    MyScene3* scene3 = new MyScene3();
    scene3->commonAssets = &commonAssets;
    sceneManager->addScene(scene3 , SCENE_3);

    MyScene4* scene4 = new MyScene4();
    scene4->commonAssets = &commonAssets;
    sceneManager->addScene(scene4 , SCENE_4);
    
    LogoScene* logoScene = new LogoScene();
    logoScene->commonAssets = &commonAssets;
    sceneManager->addScene(logoScene , SCENE_LOGO);

    sceneManager->setDrawDebug(true);
    sceneManager->setCurtainDropTime(1.0);
    sceneManager->setCurtainStayTime(0.0);
    sceneManager->setCurtainRiseTime(1.0);
    sceneManager->setOverlapUpdate(true);

    gui.loadFont("MONACO.TTF", 12);
    gui.setup("Settings", CANVAS_WIDTH, 0, ofGetWidth(), ofGetHeight());
    
    gui.setBackgroundColor(0, 0, 0, 125);

    gui.addPanel("Scene1", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene2", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene3", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.addPanel("Scene4", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.setWhichPanel(0);
    gui.setWhichColumn(0);
    gui.addToggle(toggleDrawGUI.set("DEBUG_TOGGLE", true));

    toggleDrawGUI.addListener(this, &ofApp::toggleDebug);

    gui.addLabel(fps.set("fps",""));
    gui.addLabel(currentIdleString.set("Idle",""));

    gui.addSlider( scene1->coolDown.set("coolDown",0,0,100000));
//    gui.add( Mode.set("Mode",0,0,3));
    gui.addToggle( bAuto.set("audo",false));
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
    gui.addSlider(scene2->minRadius.set("S2_MIN_RADIUS", 8,1,50));
    gui.addSlider(scene2->maxRadius.set("S2_MAX_RADIUS", 20,1,50));
    
    gui.setWhichPanel(3);
    gui.setWhichColumn(0);
    gui.addSlider(scene3->minRadius.set("S3_MIN_RADIUS", 8,1,50));
    gui.addSlider(scene3->maxRadius.set("S3_MAX_RADIUS", 20,1,50));
    
    gui.setWhichPanel(4);
    gui.setWhichColumn(0);
    gui.addSlider(scene4->maxParitcle.set("S4_MAX_PARTICLE",400,1,1000));
    gui.addSlider(scene4->initX.set("INIT_X",CANVAS_WIDTH*0.5,0,CANVAS_WIDTH));
    gui.addSlider(scene4->initY.set("INIT_Y",CANVAS_HEIGHT*0.5,0,CANVAS_HEIGHT));
    gui.addSlider(scene4->minRadius.set("S4_MIN_RADIUS",8,1,50));
    gui.addSlider(scene4->maxRadius.set("S4_MAX_RADIUS",20,1,50));
    gui.addToggle(scene4->debugDraw.set("DEBUG_DRAW",false));
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
//    if(player.isLoaded())
//    {
//        ofSetWindowShape(player.getWidth(), player.getHeight());
//    }
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
            commonAssets.nextImage();
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
            float rand = ofRandom(SCENE_2,SCENE_LOGO);
            ofLogVerbose () << " rand: " << rand;
            Scenes scene = (Scenes)rand;
            ofLogVerbose () << " scene: " << scene;
            sceneManager->goToScene(scene);
        }
            break;
        case SCENE_2:
        case SCENE_3:
        case SCENE_4:

            sceneManager->goToScene(SCENE_LOGO);
            break;
        case SCENE_LOGO:
            //loop back
            sceneManager->goToScene(SCENE_1);
            break;
            
    }
}