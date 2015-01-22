//
//  MyScene2.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 8/12/14.
//
//

#include "MyScene2.h"

void MyScene2::setup()
{
    counter = 0 ;
    ofBackground(99);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.setFPS(30.0);

    
    ofBackground(0, 0, 0);
    
    isStart = false;
}
//--------------------------------------------------------------------------------------------
void MyScene2::init()
{
    commonAssets->fbo.begin();
    ofClear(0,0,0,0);
    commonAssets->fbo.end();
    
    commonAssets->srcFbo.begin();
    ofClear(0,0,0,0);
    commonAssets->srcFbo.end();
    counter = 0 ;
//    commonAssets->bg.loadImage("backgrounds/logo03-01.png");
//    commonAssets->logo.loadImage("logos/logo03-01.png");
    image = commonAssets->bg;
//    ofDirectory *dir = &commonAssets->dir;
//    image.loadImage(dir->getFile(((int)ofRandom(dir->getFiles().size()-1))));
    float padding = 256;
    float maxVelocity = 0;
    
    int n = maxParitcle.get();
    int maxR = ((CANVAS_WIDTH>CANVAS_HEIGHT)?CANVAS_WIDTH:CANVAS_HEIGHT)*2;
    
    for(int i = 0; i <n ; i++) {
        
        float x,y,xv,yv;
        float randomPI = ofRandom(-PI,PI);
        x = (sin(randomPI)*maxR)+(sin(randomPI)*ofRandom(padding))+commonAssets->elementCenterX.get();
        y = (cos(randomPI)*maxR)+(cos(randomPI)*ofRandom(padding))+commonAssets->elementCenterY.get();
        float min = minRadius.get();
        float max = maxRadius.get();
        float r = ofRandom(min ,max);
        xv = ofRandom(-maxVelocity, maxVelocity);
        yv = ofRandom(-maxVelocity, maxVelocity);
        ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        circle.get()->setPhysics(100, 0.0, 150);
        circle.get()->setup(box2d.getWorld(), x, y , r);
        circles.push_back(circle);
//        ((maxRadius.get()-r)/maxRadius.get())*255
        float angle = (int)(352+ofRandom(-8,45))%360;
        commonAssets->setParticleColor(i, ofColor::fromHsb(angle, ofRandom(0.60,0.88)*255, ofRandom(0.6,1.0)*255,255));
//        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255,ofMap(r, minRadius.get(), maxRadius.get() , 255, 100)));
        commonAssets->setParticleNormal(i,ofVec3f(r*ofRandom(1,2),0,0));
        int col = (int)ofRandom(0, commonAssets->cellColls );
        int row = (int)ofRandom(0, commonAssets->cellRows);
        commonAssets->setParticleTexCoords(i,col,row );
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
        //        commonAssets->angle[i] = PI;//ofRandom(-PI,PI);
        
        
    }
    
    
    
    //    particleSystem.setTimeStep(1);
    
    commonAssets->updateAttribtuteData();
    
}
//--------------------------------------------------------------------------------------------
void MyScene2::update(float dt)
{


    box2d.update();
    // apply per-particle forces
    for(int i=0; i<circles.size(); i++) {
        circles[i].get()->addAttractionPoint(ofVec2f(CANVAS_WIDTH*0.5,CANVAS_HEIGHT*0.5), (isStart)?0.5:0);
        ofVec2f pos = circles[i].get()->getPosition();
        commonAssets->setParticleVertex(i, pos);
        commonAssets->setParticleAngle(i, (circles[i]->getRotation()/360.0f)*TWO_PI);
//        if(pos.x>0 && pos.x < image.getWidth() && pos.y >0 && pos.y < image.getHeight())
//        {
//            ofColor c = image.getColor(pos.x, pos.y);
////            if(c.a > 0)
//            {
//                c.a = ofMap(maxRadius.get()-circles[i].get()->getRadius(),minRadius.get(),maxRadius.get(),255,10 );//((maxRadius.get()-circles[i].get()->getRadius())/maxRadius.get())*255;
//                if(c.r > 0 && c.g > 0 && c.b > 0 )commonAssets->setParticleColor(i, c);
//            }
//        }

    }
    
    commonAssets->srcFbo.begin();
    ofClear(0, 0, 0, 0);
    commonAssets->draw();
    commonAssets->srcFbo.end();
    commonAssets->updateAttribtuteData();
    
    commonAssets->fbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent for default
    ofClear(0, 0, 0, 0);
    
    commonAssets->shader.begin();
    commonAssets->shader.setUniformTexture("maskTex", commonAssets->bg.getTextureReference(), 1 );
    commonAssets->srcFbo.draw(0, 0);
    
    
    commonAssets->shader.end();
    commonAssets->fbo.end();
    
    commonAssets->updateAttribtuteData();
    if(counter<timeOut.get())
    {
        
        counter+=ofGetElapsedTimef()-prevElapse;
    }
    else{
        ofLogVerbose() << "counter : " << counter;
        toNextScene tonextScene;
        tonextScene.sceneID = 2;
        ofNotifyEvent(toNextSceneEvent, tonextScene, this);
        counter=0;
    }
    counterString = ofToString(counter);
    prevElapse = ofGetElapsedTimef();
}
void MyScene2::draw()
{

#if DEBUG
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0xf6c738);
        circles[i].get()->draw();
    }
#endif
    ofSetColor(255, 255, 255);
    ofFill();
    commonAssets->fbo.draw(0, 0);
//    commonAssets->draw();
    ofDrawBitmapString(ofToString(commonAssets->kParticles) + "k particles", 32, 32);
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
}
void MyScene2::keyPressed(int key)
{
    if(key == ' ')
    {
        isStart = !isStart;
    }
}
void MyScene2::mousePressed( int x, int y, int button )
{
}    //scene notifications
void MyScene2::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
        init();
}
//scene notifications
void MyScene2::sceneWillDisappear( ofxScene * toScreen )
{
//    commonAssets->reset();

}

void MyScene2::sceneDidAppear()
{
    //    printf("ofxScene::sceneDidAppear() :: %d\n", sceneID);
        isStart = true;
    prevElapse = ofGetElapsedTimef();
    counter = 0 ;

}

void MyScene2::sceneDidDisappear(ofxScene *fromScreen)
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }
}
