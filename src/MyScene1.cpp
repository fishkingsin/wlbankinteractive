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
    grabber = NULL;
}
void MyScene1::setup(){  //load your scene 1 assets here...
    
    box2d.init();
    box2d.setGravity(0, -50);
    box2d.createBounds();
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
    if(NULL == grabber)
    {
        ofLogError("Scene1") << "grabber is null";
        return;
    }
    
    
    
    bool bNewFrame = false;
    grabber->update();
    bNewFrame = grabber->isFrameNew();
    float scale = (1.0f*ofGetWidth())/VIDEO_WIDTH;
    if (bNewFrame){
        
        box2d.update();
        while(circles.size()>5000)
        {
            circles.erase(circles.begin());
            
        }
        float diff = ofGetElapsedTimeMillis() - counter;
        if(diff > coolDown)
        {
            int n = ofRandom(1,10);
            if(n<circles.size())
            {
                for (int i = 0 ; i < n ; i++)
                {
                    circles.erase(circles.begin());
                }
            }
            counter = ofGetElapsedTimeMillis();
        }
        
        for (int i = 0; i < contourFinder->nBlobs; i++){
            
            //        contourFinder.blobs[i].draw(0,0);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
            float r = ofRandom(4, 20);
            
            
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), contourFinder->blobs[i].boundingRect.getCenter().x *scale,
                                        contourFinder->blobs[i].boundingRect.getCenter().y*scale, r);
            ofColor c = grabber->getPixelsRef().getColor(contourFinder->blobs[i].boundingRect.getCenter().x, contourFinder->blobs[i].boundingRect.getCenter().y);
//            circles.back().get()->setupTheCustomData(grabber->getPixelsRef().getColor(contourFinder->blobs[i].boundingRect.getCenter().x, contourFinder->blobs[i].boundingRect.getCenter().y),image,r);
            circles.back().get()->setupTheCustomData(ofColor::fromHsb(c.getHue(),255,255),images[ofRandom(images.size())],r);
            
            
        }
    }
};

void MyScene1::draw(){ //draw scene 1 here
    if(NULL== grabber)
    {
        ofLogError("Scene1") << "grabber is null";
        return;
    }
    
    ofPopStyle();
    ofPushStyle();

    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0xf6c738);
        circles[i].get()->draw();
#ifdef USE_TRIANGLE
        triangulation.addPoint(circles[i].get()->getPosition());
#endif
    }
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
        case 's':
        {
            grabber->videoSettings();
        }
            break;
    }
    
}
void MyScene1::mousePressed( int x, int y, int button ){
    
}

//scene notifications
void MyScene1::sceneWillAppear( ofxScene * fromScreen ){  // reset our scene when we appear
};

//scene notifications
void MyScene1::sceneWillDisappear( ofxScene * toScreen ){
    
}
void MyScene1::sceneDidDisappear( ofxScene * fromScreen )
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }
}