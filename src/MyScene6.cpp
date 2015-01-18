//
//  MyScene6.cpp
//  wlbankinteractive
//
//  Created by James Kong on 18/1/15.
//
//

#include "MyScene6.h"
void MyScene6::setup()
{
    easings.push_back(&easingExpo);
    easings.push_back(&easingSine);
    easings.push_back(& easingElastic);
    easings.push_back(& easingCubic);

    image = commonAssets->bg;
    //    image.loadImage("backgrounds/bg.png");
//    step = 4;
//    for (int y = 0 ; y < image.height; y+=step)
//    {
//        for (int x = 0 ; x < image.width; x+=step) {
//            if(image.getColor(x, y).getHue()>0)
//            {
//                MAX_POINTS++;
//            }
//            
//        }
//    }
    
    
    
    
}
void MyScene6::init()
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
    delay = ofRandom(0,2);
    for(int i = 0 ; i< maxParitcle.get() ; i++)
    {
//        float step = i;
        step+=theStep.get();
        start.push_back(ofPtr<ofVec3f>(new ofVec3f));
        end.push_back(ofPtr<ofVec3f>(new ofVec3f));
        start.back()->set( sin((step/n)*TWO_PI)*maxOutterR + centerX ,
                          cos((step/n)*TWO_PI)*maxOutterR + centerY) ;
        
        end.back()->set(sin(((step)/n)*TWO_PI)*maxR*(step/n)*0.25 + centerX,
                        cos(((step)/n)*TWO_PI)*maxR*(step/n)*0.25 + centerY) ;
        ofPtr<ofxTween> tx = ofPtr<ofxTween>(new ofxTween);
       
        
        
        tx.get()->setParameters(5,*ease,ofxTween::easeOut,start.back()->x, end.back()->x,duration.get(),i*delay.get());
        tweensX.push_back(tx);
        
        
        ofPtr<ofxTween> ty = ofPtr<ofxTween>(new ofxTween);
        ty.get()->setParameters(5,*ease,ofxTween::easeOut, start.back()->y, end.back()->y,duration.get(),i*delay.get());
        tweensY.push_back(ty);
        commonAssets->setParticleVertex(i, *start.back().get());
        particleSizes.push_back(ofPtr<ofVec3f > ( new ofVec3f(ofRandom(minRadius.get(), maxRadius.get() ))));
        if(end.back()->x>0 && end.back()->x < image.getWidth() &&  end.back()->y >0 &&  end.back()->y < image.getHeight())
        {
            ofColor c = image.getColor(end.back()->x, end.back()->y);
            ofVec3f v = commonAssets->billboards.getNormals()[i];
            if(c.getSaturation()>0)
            {
                        c.a = ofMap(maxRadius.get()-v.x,minRadius.get(),maxRadius.get(),10,255 );
                         c.a = ofMap(particleSizes.back()->x, minRadius.get(), maxRadius.get(), 10, 255);
                        commonAssets->setParticleColor(i, c);
            }
            else{
                c = ofColor::white;
                 c.a = ofMap(particleSizes.back()->x, minRadius.get(), maxRadius.get(), 10, 255);
                commonAssets->setParticleColor(i, c);
            }
        }
        commonAssets->setParticleNormal(i,*particleSizes.back());
        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
    }

    commonAssets->updateAttribtuteData();
}

void MyScene6::update(float dt)
{
    for(int i = 0 ; i< tweensX.size() ; i++)
    {
        float x = tweensX[i].get()->update();
        float y = tweensY[i].get()->update();
                commonAssets->setParticleVertex(i, ofVec3f(x,y,0));
        


    }
    
    
    
    
}
void MyScene6::draw()
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
        ofPopStyle();
    }
    commonAssets->draw();
}
void MyScene6::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
    init();

}
void MyScene6::sceneDidAppear()
{
    
    
}
void MyScene6::sceneWillDisappear(ofxScene *toScreen)
{
    
    
}
void MyScene6::sceneDidDisappear(ofxScene *fromScreen)
{
    tweensX.clear();
    tweensY.clear();
    start.clear();
    end.clear();
    particleSizes.clear();
    image.clear();
}