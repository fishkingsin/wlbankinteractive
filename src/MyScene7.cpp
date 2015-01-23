//
//  MyScene7.cpp
//  wlbankinteractive
//
//  Created by James Kong on 18/1/15.
//
//

#include "MyScene7.h"

void MyScene7::setup()
{
    paraGroup.setName("Scene7");
    paraGroup.add(maxParitcle.set("S7_MAX_PARTICLE",3000,1,10000));
    paraGroup.add(minRadius.set("S7_MIN_RADIUS", 8,1,50));
    paraGroup.add(maxRadius.set("S7_MAX_RADIUS", 20,1,50));
    paraGroup.add(maxR.set("S7_MAX_R",CANVAS_WIDTH*0.5, 0,CANVAS_WIDTH));
    paraGroup.add(maxOutterR.set("S7_MAX_OUTTER_R", CANVAS_WIDTH*2,0,CANVAS_WIDTH*5));
    paraGroup.add(delay.set("S7_DELAY", 1, 0,20));
    paraGroup.add(duration.set("S7_DURATION", 1000,1,50000));
    paraGroup.add(theStep.set("S7_STEP", 1,50.0f,100));
    paraGroup.add(minStep.set("S7_MIN_STEP", 1,0.0f,100));
    paraGroup.add(maxStep.set("S7_MAX_STEP", 50,0.0f,100));
    paraGroup.add(minDelay.set("S7_MIN_DELAY", 0,0.0f,100));
    paraGroup.add(maxDelay.set("S7_MAX_DELAY", 50,0.0f,100));

    paraGroup.add(bDebug.set("S7_DEBUG",false));
    easings.push_back(&easingExpo);
    easings.push_back(&easingSine);
    easings.push_back(& easingLinear);
    easings.push_back(& easingCubic);
    
    image = commonAssets->bg;
}
void MyScene7::init()
{
    image = commonAssets->bg;
    
    float n = maxParitcle.get();
    //    int maxR = ((CANVAS_WIDTH>CANVAS_HEIGHT)?CANVAS_WIDTH:CANVAS_HEIGHT)*2;
    int centerX = CANVAS_WIDTH*0.5;
    int centerY = CANVAS_HEIGHT*0.5;
    float step = 0;
    int _index = (int)ofRandom(easings.size());
    ofxEasing * ease = easings[_index];
    ofLogVerbose() << "_index : " << _index;
    delay.set(ofRandom(minDelay.get(),maxDelay.get()));
    theStep.set(ofRandom(minStep.get(),maxStep.get()));
     polylines = createOutlineFromImage();
    int indexOfVertext=0;
    for(int i = 0 ; i < polylines.size() ; i++)
    {
        vector<ofVec3f> v =  polylines[i].getVertices();
        for(int j = 0 ; j < v.size() ;j++)
        {
            
            
                
            
//        }
//    for(int i = 0 ; i< maxParitcle.get() ; i++)
//    {
        //        float step = i;
        step+=theStep.get();
        start.push_back(ofPtr<ofVec3f>(new ofVec3f));
        end.push_back(ofPtr<ofVec3f>(new ofVec3f(v[j])));
        start.back()->set( sin((step/n)*TWO_PI)*maxOutterR + centerX ,
                          cos((step/n)*TWO_PI)*maxOutterR + centerY) ;
        
//        end.back()->set(sin(((step)/n)*TWO_PI)*maxR*(step/n)*0.25 + centerX,
//                        cos(((step)/n)*TWO_PI)*maxR*(step/n)*0.25 + centerY) ;
        ofPtr<ofxTween> tx = ofPtr<ofxTween>(new ofxTween);
        
        
        
        tx.get()->setParameters(5,*ease,ofxTween::easeOut,start.back()->x, end.back()->x,duration.get(),indexOfVertext*delay.get());
        tweensX.push_back(tx);
        
        
        ofPtr<ofxTween> ty = ofPtr<ofxTween>(new ofxTween);
        ty.get()->setParameters(5,*ease,ofxTween::easeOut, start.back()->y, end.back()->y,duration.get(),indexOfVertext*delay.get());
        tweensY.push_back(ty);
        commonAssets->setParticleVertex(indexOfVertext, *start.back().get());
        particleSizes.push_back(ofPtr<ofVec3f > ( new ofVec3f(ofRandom(minRadius.get(), maxRadius.get() ))));
        if(end.back()->x>0 && end.back()->x < image.getWidth() &&  end.back()->y >0 &&  end.back()->y < image.getHeight())
        {
            ofColor c = image.getColor(end.back()->x, end.back()->y);
            ofVec3f v = commonAssets->billboards.getNormals()[indexOfVertext];
            if(c.getSaturation()>0)
            {
                c.a = ofMap(maxRadius.get()-v.x,minRadius.get(),maxRadius.get(),10,255 );
                c.a = ofMap(particleSizes.back()->x, minRadius.get(), maxRadius.get(), 10, 255);
                commonAssets->setParticleColor(indexOfVertext, c);
            }
            else{
                c = ofColor::white;
                c.a = ofMap(particleSizes.back()->x, minRadius.get(), maxRadius.get(), 10, 255);
                commonAssets->setParticleColor(indexOfVertext, c);
            }
        }
        commonAssets->setParticleNormal(indexOfVertext,*particleSizes.back());
        commonAssets->setParticleTexCoords(indexOfVertext, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));
        commonAssets->divAtt[indexOfVertext] = 1.0f/commonAssets->cellColls;
            indexOfVertext++;
        }//polylines
    }
    if(tweensY.size()>0)
    {
        ofAddListener(tweensY.back()->end_E, this, &MyScene7::tweenEnd);
    }
    commonAssets->updateAttribtuteData();
}

void MyScene7::update(float dt)
{
    for(int i = 0 ; i< tweensX.size() ; i++)
    {
        float x = tweensX[i].get()->update();
        float y = tweensY[i].get()->update();
        commonAssets->setParticleVertex(i, ofVec3f(x,y,0));
        
        
        
    }
    
    
    
    
}
void MyScene7::draw()
{
    if(bDebug)
    {
        ofPushStyle();
        ofSetColor(0);
        ofNoFill();
        for(int i = 0; i < start.size() ; i++)
        {
            ofRect(*start[i].get(),10,10);
        }
        for(int i = 0; i < end.size() ; i++)
        {
            ofRect(*end[i].get(),10,10);
        }
//        for(int i = 0 ; i < polylines.size() ; i++)
//        {
//            polylines[i].draw();
//        }
        ofPopStyle();
    }
    commonAssets->draw();
}
void MyScene7::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
    init();
    
}
void MyScene7::sceneDidAppear()
{
    
    
}
void MyScene7::sceneWillDisappear(ofxScene *toScreen)
{
    
    
}
void MyScene7::sceneDidDisappear(ofxScene *fromScreen)
{
    tweensX.clear();
    tweensY.clear();
    start.clear();
    end.clear();
    particleSizes.clear();
    image.clear();
}

void MyScene7::tweenEnd(int &i)
{
    toNextScene tonextScene;;
    ofNotifyEvent(toNextSceneEvent, tonextScene, this);
    
}
vector<ofPolyline> MyScene7::createOutlineFromImage()
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