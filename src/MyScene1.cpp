//
//  MyScene1.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 5/12/14.
//
//

#include "MyScene1.h"
MyScene1::MyScene1()
{
    
}
void MyScene1::setup(){  //load your scene 1 assets here...
    font.loadFont("LiHei.ttf", 20);
    image.loadImage("scene1/question-01.png");
    paraGroup.setName("Scene1");
    paraGroup.add(numParticle.set("PARTICLE_SIZE",""));
    paraGroup.add(maxParticle.set("S1_MAX_PARTICLE",100,1,1000));
    paraGroup.add(minRadius.set("S1_MIN_RADIUS",8,1,50));
    paraGroup.add(maxRadius.set("S1_MAX_RADIUS",20,1,50));
    paraGroup.add(minInputY.set("S1_MIN_INPUT_Y",CANVAS_HEIGHT*0.9,1,CANVAS_HEIGHT));
    paraGroup.add(maxInputY.set("S1_MAX_INOUT_Y",CANVAS_HEIGHT*0.95,1,CANVAS_HEIGHT));
    paraGroup.add(minInputX.set("S1_MIN_INPUT_X",CANVAS_WIDTH*0.2,1,CANVAS_WIDTH));
    paraGroup.add(maxInputX.set("S1_MAX_INOUT_X",CANVAS_WIDTH,1,CANVAS_WIDTH));
    paraGroup.add(minDis.set("MIN_DISTANCE",0,0,100));
    paraGroup.add(    offSetPower.set("OFFSET_POWER",0,0,20));
    paraGroup.add(density.set("DENSITY",0,0,100));
    paraGroup.add(bounce.set("BOUNCE",0,0,3));
    paraGroup.add(fiction.set("FICTION",0,0,100));
    paraGroup.add(minAlpha.set("MIN_ALPHA", 0, 0, 255));
    
    //extra text object
    paraGroup.add(bDebug.set("bDebug",false));
    paraGroup.add(minObjectAppearLeft.set("minObjectAppearLeft",0,0,CANVAS_WIDTH));
    paraGroup.add(maxObjectAppearLeft.set("maxObjectAppearLeft",0,0,CANVAS_WIDTH));
    paraGroup.add(minObjectAppearRight.set("minObjectAppearRight",0,0,CANVAS_WIDTH));
    paraGroup.add(maxObjectAppearRight.set("maxObjectAppearRight",0,0,CANVAS_WIDTH));
    
    minInputY.addListener(this, &MyScene1::objectAppearRegionUpdate);
    maxInputY.addListener(this, &MyScene1::objectAppearRegionUpdate);
    minObjectAppearLeft.addListener(this, &MyScene1::objectAppearRegionUpdate);
    maxObjectAppearLeft.addListener(this, &MyScene1::objectAppearRegionUpdate);
    minObjectAppearRight.addListener(this, &MyScene1::objectAppearRegionUpdate);
    maxObjectAppearRight.addListener(this, &MyScene1::objectAppearRegionUpdate);
    
    paraGroup.add(objectDecay.set("objectDecay",0,0,1));
    paraGroup.add(objectAge.set("objectAge",0,0,10));
    paraGroup.add(objectDuration.set("objectDuration",1000,1000,100000));
    box2d.init();
    box2d.setGravity(0, -2);
    //    box2d.createBounds(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
    box2d.setFPS(60.0);
//    box2d.registerGrabbing();
    
    counter = 0;
    images.resize(8);
    for(int i = 0; i < 8 ; i++)
    {
        images[i].loadImage("images/"+ofToString(i+1)+".png");
    }
    
    
    
};


void MyScene1::update(float dt){ //update scene 1 here
    
    numParticle  = ofToString(circles.size());
    
    box2d.update();
    if(isFireEvent)
    {
        if(circles.size()==0)
        {
            toNextScene tonextScene;
            tonextScene.sceneID=1;
            ofNotifyEvent(toNextSceneEvent, tonextScene, this);
            isFireEvent = false;
        }
        
    }
    if(circles.size()>maxParticle)
    {
        if(!isFireEvent)
        {
            if(commonAssets->bAuto)
            {
                edges.clear();
                isFireEvent = true;
                
            }
            else{
                circles.clear();
                commonAssets->reset();
            }
            
        }
        //        circles.erase(circles.begin());
        
    }
    float diff = ofGetElapsedTimeMillis() - counter;

    for (int i = 0 ; i < circles.size() ; i++) {
        circles[i]->update();
        commonAssets->setParticleAngle(circles[i]->index, (circles[i]->getRotation()/360.0f)*TWO_PI);
        commonAssets->setParticleVertex(circles[i]->index, circles[i]->getPosition());
        commonAssets->setParticleNormal(circles[i]->index, ofVec3f(circles[i]->getRadius(),0,0));
        
    }
    commonAssets->updateAttribtuteData();
    ofRemove(circles, CustomParticle::shouldRemoveOffScreen);
    if(objectAge>0)
    {
        objectAge -= objectDecay;
    }
    else
    {
        objectX.setDuration(0);
    }
};

void MyScene1::draw(){ //draw scene 1 here
    
    ofPopStyle();
    ofSetColor(255);
    image.draw(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
    ofPushStyle();
    commonAssets->draw();
    float _x = objectX.update();
    if(objectAge>0 && objectX.isRunning())
    {
        ofPushStyle();
        ofSetColor(ofColor::white);
        font.drawString("DRAM", _x, minInputY);
        ofPopStyle();
    }
    if(bDebug)
    {
        
        ofPushStyle();
        ofNoFill();
        ofSetColor(ofColor::wheat);
        ofRect( minInputX , minInputY, maxInputX - minInputX , maxInputY-minInputY ) ;

        ofSetColor(ofColor::yellow);
        ofRect( minObjectAppearLeft , minInputY, maxObjectAppearLeft - minObjectAppearLeft , maxInputY-minInputY ) ;
        ofSetColor(ofColor::red);
        ofRect( minObjectAppearRight , minInputY, maxObjectAppearRight - minObjectAppearRight , maxInputY-minInputY ) ;
        if(objectAge>0 && objectX.isRunning())
        {
            ofSetColor(ofColor::cyan);
            ofLine(_x-20,minInputY+10,_x+20,minInputY+10);
            ofSetColor(ofColor::gold);
            ofLine(_x,minInputY-20+10,_x,minInputY+20+10);
        }
            ofSetColor(ofColor::purple);
            ofLine( prevPoint , currPoint);
        

        ofPopStyle();
        
    }
#ifdef USE_TRIANGLE
    triangulation.addPoint(circles[i].get()->getPosition());
#endif
#ifdef USE_TRIANGLE
    triangulation.triangulate();
#endif
    // draw the ground
    box2d.drawGround();
    ofPopStyle();
    ofPushStyle();
    ofNoFill();
#ifdef USE_TRIANGLE
    triangulation.draw();
#endif
    ofPopStyle();
#ifdef USE_TRIANGLE
    triangulation.reset();
#endif
    
};

void MyScene1::keyPressed(int key)
{
    switch(key)
    {
        case 'b':
        {
            
            createParticle( CANVAS_WIDTH*0.5+ofRandom(-CANVAS_WIDTH*0.5, CANVAS_WIDTH*0.5), CANVAS_HEIGHT*0.8+ofRandom(-50, 50), ofColor::white);
        }
            break;
        case 's':
        {
            createParticle(ofRandom( CANVAS_WIDTH), CANVAS_HEIGHT*0.5+ofRandom(0, 50), ofColor::white);
        }
            break;
        case 'c':
        {
            circles.clear();
            commonAssets->reset();
        }
            break;
    }
    
}
void MyScene1::mousePressed( int x, int y, int button ){
    if(ofRectangle(0,0,CANVAS_WIDTH,CANVAS_HEIGHT).inside(x, y))
    {
        createParticle(x, y, ofColor::white);
    }
}

//scene notifications
void MyScene1::sceneWillAppear( ofxScene * fromScreen ){  // reset our scene when we appear
    commonAssets->reset();
    
    objectAge.set(objectAge.getMax());
    isFireEvent = false;
    setupEdge();
    isStart = false;
    
    commonAssets->goldenRatioBank.clear();
    int initNum=1;
    float initSize = maxRadius;
    for(int i = 0 ; i < commonAssets->kParticles ; i++)
    {
        initSize = 1 / kGoldenRatio *initSize ;
        if(initSize<minRadius)
        {
            break;
        }
        initNum = maxRadius/initSize;
        for(int j = 0 ; j < initNum ;j++)
        {
            commonAssets->goldenRatioBank.push_back(initSize);
        }
    }
    
};

void MyScene1::sceneDidAppear() {
    isStart = true;
}
//scene notifications
void MyScene1::sceneWillDisappear( ofxScene * toScreen ){
    commonAssets->reset();
    
}
void MyScene1::sceneDidDisappear( ofxScene * fromScreen )
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }
    isStart = false;
}

void MyScene1::eventsIn(customeOSCData & data)
{
    if(!isFireEvent && isStart)
    {
        
        currPoint.set(ofPoint(ofMap(data.pos.x,0,1,minInputX,maxInputX), ofMap(data.pos.y,0,1,minInputY,maxInputY)));
        float distance = prevPoint.distance(currPoint);
        if(objectX.isCompleted())
        {
        if(objectAppearLeft.inside(currPoint) && objectAppearLeft.inside(prevPoint) && currPoint.x>prevPoint.x)
        {
            objectX.setParameters(0, linearEasing, ofxTween::easeOut, minObjectAppearLeft, maxObjectAppearRight, objectDuration, 0);
        }
        else if(objectAppearRight.inside(currPoint) && objectAppearRight.inside(prevPoint) && currPoint.x<prevPoint.x )
        {
            objectX.setParameters(0, linearEasing, ofxTween::easeOut, maxObjectAppearRight, minObjectAppearLeft, objectDuration, 0);
        }
        }
        objectAge.set(objectAge.getMax());
        if(abs(distance)>minDis)
        {
            
            createParticle(currPoint.x, currPoint.y , ofColor::white);
            
            prevPoint = currPoint ;
        }
    }
    
}

void MyScene1::createParticle(float _x , float _y , ofColor color)
{
    
    float x = MIN(MAX(0,_x),CANVAS_WIDTH);
    float y = MIN(MAX(0,_y),CANVAS_HEIGHT);
    circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
    float r = commonAssets->goldenRatioBank[circles.size()%commonAssets->goldenRatioBank.size()];
    //    circles.back().get()->addForce(ofVec2f(0,10), 10);
    circles.back().get()->setPhysics(density+r,bounce,fiction);
    circles.back().get()->setup(box2d.getWorld(),x,y, r*0.1);
    float angle = (int)(352+ofRandom(commonAssets->minHue,commonAssets->maxHue))%360;
    ofColor c = ofColor::fromHsb(angle, ofRandom(commonAssets->minSaturation,commonAssets->maxSaturation)*255, ofRandom(commonAssets->minBright,commonAssets->maxBright)*255, ofMap(r, minRadius, maxRadius, 255,minAlpha));
    
    circles.back().get()->setupTheCustomData(c,images[ofRandom(images.size())],r,5);
    circles.back().get()->index = circles.size()-1;
    commonAssets->setParticleTexCoords(circles.size()-1,(int)ofRandom(commonAssets->cellColls),(int)ofRandom(commonAssets->cellRows) );
    commonAssets->setParticleColor(circles.size()-1, c);
    commonAssets->setParticleNormal(circles.size()-1,ofVec3f(circles.back().get()->getRadius(),0,0));
    
    commonAssets->divAtt[circles.size()-1] = 1.0f/commonAssets->cellColls;
    
}


void MyScene1::setupEdge()
{
    
    //bound
    ofPtr<ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    edge.get()->addVertex(0,0);
    edge.get()->addVertex(CANVAS_WIDTH,0);
    edge.get()->addVertex(CANVAS_WIDTH,CANVAS_HEIGHT);
    edge.get()->addVertex(0,CANVAS_HEIGHT);
    edge.get()->addVertex(0,0);
    
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
    
    //    commonAssets.blockRectX, commonAssets.blockRectY, commonAssets.blockRectW, commonAssets.blockRectH
    edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    edge.get()->addVertex(commonAssets->blockRectX,commonAssets->blockRectY);
    edge.get()->addVertex(commonAssets->blockRectX+commonAssets->blockRectW,commonAssets->blockRectY);
    edge.get()->addVertex(commonAssets->blockRectX+commonAssets->blockRectW,commonAssets->blockRectY+commonAssets->blockRectH);
    edge.get()->addVertex(commonAssets->blockRectX,commonAssets->blockRectY+commonAssets->blockRectH);
    edge.get()->addVertex(commonAssets->blockRectX,commonAssets->blockRectY);
    
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
}

void MyScene1::objectAppearRegionUpdate(float &f)
{
    objectAppearLeft.set( minObjectAppearLeft , minInputY, maxObjectAppearLeft - minObjectAppearLeft , maxInputY-minInputY );
    
    objectAppearRight.set( minObjectAppearRight , minInputY, maxObjectAppearRight - minObjectAppearRight , maxInputY-minInputY );
}