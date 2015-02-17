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
    paraGroup.setName("Scene2");
    paraGroup.add(logoTimeout.set("S2_LOGO_TIMEOUT",5000,1000,10000));
    paraGroup.add(logoDelay.set("S2_LOGO_DELAY",5000,1000,10000));
    paraGroup.add(maxParitcle.set("S2_MAX_PARTICLE",3000,1,10000));
    paraGroup.add(minRadius.set("S2_MIN_RADIUS",8,1,50));
    paraGroup.add(maxRadius.set("S2_MAX_RADIUS",20,1,50));
    paraGroup.add(radius.set("S2_LOGO_RADIUS",CANVAS_WIDTH*0.5,0,CANVAS_WIDTH));
    paraGroup.add(counterString.set("S2_COUNTER",""));
    paraGroup.add(minRScale.set("S2_MIN_R_SCALE",1,0,2));
    paraGroup.add(maxRScale.set("S2_MAX_R_SCALE",1,0,2));
    paraGroup.add(timeOut.set("S2_TIME_OUT",5,0,20));
    
    
    counter = 0 ;
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
    commonAssets->goldenRatioBank.clear();
    int initNum=1;
    float initSize = commonAssets->maxRadius;
    for(int i = 0 ; i < commonAssets->kParticles ; i++)
    {
        initSize = 1 / kGoldenRatio *initSize ;
        if(initSize<commonAssets->minRadius)
        {
            break;
        }
        initNum = commonAssets->maxRadius/initSize;
        for(int j = 0 ; j < initNum ;j++)
        {
            commonAssets->goldenRatioBank.push_back(initSize);
        }
    }
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
        float r = commonAssets->goldenRatioBank[i%commonAssets->goldenRatioBank.size()];
        xv = ofRandom(-maxVelocity, maxVelocity);
        yv = ofRandom(-maxVelocity, maxVelocity);
        ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        circle.get()->setPhysics(100, 0.0, 150);
        circle.get()->setup(box2d.getWorld(), x, y , r);
        circles.push_back(circle);
//        ((maxRadius.get()-r)/maxRadius.get())*255
        float angle = (int)(352+ofRandom(commonAssets->minHue,commonAssets->maxHue))%360;
        commonAssets->setParticleColor(i, ofColor::fromHsb(angle, ofRandom(commonAssets->minSaturation,commonAssets->maxSaturation)*255, ofRandom(commonAssets->minBright,commonAssets->maxBright)*255,255));
//        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255,ofMap(r, minRadius.get(), maxRadius.get() , 255, 100)));
        commonAssets->setParticleNormal(i,ofVec3f(r*ofRandom(minRScale,maxRScale),0,0));
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
    
    if(isStart){
        box2d.update();
        // apply per-particle forces
        for(int i=0; i<circles.size(); i++) {
            circles[i].get()->addAttractionPoint(ofVec2f(commonAssets->elementCenterX,commonAssets->elementCenterY), (isStart)?0.5:0);
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
//        float alpha = counter/timeOut;
//
//        counterForAlpha = MAX(counterForAlpha,alpha);
//        commonAssets->shader.setUniform1f("time", counterForAlpha.update() );
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
}
void MyScene2::draw()
{
    ofPushStyle();
    ofSetColor( commonAssets->maskWhite, commonAssets->maskWhite, commonAssets->maskWhite ,counterForAlpha.update());
    image.draw(0,0);

    ofPopStyle();
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
//    ofDrawBitmapString(ofToString(commonAssets->kParticles) + "k particles", 32, 32);
    
//    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
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
    prevElapse = ofGetElapsedTimef();
    counter = 0 ;
//    counterForAlpha = 0;
    isStart = true;
    prevElapse = ofGetElapsedTimef();
    counter = 0 ;

    
    counterForAlpha.setParameters(0,linear,ofxTween::easeOut,0,255,logoTimeout,logoDelay);
}
//scene notifications
void MyScene2::sceneWillDisappear( ofxScene * toScreen )
{
//    commonAssets->reset();

}

void MyScene2::sceneDidAppear()
{
    //    printf("ofxScene::sceneDidAppear() :: %d\n", sceneID);
    

}

void MyScene2::sceneDidDisappear(ofxScene *fromScreen)
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }
    isStart = false;
}
