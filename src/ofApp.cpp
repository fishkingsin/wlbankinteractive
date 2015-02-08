#include "ofApp.h"
#define PORT 12345
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
    info.version = (char*)glGetString(GL_VERSION);
    info.vendor = (char*)glGetString(GL_VENDOR);
    info.renderer = (char*)glGetString(GL_RENDERER);
    info.bVboSupported = false;
    info.bShadersSupported = false;
    info.bPointSpritesSupported = false;
    dirVideo.listDir("congrad_movies");
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
    
    
    
    
    receiver.setup(PORT);
    
    
    
    
    commonAssets.loadImage("particleGrid.png",4,4,8);
    commonAssets.setup();
    commonAssets.nextImage();
    
    ///////////////////////////////////////
    
    sceneManager = ofxSceneManager::instance();
    scene1 = new MyScene1();
    scene1->commonAssets = &commonAssets;
    sceneManager->addScene(scene1 , SCENE_1);

    sceneManager->setCurtainTimes(10,10,10);
    ofAddListener(trackerEvent, scene1, &MyScene1::eventsIn);
    ofAddListener(scene1->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    //    MyScene2* scene2 = new MyScene2();
    //    scene2->commonAssets = &commonAssets;
    //    sceneManager->addScene(scene2 , SCENE_2);
    //    ofAddListener(scene2->toNextSceneEvent, this, &ofApp::handleToNextScene);
    //
    //    MyScene3* scene3 = new MyScene3();
    //    scene3->commonAssets = &commonAssets;
    //    sceneManager->addScene(scene3 , SCENE_3);
    //    ofAddListener(scene3->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    MyScene4* scene4 = new MyScene4();
    scene4->commonAssets = &commonAssets;
    sceneManager->addScene(scene4 , SCENE_4);
    ofAddListener(scene4->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    /*MyScene6* scene6 = new MyScene6();
     scene6->commonAssets = &commonAssets;
     sceneManager->addScene(scene6 , SCENE_6);
     ofAddListener(scene6->toNextSceneEvent, this, &ofApp::handleToNextScene);*/
    
    
    //    MyScene7* scene7 = new MyScene7();
    //    scene7->commonAssets = &commonAssets;
    //    sceneManager->addScene(scene7 , SCENE_7);
    //    ofAddListener(scene7->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
    /*    MyScene8* scene8 = new MyScene8();
     scene8->commonAssets = &commonAssets;
     sceneManager->addScene(scene8 , SCENE_8);
     ofAddListener(scene8->toNextSceneEvent, this, &ofApp::handleToNextScene);
     
     LogoScene* logoScene = new LogoScene();
     logoScene->commonAssets = &commonAssets;
     sceneManager->addScene(logoScene , SCENE_LOGO);
     ofAddListener(logoScene->toNextSceneEvent, this, &ofApp::handleToNextScene);*/
    
    //    MySceneLiquidfun *sceneLiquidfun = new MySceneLiquidfun();
    //    sceneLiquidfun->commonAssets = &commonAssets;
    //    sceneManager->addScene(sceneLiquidfun , SCENE_10);
    //    ofAddListener(sceneLiquidfun->toNextSceneEvent, this, &ofApp::handleToNextScene);
    
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
    gui.addPanel("Liquidfun", 4, false)->setBackgroundColor(0, 0, 0, 125);
    gui.setWhichPanel(0);
    gui.setWhichColumn(0);
    gui.addToggle(toggleDrawGUI.set("DEBUG_TOGGLE", true));
    gui.addGroup(commonAssets.paraGroup);
    
    toggleDrawGUI.addListener(this, &ofApp::toggleDebug);
    gui.addToggle(bLogFile.set("ENABLE_LOG_TO_FILE",false));
    bLogFile.addListener( this, &ofApp::enableLogToFile);
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
    gui.setWhichColumn(1);
    
    //    gui.add( Mode.set("Mode",0,0,3));

    gui.addToggle( timePriority.set("Toggle Time Prioirty",false));
    gui.addSlider( maxIdleTime.set("Max Idle(min)",0.5,0,60.0f));
    gui.setWhichColumn(1);
    
    gui.addFileLister("VideoFiles", &videoFileLister, 200, 100);
    int numFile = videoFileLister.listDir("movies");
    if(numFile>0)
    {
        player.loadMovie(videoFileLister.getPath(0));
        player.setLoopState(OF_LOOP_NORMAL);
        player.play();
    }
    else{
        ofLogError() << "0 file in "<< videoFileLister.getOriginalDirectory();
    }
    //    ofAddListener(videoFileLister,this,ofApp::filechanges);
    //scene1
    gui.setWhichPanel(1);
    gui.setWhichColumn(0);
    
    gui.addGroup(scene1->paraGroup);
    //scene2
    //    gui.setWhichPanel(2);
    //    gui.setWhichColumn(0);
    //    gui.addGroup(scene2->paraGroup);
    //
    //    gui.setWhichPanel(3);
    //    gui.setWhichColumn(0);
    //    gui.addGroup(scene3->paraGroup);;
    gui.setWhichPanel(4);
    gui.setWhichColumn(0);
    gui.addGroup(scene4->paraGroup);
    
    /*gui.setWhichPanel(5);
     gui.setWhichColumn(0);
     gui.addGroup(scene6->paraGroup);
     */
    
    
    //    gui.setWhichPanel(7);
    //    gui.setWhichColumn(0);
    //    gui.addGroup(scene7->paraGroup);
    
    /*gui.setWhichPanel(8);
     gui.setWhichColumn(0);
     gui.addGroup(scene8->paraGroup);
     gui.setWhichPanel(9);
     gui.setWhichColumn(0);
     gui.addGroup(logoScene->paraGroup);
     */
    //    gui.setWhichPanel(10);
    //    gui.setWhichColumn(0);
    //    gui.addGroup(sceneLiquidfun->paraGroup);
    
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
    gui.enableEvents();
    ofAddListener(gui.guiEvent, this, &ofApp::eventsIn);
    sceneManager->setDrawDebug(toggleDrawGUI);
    ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);
    
    
}
void ofApp::exit()
{
    ofLogToConsole();
}
void ofApp::eventsIn(guiCallbackData & data){
    // print to terminal if you want to
    //this code prints out the name of the events coming in and all the variables passed
    printf("ofApp::eventsIn - name is %s - \n", data.getXmlName().c_str());
    if( data.getDisplayName() != "" ){
        printf(" element name is %s \n", data.getDisplayName().c_str());
    }
    for(int k = 0; k < data.getNumValues(); k++){
        if( data.getType(k) == CB_VALUE_FLOAT ){
            printf("%i float  value = %f \n", k, data.getFloat(k));
        }
        else if( data.getType(k) == CB_VALUE_INT ){
            printf("%i int    value = %i \n", k, data.getInt(k));
        }
        else if( data.getType(k) == CB_VALUE_STRING ){
            printf("%i string value = %s \n", k, data.getString(k).c_str());
        }
    }
    
    printf("\n");
    
    if( data.getXmlName() == "VIDEOFILES" ){
        player.loadMovie(data.getString(1));
        player.setLoopState(OF_LOOP_NORMAL);
        player.play();
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    
    status = "App running at " + ofToString(ofGetFrameRate());
    if(congradVideo.isLoaded())
    {
        congradVideo.update();
    }
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
    
    ofPushStyle();
    ofSetColor(255,alphaTween.update());
    congradVideo.draw(0,0);
    //    commonAssets.player.draw(0,0);
    //    commonAssets.logo.draw(0,0);
    ofPopStyle();
    if(toggleDrawGUI)
    {
        ofPushStyle();
        ofPushMatrix();
        gui.draw();
        ofPopMatrix();
        ofPopStyle();
    }
    ofPushStyle();
    ofSetColor(0);
    ofRect(commonAssets.blockRectX, commonAssets.blockRectY, commonAssets.blockRectW, commonAssets.blockRectH);
    ofPopStyle();
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
        case '0':
            //            commonAssets.nextImage();
        {
            ofColor cColor = ofColor::fromHsb(ofRandom(360), 255, 255);
            if(curtainColors.size()>0)
            {
                cColor = curtainColors[int(ofRandom(curtainColors.size()))];
            }
            sceneManager->setCurtainColor(cColor.r,cColor.g,cColor.b , 0);
            if (key == '1') sceneManager->goToScene(SCENE_1, true); /* true >> regardless of curtain state (so u can change state while curtain is moving)*/
            if (key == '2') sceneManager->goToScene(SCENE_2);
            if (key == '3') sceneManager->goToScene(SCENE_3);
            if (key == '4') sceneManager->goToScene(SCENE_4);
            //            if (key == '6') sceneManager->goToScene(SCENE_6);
            if (key == '7') sceneManager->goToScene(SCENE_7);
            //            if (key == '8') sceneManager->goToScene(SCENE_8);
            //            if (key == '9') sceneManager->goToScene(SCENE_LOGO);
            if(key == '0')sceneManager->goToScene(SCENE_10);
            
        }
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ' :
            
            toggleDrawGUI = !toggleDrawGUI;
            
            
            break;
        case  's':
            gui.saveSettings();
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
    sceneManager->setCurtainColor(cColor.r,cColor.g,cColor.b , 0);
    
    switch(sceneID)
    {
        case SCENE_1:
            //go to next scene 2-4
        {
            commonAssets.nextImage();
            
            int rand=SCENE_4;
            
            ofLogVerbose () << " rand: " << rand;
            Scenes scene = (Scenes)rand;
            ofLogVerbose () << " scene: " << scene;
            sceneManager->goToScene(scene);
        }
            break;
        case SCENE_2:
        case SCENE_3:
        case SCENE_4:
        case SCENE_7:
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
    
    if(commonAssets.bAuto)
    {
        if(tonextscene.sceneID==1)
        {
            ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);
            ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
            nextScene();
            
        }
        else{
            
            ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);
            ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
            if(congradVideo.loadMovie( dirVideo.getPath(commonAssets.imageIndex) ))
            {
                congradVideo.play();
                congradVideo.setLoopState(OF_LOOP_PALINDROME);
            }
            nextScene();
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
    if(commonAssets.bAuto)
    {
        ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEnd);
        alphaTween.setParameters(0,easingeLinear,ofxTween::easeIn,255,0,1000,congradVideo.getDuration()*1000);
        ofAddListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
    }
    else{
        ofLogWarning() << "Auto mode off has scene incoming";
    }
}

void ofApp::tweenEasingOutEnd(int &i)
{
    if(commonAssets.bAuto)
    {
        
        congradVideo.stop();
        
        ofRemoveListener(alphaTween.end_E, this, &ofApp::tweenEasingOutEnd);
        
    }
    else{
        ofLogWarning() << "Auto mode off has scene incoming";
    }
    
}
void ofApp::enableLogToFile(bool &b)
{
    ofLogToFile(ofGetTimestampString()+".txt", b);
}