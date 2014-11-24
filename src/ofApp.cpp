#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    
    box2d.init();
    box2d.setGravity(0, -50);
    box2d.createBounds();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    fbo.allocate(VIDEO_WIDTH,VIDEO_HEIGHT,GL_RGB);
    pixels.allocate(VIDEO_WIDTH,VIDEO_HEIGHT,OF_IMAGE_COLOR);
    
    grabber.setDesiredFrameRate(60);
    grabber.initGrabber(VIDEO_WIDTH,VIDEO_HEIGHT);
    
    opticalFlow.setup(ofRectangle(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT));
    cvImage.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    grayImage.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    opticalFlow.setOpticalFlowSize(14);
    opticalFlow.setOpticalFlowBlur(14);
    
    
    grayBg.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
    grayDiff.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
    threshold = 80;
    gui.setup("Settings");
    gui.add(threshold.set("threashold",80,1,255));
    gui.add( minArea.set("minArea",20,(VIDEO_WIDTH*VIDEO_HEIGHT)/3,VIDEO_WIDTH*VIDEO_HEIGHT));
    gui.add( maxArea.set("maxArea",80,(VIDEO_WIDTH*VIDEO_HEIGHT)/3,VIDEO_WIDTH*VIDEO_HEIGHT));
    gui.add( nConsidered.set("nConsidered",10,1,100));
    gui.add( bFindHoles.set("bFindHoles",true));
    gui.add( bUseApproximation.set("bUseApproximation",true));
    gui.add( debugDraw1.set("debugDraw1",false));
    gui.add( debugDraw2.set("debugDraw2",false));
    gui.add( debugDraw3.set("debugDraw3",false));
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    while(circles.size()>500)
    {
        circles.erase(circles.begin());
        
    }
    if(maxArea<minArea)
    {
        maxArea = minArea;
    }
    
    box2d.update();
    bool bNewFrame = false;
    grabber.update();
    bNewFrame = grabber.isFrameNew();
    float scale = (1.0f*ofGetWidth())/VIDEO_WIDTH;
    if (bNewFrame){
        opticalFlow.update(grabber);
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
        //        cvImage.setFromPixels(grabber.getPixels(), VIDEO_WIDTH ,VIDEO_HEIGHT);
        cvImage.setFromPixels(pixels.getPixels(), VIDEO_WIDTH ,VIDEO_HEIGHT);
        grayImage = cvImage;
        
        //        grayImage.blurHeavily();
        
        
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayDiff, 20, (VIDEO_WIDTH*VIDEO_HEIGHT)/3, 10, true);	// find holes
        
        grayBg = grayImage;
    }
    for (int i = 0; i < contourFinder.nBlobs; i++){
        
        //        contourFinder.blobs[i].draw(0,0);
        
        // draw over the centroid if the blob is a hole
        ofSetColor(255);
        circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
        float r = ofRandom(4, 20);
        
        
        circles.back().get()->setPhysics(3.0, 0.53, 0.1);
        circles.back().get()->setup(box2d.getWorld(), contourFinder.blobs[i].boundingRect.getCenter().x *scale,
                                    contourFinder.blobs[i].boundingRect.getCenter().y*scale, r);
        circles.back().get()->setupTheCustomData(grabber.getPixelsRef().getColor(contourFinder.blobs[i].boundingRect.getCenter().x, contourFinder.blobs[i].boundingRect.getCenter().y));
        
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    if(debugDraw1)
    {
        cvImage.draw(0,0,ofGetWidth(),ofGetHeight());
    }
    if(debugDraw2)
    {
        //    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
        opticalFlow.draw(ofGetWidth(),ofGetHeight());
    }
    if(debugDraw3)
    {
        grayImage.draw(20,20,160,120);
        grayBg.draw(180,20,160,120);
        grayDiff.draw(20,180,160,120);
        grabber.draw(180, 160, 160, 120);
        
        ofPushStyle();
        ofSetHexColor(0xffffff);
        
        // we could draw the whole contour finder
        contourFinder.draw(0,0,ofGetWidth(),ofGetHeight());
        
        
    }
    ofPopStyle();
    ofPushStyle();
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0xf6c738);
        circles[i].get()->draw();
    }
    
    // draw the ground
    box2d.drawGround();
    ofPopStyle();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'c':
            float r = ofRandom(4, 20);
            circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
            
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
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
