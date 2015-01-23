//
//  LogoScene.cpp
//  wlbankinteractive
//
//  Created by James Kong on 17/1/15.
//
//

#include "LogoScene.h"
void LogoScene::setup(){
    paraGroup.setName("LogoScene");
    paraGroup.add(timeOut.set("SLOGO_TIME_OUT",5,0,20));
    paraGroup.add(counterString.set("SLOGO_COUNTER",""));
}
void LogoScene::init(){
        prevElapse = ofGetElapsedTimef();
    logo = commonAssets->logo;
    counter = 0;
}
void LogoScene::update(float dt){
    if(counter<timeOut.get())
    {
        counter+=ofGetElapsedTimef()-prevElapse;
    }
    else{
        toNextScene tonextScene;
        ofNotifyEvent(toNextSceneEvent, tonextScene, this);
        counter=0;
    }
    counterString = ofToString(counter);
    prevElapse = ofGetElapsedTimef();
}
void LogoScene::draw(){
    logo.draw(0,0);
}
void LogoScene::keyPressed(int key){
}
void LogoScene::mousePressed( int x, int y, int button ){
}    //scene notifications
void LogoScene::sceneWillAppear( ofxScene * fromScreen ){

    init();
}
//scene notifications
void LogoScene::sceneWillDisappear( ofxScene * toScreen ){
}
void LogoScene::sceneDidAppear(){
}
void LogoScene::sceneDidDisappear(ofxScene *fromScreen){
}