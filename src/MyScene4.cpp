//
//  MyScene4.cpp
//  wlbankinteractive
//
//  Created by James Kong on 4/1/15.
//
//

#include "MyScene4.h"


void MyScene4::setup()
{
    paraGroup.setName("Scene4");
    paraGroup.add(maxParitcle.set("S4_MAX_PARTICLE",400,1,1000));
    paraGroup.add(minRadius.set("S4_MIN_RADIUS",8,1,50));
    paraGroup.add(maxRadius.set("S4_MAX_RADIUS",20,1,50));
    paraGroup.add(minRScale.set("S4_MIN_R_SCALE",1,0,2));
    paraGroup.add(maxRScale.set("S4_MAX_R_SCALE",1,0,2));

    paraGroup.add(debugDraw.set("DEBUG_DRAW",false));
    paraGroup.add(timeOut.set("S4_TIME_OUT",5,0,20));
    paraGroup.add(counterString.set("S4_COUNTER",""));
    isStart = false;
    ofDisableArbTex();
    counter = 0 ;
    //    image.loadImage("bg.png");
    box2d.init();
    box2d.setGravity(0, 30);
    //    box2d.createGround();
    box2d.setFPS(30.0);
    //    setupEdge();

    

    
    
}
void MyScene4::init()
{
//    maskFbo.begin();
//    ofClear(0,0,0,0);
//    maskFbo.end();
    
    commonAssets->fbo.begin();
    ofClear(0,0,0,0);
    commonAssets->fbo.end();

    commonAssets->srcFbo.begin();
    ofClear(0,0,0,0);
    commonAssets->srcFbo.end();
    
//    maskFbo.begin();
//    commonAssets->bg.draw(0,0);
//    maskFbo.end();
    
    prevElapse = ofGetElapsedTimef();
    counter = 0;
    setupEdge();
    image = commonAssets->bg;
    //    ofDirectory *dir = &commonAssets->dir;
    //    image.loadImage(dir->getFile(((int)ofRandom(dir->getFiles().size()-1))));
    col = 0;//(int)ofRandom(0, commonAssets->cellColls );
    row = 2;//(int)ofRandom(0, commonAssets->cellRows);
    for(int i = 0 ; i < maxParitcle.get(); i++)
    {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(10, 0.1, 0.5);
        c.get()->setup(box2d.getWorld(), commonAssets->elementCenterX.get()+ofRandom(-10,10), -i*100, ofRandom(minRadius.get(), maxRadius.get()));
        ofVec2f pos = c.get()->getPosition();
        float r = c.get()->getRadius();
        
        commonAssets->setParticleVertex(i, pos);
        float angle = (int)(352+ofRandom(commonAssets->minHue,commonAssets->maxHue))%360;
        commonAssets->setParticleColor(i, ofColor::fromHsb(angle, ofRandom(commonAssets->minSaturation,commonAssets->maxSaturation)*255, ofRandom(commonAssets->minBright,commonAssets->maxBright)*255,255));
        commonAssets->setParticleNormal(i,ofVec3f(r*ofRandom(minRScale,maxRScale),0,0));
        
        commonAssets->setParticleTexCoords(i,col,row );
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
        
        circles.push_back(c);
    }
    commonAssets->updateAttribtuteData();
    
}
void MyScene4::update(float dt)
{
    if(isStart){
        box2d.update();
        for(int i=0; i<circles.size(); i++) {
            ofVec2f pos = circles[i].get()->getPosition();
            float r = circles[i].get()->getRadius();
            commonAssets->setParticleVertex(i, pos);
            commonAssets->setParticleAngle(i,(circles[i]->getRotation()/360.0f)*TWO_PI);
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
void MyScene4::draw()
{
        commonAssets->fbo.draw(0, 0);
    if(debugDraw.get())
    {
        ofSetColor(0);
        for(int i = 0 ; i < edges.size() ; i++)
        {
            edges[i]->draw();
        }
        ofPushStyle();
        ofNoFill();
        ofSetColor(ofColor::cyan);
        for(int i = 0 ; i < circles.size() ; i++)
        {
            circles[i]->draw();
        }
        ofPopStyle();
        ofSetColor(255);
       commonAssets-> srcFbo.draw(0, 0);
        commonAssets->bg.draw(0,0);

    }
    
}
void MyScene4::keyPressed(int key)
{
    if(key == 'b') {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 0.5);
        c.get()->setup(box2d.getWorld(), commonAssets->elementCenterX.get(), 0, ofRandom(minRadius.get(),maxRadius.get()));
        
        circles.push_back(c);
        commonAssets->setParticleColor(circles.size()-1, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleTexCoords(circles.size()-1,col,row );
    }
    if(key == 'c') {
        edges.clear();
    }
    if(key=='e')
    {
        setupEdge();
    }
}
void MyScene4::mousePressed( int x, int y, int button )
{
    
}
void MyScene4::sceneWillAppear( ofxScene * fromScreen )
{
    
    commonAssets->reset();
    counter = 0;
    prevElapse = ofGetElapsedTimef();
    init();
}
//scene notifications
void MyScene4::sceneWillDisappear( ofxScene * toScreen )
{
    
}
void MyScene4::sceneDidAppear()
{

    counter = 0;
    prevElapse = ofGetElapsedTimef();
    isStart = true;

}
void MyScene4::sceneDidDisappear(ofxScene *fromScreen)
{
    circles.clear();
    edges.clear();
    isStart = false;
}

void MyScene4::setupEdge()
{
    int density = 10;
    float radius =  CANVAS_HEIGHT*0.40;
    ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    for (int i=-180+density+25; i<180-25; i+=density) {
        float x = sin(TWO_PI*(i/360.0f))*radius+commonAssets->elementCenterX.get();
        float y = cos(TWO_PI*(i/360.0f))*radius+commonAssets->elementCenterY.get();
        edge.get()->addVertex(x, y);
        edge.get()->create(box2d.getWorld());
        
    }
    
    
    edges.push_back(edge);
    //bound
    //     edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    //    edge.get()->addVertex(CANVAS_WIDTH,0);
    //    edge.get()->addVertex(CANVAS_WIDTH,CANVAS_HEIGHT);
    //    edge.get()->addVertex(0,CANVAS_HEIGHT);
    //    edge.get()->addVertex(0,0);
    //
    //    edge.get()->create(box2d.getWorld());
    //        edges.push_back(edge);
    //
    //    vector<ofPolyline> polylines = createOutlineFromImage("logo01.jpg");
    //
    //    for (int i = 0 ; i < polylines.size(); i++) {
    //         ofPtr <ofxBox2dEdge> _edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    //        _edge.get()->addVertexes(polylines[i]);
    //        _edge.get()->create(box2d.getWorld());
    //        edges.push_back(_edge);
    //    }
    
    
}

vector<ofPolyline> MyScene4::createOutlineFromImage(string path)
{
    ofxCvColorImage cvImgColor;
    ofxCvGrayscaleImage cvImgGrayscale;
    ofxCvContourFinder contourFinder;
    vector<ofPolyline> polylines;
    
    ofImage image;
    image.loadImage(path);
    cvImgColor.allocate(image.getWidth(),image.getHeight());
    cvImgGrayscale.allocate(image.getWidth(),image.getHeight());
    
    cvImgColor.setFromPixels(image.getPixels(), image.getWidth(),image.getHeight());
    cvImgGrayscale.setFromColorImage(cvImgColor);
    cvImgGrayscale.threshold(125,true);
    contourFinder.findContours(cvImgGrayscale, 20, image.getWidth()*image.getHeight(), 20, true, false);
    
    polylines.clear();
    for(unsigned int i = 0; i < contourFinder.blobs.size(); i++) {
        ofPolyline cur;
        // add all the current vertices to cur polyline
        cur.addVertices(contourFinder.blobs[i].pts);
        cur.setClosed(true);
        
        // add the cur polyline to all these vector<ofPolyline>
        polylines.push_back(cur);
    }
    return polylines;
    
}