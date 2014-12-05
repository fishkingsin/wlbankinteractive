//
//  MyScene1.h
//  wlbankinteractive
//
//  Created by Kong king sin on 4/12/14.
//
//

#ifndef wlbankinteractive_MyScene1_h
#define wlbankinteractive_MyScene1_h
#include "ofxBox2d.h"
#include "ofMain.h"
#include "ofxScene.h"
#include "ofxDelaunay.h"
#include "ofxOpenCV.h"

#include "ofxOpticalFlowLK.h"
#include "Constants.h"
class Data {
public:
    ofColor color;
    int		id;
};
// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
    
public:
    
    void setupTheCustomData(ofColor color) {
        
        // we are using a Data pointer because
        // box2d needs to have a pointer not
        // a referance
        setData(new Data());
        Data * theData = (Data*)getData();
        
        theData->id = ofRandom(0, 100);
        
        theData->color = color;
        
    }
    
    void draw() {
        Data* theData = (Data*)getData();
        if(theData) {
            
            // Evan though we know the data object lets just
            // see how we can get the data out from box2d
            // you would use this when using a contact listener
            // or tapping into box2d's solver.
            
            float radius = getRadius();
            ofPushMatrix();
            ofTranslate(getPosition());
            ofRotateZ(getRotation());
            ofSetColor(theData->color);
            ofFill();
            ofCircle(0, 0, radius);
            
            ofPopMatrix();
        }
    }
    
    
};


class MyScene1 : public ofxScene{
public:
    MyScene1()
    {
        grabber = NULL;
    }
    void setup(){  //load your scene 1 assets here...
        
        box2d.init();
        box2d.setGravity(0, -50);
        box2d.createBounds();
        box2d.setFPS(60.0);
        box2d.registerGrabbing();
        
        fbo.allocate(VIDEO_WIDTH,VIDEO_HEIGHT,GL_RGB);
        pixels.allocate(VIDEO_WIDTH,VIDEO_HEIGHT,OF_IMAGE_COLOR);
        
        
        
        opticalFlow.setup(ofRectangle(0, 0, VIDEO_WIDTH, VIDEO_HEIGHT));
        cvImage.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
        grayImage.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
        opticalFlow.setOpticalFlowSize(14);
        opticalFlow.setOpticalFlowBlur(14);
        grayBg.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
        grayDiff.allocate(VIDEO_WIDTH,VIDEO_HEIGHT);
        threshold = 80;
        counter = 0;
        
    };
    
    
    void update(float dt){ //update scene 1 here
        if(NULL == grabber)
        {
            ofLogError("Scene1") << "grabber is null";
            return;
        }
        if(maxArea<minArea)
        {
            maxArea = minArea;
        }
        
        
        bool bNewFrame = false;
        grabber->update();
        bNewFrame = grabber->isFrameNew();
        float scale = (1.0f*ofGetWidth())/VIDEO_WIDTH;
        if (bNewFrame){
            opticalFlow.update(*grabber);
            fbo.begin();
            ofPushStyle();
            ofSetColor(0);
            ofFill();
            ofRect(0, 0, VIDEO_WIDTH,VIDEO_HEIGHT);
            ofPopStyle();
            ofSetColor(255);
            opticalFlow.draw(VIDEO_WIDTH,VIDEO_HEIGHT);
            fbo.end();
            fbo.readToPixels(pixels);
            //        cvImage.setFromPixels(grabber->getPixels(), VIDEO_WIDTH ,VIDEO_HEIGHT);
            cvImage.setFromPixels(pixels.getPixels(), VIDEO_WIDTH ,VIDEO_HEIGHT);
            grayImage = cvImage;
            
            if(bBlur)grayImage.blurGaussian();
            
            
            
            
            // take the abs value of the difference between background and incoming and then threshold:
            grayDiff.absDiff(grayBg, grayImage);
            grayDiff.threshold(threshold);
            
            // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
            // also, find holes is set to true so we will get interior contours as well....
            contourFinder.findContours(grayImage,
                                       minArea,
                                       maxArea,
                                       nConsidered,
                                       bFindHoles,
                                       bUseApproximation);	// find holes
            
            grayBg = grayImage;
        }
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
        for (int i = 0; i < contourFinder.nBlobs; i++){
            
            //        contourFinder.blobs[i].draw(0,0);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            circles.push_back(ofPtr<CustomParticle>(new CustomParticle));
            float r = ofRandom(4, 20);
            
            
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), contourFinder.blobs[i].boundingRect.getCenter().x *scale,
                                        contourFinder.blobs[i].boundingRect.getCenter().y*scale, r);
            circles.back().get()->setupTheCustomData(grabber->getPixelsRef().getColor(contourFinder.blobs[i].boundingRect.getCenter().x, contourFinder.blobs[i].boundingRect.getCenter().y));
            
            
        }
    };
    
    void draw(){ //draw scene 1 here
        if(NULL== grabber)
        {
            ofLogError("Scene1") << "grabber is null";
            return;
        }
        if(debugDraw1)
        {
            grabber->draw(0,0,ofGetWidth(),ofGetHeight());
        }
        ofPopStyle();
        ofPushStyle();
        for(int i=0; i<circles.size(); i++) {
            ofFill();
            ofSetHexColor(0xf6c738);
            circles[i].get()->draw();
            triangulation.addPoint(circles[i].get()->getPosition());
            
        }
        triangulation.triangulate();
        // draw the ground
        box2d.drawGround();
        ofPopStyle();
        ofPushStyle();
        ofNoFill();
        triangulation.draw();
        ofPopStyle();
        triangulation.reset();
        
        if(debugDraw2)
        {
            //    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
            opticalFlow.draw(ofGetWidth(),ofGetHeight());
        }
        if(debugDraw3)
        {
            grayImage.draw(20,20,160,120);
            grayBg.draw(180,20,160,120);
            grayDiff.draw(20,180,160,120);
            grabber->draw(180, 160, 160, 120);
            
            ofPushStyle();
            ofSetHexColor(0xffffff);
            
            // we could draw the whole contour finder
            contourFinder.draw(0,0,ofGetWidth(),ofGetHeight());
            
            
        }
    };
    
    void keyPressed(int key)
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
    void mousePressed( int x, int y, int button ){
        
    }
    
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen ){  // reset our scene when we appear
    };
    
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen ){
    }
    
    ofVideoGrabber *grabber;
    
    //sencing
    ofxOpticalFlowLK opticalFlow;
    ofxCvColorImage cvImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvContourFinder 	contourFinder;
    
    ofFbo fbo;
    ofPixels pixels;
    ofParameter<int> coolDown;
    
    ofParameter<int>  threshold;
    ofParameter<int> minArea;
    ofParameter<int> maxArea;
    ofParameter<int> nConsidered;
    ofParameter<bool> bFindHoles;
    ofParameter<bool> bUseApproximation ;
    ofParameter<bool> bBlur;
    ofParameter<bool> debugDraw1;
    ofParameter<bool> debugDraw2;
    ofParameter<bool> debugDraw3;
    float counter;
    //box2d
    ofxBox2d                            box2d;			  //	the box2d world
    vector    <ofPtr<CustomParticle> >	circles;		  //	default box2d circles
    ofxDelaunay triangulation;
    
    
};

#endif
