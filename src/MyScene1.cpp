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
    paraGroup.setName("Scene1");
    paraGroup.add(numParticle.set("PARTICLE_SIZE",""));
    paraGroup.add(maxParticle.set("S1_MAX_PARTICLE",100,1,1000));
    paraGroup.add(minRadius.set("S1_MIN_RADIUS",8,1,50));
    paraGroup.add(maxRadius.set("S1_MAX_RADIUS",20,1,50));
    paraGroup.add(minDis.set("MIN_DISTANCE",0,0,100));
    paraGroup.add(    offSetPower.set("OFFSET_POWER",0,0,20));
    paraGroup.add(density.set("DENSITY",0,0,100));
    paraGroup.add(bounce.set("BOUNCE",0,0,3));
    paraGroup.add(fiction.set("FICTION",0,0,100));
    paraGroup.add(minAlpha.set("MIN_ALPHA", 0, 0, 255));

    box2d.init();
    box2d.setGravity(0, -5);
    //    box2d.createBounds(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
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
    //    if(diff > coolDown)
    //    {
    //        int n = ofRandom(1,10);
    //        if(n<circles.size())
    //        {
    //            for (int i = 0 ; i < n ; i++)
    //            {
    //                circles.erase(circles.begin());
    //            }
    //        }
    //        counter = ofGetElapsedTimeMillis();
    //    }
    
    for (int i = 0 ; i < circles.size() ; i++) {
        circles[i]->update();
        commonAssets->setParticleAngle(circles[i]->index, (circles[i]->getRotation()/360.0f)*TWO_PI);
        commonAssets->setParticleVertex(circles[i]->index, circles[i]->getPosition());
        commonAssets->setParticleNormal(circles[i]->index, ofVec3f(circles[i]->getRadius(),0,0));

    }
    commonAssets->updateAttribtuteData();
    ofRemove(circles, CustomParticle::shouldRemoveOffScreen);
};

void MyScene1::draw(){ //draw scene 1 here
    
    ofPopStyle();
    ofPushStyle();
    commonAssets->draw();
    //    for(int i=0; i<circles.size(); i++) {
    //        ofFill();
    //        ofSetHexColor(0xf6c738);
    //        circles[i].get()->draw();
#ifdef USE_TRIANGLE
    triangulation.addPoint(circles[i].get()->getPosition());
#endif
    //    }
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
            
            createParticle( CANVAS_WIDTH*0.5+ofRandom(-50, 50), CANVAS_HEIGHT*0.5+ofRandom(-50, 50), ofColor::white);
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
    createParticle( x,y, ofColor::white);
    }
}

//scene notifications
void MyScene1::sceneWillAppear( ofxScene * fromScreen ){  // reset our scene when we appear
    commonAssets->reset();
    isFireEvent = false;
    setupEdge();
};


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
}

void MyScene1::eventsIn(customeOSCData & data)
{
    if(!isFireEvent)
    {
    currPoint.set(ofPoint(data.pos.x*CANVAS_WIDTH, CANVAS_HEIGHT*0.9));
    float distance = prevPoint.distance(currPoint);
    
    if(abs(distance)>minDis)
    {

        createParticle(currPoint.x, currPoint.y , ofColor::white);
//        createParticle(currPoint.x-(distance*offSetPower), currPoint.y , ofColor::white);
        prevPoint = currPoint ;
    }
    //    if(circles.size()<maxParticle.get())
    //    {
    
    //        circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
    //        float r = ofRandom(4, 10);
    //
    //
    //        circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    //        circles.back().get()->setup(box2d.getWorld(), data.pos.x*CANVAS_WIDTH, data.pos.y*CANVAS_HEIGHT, r);
    //        ofColor c = ofColor::fromHsb(data.c.getHue(),MAX(data.c.getSaturation() ,200), MAX(data.c.getBrightness(),200));
    //        circles.back().get()->setupTheCustomData(c,images[ofRandom(images.size())],r);
    //    }
    }
}

void MyScene1::createParticle(float _x , float _y , ofColor color)
{
    float x = MIN(MAX(0,_x),CANVAS_WIDTH);
    float y = MIN(MAX(0,_y),CANVAS_HEIGHT);
    circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
    float r = ofRandom(minRadius, maxRadius);
    circles.back().get()->addForce(ofVec2f(0,10), 10);
    circles.back().get()->setPhysics(density,bounce,fiction);
    circles.back().get()->setup(box2d.getWorld(),x,y, r*0.1);
    float angle = (int)(352+ofRandom(commonAssets->minHue,commonAssets->maxHue))%360;
    ofColor c = ofColor::fromHsb(angle, ofRandom(commonAssets->minSaturation,commonAssets->maxSaturation)*255, ofRandom(commonAssets->minBright,commonAssets->maxBright)*255, ofMap(r, minRadius, maxRadius, 255,minAlpha));
    
    circles.back().get()->setupTheCustomData(c,images[ofRandom(images.size())],r);
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
