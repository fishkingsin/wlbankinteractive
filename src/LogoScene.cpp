//
//  LogoScene.cpp
//  wlbankinteractive
//
//  Created by James Kong on 17/1/15.
//
//

#include "LogoScene.h"
void LogoScene::setup(){
    
}
void LogoScene::init(){
    logo = commonAssets->logo;
}
void LogoScene::update(float dt){
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