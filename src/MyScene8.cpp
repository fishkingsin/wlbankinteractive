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
}
//--------------------------------------------------------------
void MyScene8::update(float dt){
    
    for (int i=0; i<particles.size(); i++) {
        particles[i].update();
    }
    ofSetColor(255);
    
    fbo.begin();
    for (int i=0; i<particles.size(); i++) {
        CircularParticle &p = particles[i];
        p.draw();
    }
    fbo.end();
    
    for (int i=0; i<80; i++) {
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

//--------------------------------------------------------------
void MyScene8::draw(){
    
    fbo.draw(0,0);
}

void MyScene8::createParticle() {
    CircularParticle p;
    p.setup();
    p.pos.set(ofRandomWidth(), ofRandomHeight());
    if(p.pos.x >0 && p.pos.x < img.width && p.pos.y > 0 && p.pos.y < img.height)
    {
        p.color = img.getColor(p.pos.x,p.pos.y);
    }
    else{
        p.color.set(255,255,255,0);
    }
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
    
}
void MyScene8::sceneDidDisappear(ofxScene *fromScreen)
{
    particles.clear();
}
