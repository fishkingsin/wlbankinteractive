#include "ofApp.h"
#include "MyScene2.h"
#include "MyScene3.h"
#include "MyScene4.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofDisableArbTex();
    ofSetLogLevel(OF_LOG_VERBOSE);

    grabberManager.setup();
    
    
    
    fbo.allocate(VIDEO_WIDTH,VIDEO_HEIGHT,GL_RGB);
    pixels.allocate(VIDEO_WIDTH,VIDEO_HEIGHT,OF_IMAGE_COLOR);
    
    
    
    opticalFlow.setup(ofRectangle(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT));
    cvImage.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    grayImage.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    opticalFlow.setOpticalFlowSize(14);
    opticalFlow.setOpticalFlowBlur(14);
    grayBg.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
    grayDiff.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
    threshold = 80;

    commonAssets.loadImage("particleGrid.png",4,4,8);
    commonAssets.setup();
    ///////////////////////////////////////
    
    sceneManager = ofxSceneManager::instance();
    scene1 = new MyScene1();
//    scene1->grabber = &grabber;
    scene1->contourFinder = &contourFinder;
    sceneManager->addScene(scene1 , SCENE_1);
    
    
    
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
//   sceneManager->goToScene(SCENE_2);
//    int step = 10;
//    for(int y = 0 ;y < VIDEO_HEIGHT ; y+=step )
//    {
//        for(int x = 0 ;x < VIDEO_WIDTH ; x+=step )
//        {
//            points.push_back(ofPtr<FlowPoint>(new FlowPoint));
//            points.back().
//            get()->setPosition(ofPoint(x,y));
//            points.back().get()->setup();
//        }
//    }
    
    gui.setup("Settings");
    gui.add(threshold.set("threashold",80,1,255));
    gui.add( minArea.set("minArea",20,20,VIDEO_WIDTH*VIDEO_HEIGHT));
    gui.add( maxArea.set("maxArea",80,20,VIDEO_WIDTH*VIDEO_HEIGHT));
    gui.add( nConsidered.set("nConsidered",10,1,100));
    gui.add( bFindHoles.set("bFindHoles",true));
    gui.add( bUseApproximation.set("bUseApproximation",true));
    gui.add( bBlur.set("bBlur",true));
    gui.add( debugDraw1.set("debugDraw1",false));
    gui.add( debugDraw2.set("debugDraw2",false));
    gui.add( debugDraw3.set("debugDraw3",false));
    gui.add( scene1->coolDown.set("coolDown",0,0,100000));
//    gui.add( Mode.set("Mode",0,0,3));
    gui.add( timePriority.set("Toggle Time Prioirty",false));
    gui.add( maxIdleTime.set("Mac Idle(min)",0.5,0,60.0f));
    
    gui.add(fps.set("fps",""));
    gui.add(currentIdleString.set("Idle",""));
    gui.loadFromFile("settings.xml");
    
    sceneManager->setDrawDebug(toggleDrawGUI);
    
}

//--------------------------------------------------------------
void ofApp::update(){
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
    if(maxArea<minArea)
    {
        maxArea = minArea;
    }
    
    grabberManager.update();
    
    float dt = 0.016666666;
    if(sceneManager->getCurrentSceneID()==SCENE_1)
    {

        
        
        bool bNewFrame = true;//grabber.isFrameNew();
        float scale = (1.0f*ofGetWidth())/VIDEO_WIDTH;
        if (bNewFrame){
//            opticalFlow.update(grabber);
            fbo.begin();
            ofPushStyle();
            ofSetColor(0);
            ofFill();
            ofRect(0, 0, VIDEO_WIDTH,VIDEO_HEIGHT);
            ofPopStyle();
            ofSetColor(255);
            opticalFlow.draw(VIDEO_WIDTH,VIDEO_HEIGHT);
            fbo.end();
            fbo.readToPixels(pixels);
            //        cvImage.setFromPixels(grabber->getPixels(), VIDEO_WIDTH ,VIDEO_HEIGHT);
            cvImage.setFromPixels(pixels.getPixels(), VIDEO_WIDTH ,VIDEO_HEIGHT);
            grayImage = cvImage;
            
            if(bBlur)grayImage.blur();
            
            
            
            
            // take the abs value of the difference between background and incoming and then threshold:
            grayDiff.absDiff(grayBg, grayImage);
            grayDiff.threshold(threshold);
            
            // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
            // also, find holes is set to true so we will get interior contours as well....
            contourFinder.findContours(grayImage,
                                       minArea,
                                       maxArea,
                                       nConsidered,
                                       bFindHoles,
                                       bUseApproximation);	// find holes
            
            grayBg = grayImage;
        }
    }
    sceneManager->update( dt );
    
//    switch(Mode)
//    {
//        case 0:
//        {
//            
//        }
//            break;
//        case 1:
//        {
//            float dt = 1.0f / ofGetFrameRate();
//            for(int i=0; i<points.size(); i++) {
//                points[i].get()->update(dt);
//            }
//        }
//            break;
//        case 2:
//        {
////            mioFlow.update(grabber.getTextureReference());
//        }
//            break;
//        case 3:
//        {
//            
//        }
//            break;
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    grabberManager.videoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    sceneManager->draw();
    
    if(debugDraw1)
    {
        grabberManager.draw();
    }
//    switch(Mode)
//    {
//        case 0:
//        {
//            
//        }
//            break;
//        case 1:
//        {
//            for(int i=0; i<points.size(); i++) {
//                points[i].get()->draw();
//            }
//        }
//            break;
//        case 2:
////            mioFlow.getFlowBlurTexture().draw(0,0);
//            
//            break;
//        case 3:
//            break;
//    }
    
    if(debugDraw2)
    {
        ofSetColor(255);
        //    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
        opticalFlow.draw(ofGetWidth(),ofGetHeight());
    }
    if(debugDraw3)
    {
        ofSetColor(255);
        grayImage.draw(20,20,160,120);
        grayBg.draw(180,20,160,120);
        grayDiff.draw(20,180,160,120);
//        grabber.draw(180, 160, 160, 120);
        
        ofPushStyle();
        ofSetHexColor(0xffffff);
        
        // we could draw the whole contour finder
        contourFinder.draw(0,0,ofGetWidth(),ofGetHeight());
        
        
    }
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


