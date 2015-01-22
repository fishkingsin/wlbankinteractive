//
//  MyScene8.cpp
//  wlbankinteractive
//
//  Created by James Kong on 19/1/15.
//
//

#include "MyScene8.h"
//--------------------------------------------------------------
void MyScene8::setup(){
    fbo.allocate(CANVAS_WIDTH, CANVAS_HEIGHT,GL_RGBA);
}
void MyScene8::init()
{
    prevElapse = ofGetElapsedTimef();
    counter = 0;

    fbo.begin();
    ofClear(0, 0, 0,0);
    fbo.end();
    img = commonAssets->bg;
    isStart = false;
}
//--------------------------------------------------------------
void MyScene8::update(float dt){
    if(isStart)
    {
    for (int i=0; i<particles.size(); i++) {
        particles[i].update();
    }
    ofSetColor(255);
    
    fbo.begin();

    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);

    for (int i=0; i<particles.size(); i++) {
        CircularParticle &p = particles[i];
        p.draw();
    }
    fbo.end();
    
    for (int i=0; i<40; i++) {
        createParticle();
    }
    
    while (particles.size()>1000) {
        particles.erase(particles.begin());
    }
    if(counter<timeOut.get())
    {
        
        counter+=ofGetElapsedTimef()-prevElapse;
    }
    else{
        ofLogVerbose() << "counter : " << counter;
        toNextScene tonextScene;
        ofNotifyEvent(toNextSceneEvent, tonextScene, this);
        counter=0;
    }
    counterString = ofToString(counter);
    prevElapse = ofGetElapsedTimef();
    }
}

//--------------------------------------------------------------
void MyScene8::draw(){
    fbo.draw(0,0);

    
}

void MyScene8::createParticle() {
    CircularParticle p;
    p.setup();
    p.pos.set(ofRandom(img.getWidth()), ofRandom(img.getHeight()));

    p.color = img.getColor(p.pos.x,p.pos.y);
    particles.push_back(p);

}

//--------------------------------------------------------------
void MyScene8::keyPressed(int key){
}
void MyScene8::sceneWillAppear( ofxScene * fromScreen )
{
    init();
}
void MyScene8::sceneWillDisappear( ofxScene * toScreen )
{
    
}
void MyScene8::sceneDidAppear()
{
    isStart = true;
}
void MyScene8::sceneDidDisappear(ofxScene *fromScreen)
{
    particles.clear();
}
