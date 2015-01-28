//
//  MySceneLiquidfun.cpp
//  wlbankinteractive
//
//  Created by James Kong on 27/1/15.
//
//

#include "MySceneLiquidfun.h"
void MySceneLiquidfun::setup()
{
    paraGroup.setName("MySceneLiquidfun");
    paraGroup.add(maxParitcle.set("SLQF_MAX_PARTICLE",400,1,5000));
    paraGroup.add(minRadius.set("SLQF_MIN_RADIUS",8,1,50));
    paraGroup.add(maxRadius.set("SLQF_MAX_RADIUS",20,1,50));
    paraGroup.add(minRScale.set("SLQF_MIN_R_SCALE",1,0,2));
    paraGroup.add(maxRScale.set("SLQF_MAX_R_SCALE",1,0,2));
    
    paraGroup.add(debugDraw.set("SLQF_DEBUG_DRAW",false));
    paraGroup.add(timeOut.set("SLQF_TIME_OUT",5,0,20));
    paraGroup.add(counterString.set("SLQF_COUNTER",""));
    
    isStart = false;
    ofDisableArbTex();
    counter = 0 ;
    box2d.init();
    box2d.setGravity(0, 5);
    box2d.setFPS(30.0);

//    box2d.createBounds(0,0, CANVAS_WIDTH, CANVAS_HEIGHT);
}
void MySceneLiquidfun::init()
{
    image = commonAssets->bg;
    setupEdge();
    particles.setup(box2d.getWorld());
    
//    for (int i = 0; i < maxParitcle; i++) {
//        ofVec2f position = ofVec2f( (CANVAS_WIDTH * 0.5 +ofRandom(-100,100)),
//                                   (  CANVAS_HEIGHT*0.5+ ofRandom(-100,0)));
//        ofVec2f velocity = ofVec2f(0, 0);
//        particles.createParticle(position, velocity);
//    }
}
void MySceneLiquidfun::update(float dt)
{
    if(isStart){
        if(particles.getParticleCount()<maxParitcle)
        {
            ofVec2f position = ofVec2f( (CANVAS_WIDTH * 0.5 +ofRandom(-100,100)),
                                       (  ofRandom(-100,0)));
            ofVec2f velocity = ofVec2f(0, 0);
            particles.createParticle(position, velocity);
        }
        box2d.update();
    }
}
void MySceneLiquidfun::draw()
{
    particles.draw();
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
        
        ofPopStyle();
        
        
    }

}
void MySceneLiquidfun::keyPressed(int key)
{
    
}
void MySceneLiquidfun::mousePressed( int x, int y, int button )
{
    
}    //scene notifications
void MySceneLiquidfun::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
    counter = 0;
    prevElapse = ofGetElapsedTimef();
    init();
}
//scene notifications
void MySceneLiquidfun::sceneWillDisappear( ofxScene * toScreen )
{
    
}
void MySceneLiquidfun::sceneDidAppear()
{
    counter = 0;
    prevElapse = ofGetElapsedTimef();
    isStart = true;

}
void MySceneLiquidfun::sceneDidDisappear(ofxScene *fromScreen)
{
    particles.destroy();
    edges.clear();
    isStart = false;
}

void MySceneLiquidfun::setupEdge()
{
    ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    
    //    bound
    edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    edge->setPhysics(0, 0, 0);
    edge.get()->addVertex(CANVAS_WIDTH,0);
    edge.get()->addVertex(CANVAS_WIDTH,CANVAS_HEIGHT);
    edge.get()->addVertex(0,CANVAS_HEIGHT);
    edge.get()->addVertex(0,0);
    
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
    
    vector<ofPolyline> polylines = createOutlineFromImage();
    
    for (int i = 0 ; i < polylines.size(); i++) {
        ofPtr <ofxBox2dEdge> _edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
        _edge.get()->addVertexes(polylines[i]);
        _edge.get()->create(box2d.getWorld());
        edges.push_back(_edge);
    }
}
vector<ofPolyline>  MySceneLiquidfun::createOutlineFromImage()
{
    
    image.setImageType(OF_IMAGE_COLOR);
    
    ofxCvColorImage cvImgColor;
    ofxCvGrayscaleImage cvImgGrayscale;
    ofxCvContourFinder contourFinder;
    vector<ofPolyline> polylines;
    
    cvImgColor.allocate(image.getWidth(),image.getHeight());
    cvImgGrayscale.allocate(image.getWidth(),image.getHeight());
    
    cvImgColor.setFromPixels(image.getPixels(), image.getWidth(),image.getHeight());
    cvImgGrayscale.setFromColorImage(cvImgColor);
    cvImgGrayscale.threshold(200,true);
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
