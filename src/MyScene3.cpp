//
//  MeScene4.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 25/12/14.
//
//

#include "MyScene3.h"
void MyScene3::setup()
{
    image = commonAssets->bg;
//    image.loadImage("backgrounds/bg.png");
    step = 4;
    for (int y = 0 ; y < image.height; y+=step)
    {
        for (int x = 0 ; x < image.width; x+=step) {
            if(image.getColor(x, y).getHue()>0)
            {
                MAX_POINTS++;
            }
            
        }
    }

    
    

}
void MyScene3::init()
{
//    tweensY.clear();
//    tweensX.clear();
    image = commonAssets->bg;
//    ofDirectory *dir = &commonAssets->dir;
//    image.loadImage(dir->getFile(((int)ofRandom(dir->getFiles().size()-1))));
    MAX_POINTS = 0;
    for (int y = 0 ; y < image.height; y+=step)
    {
        for (int x = 0 ; x < image.width; x+=step) {
            if(image.getColor(x, y).getHue()>0 && image.getColor(x, y).a>0)
            {
                MAX_POINTS++;
            }
            
        }
    }
//    image.loadImage("backgrounds/bg.png");
    ofPoint* points = new ofPoint[MAX_POINTS];
    ofPoint* targets = new ofPoint[MAX_POINTS];
    int maxR = ((CANVAS_WIDTH>CANVAS_HEIGHT)?CANVAS_WIDTH:CANVAS_HEIGHT);
    float padding = 256;
    int  i= 0 ;
    for (int y = 0 ; y < image.height; y+=step)
    {
        for (int x = 0 ; x < image.width; x+=step) {
            if(i<MAX_POINTS)
            {
            if(image.getColor(x, y).getSaturation()>0)
            {
                targets[i].set(x,y);
                
                i++;
                
            }
            }
        }
    }
    
    int mode = (int)ofRandom(0,4);
    
    for(int i = 0 ; i< MAX_POINTS ; i++)
    {
        float randomPI = ofRandom(-PI,PI);
        float r = ofRandom(maxR);
        float _x = 0;//
        float _y = 0;//
        switch (mode) {
            case 0:
                _x = (sin(randomPI)*maxR)+(sin(randomPI)*ofRandom(padding))+commonAssets->elementCenterX.get();
                _y = (cos(randomPI)*maxR)+(cos(randomPI)*ofRandom(padding))+commonAssets->elementCenterY.get();

                break;
            case 1:
            {
                int direction = (int)ofRandom(0, 1);
                
                _x = (direction==1)?-100:ofGetWidth()+100;
                _y = (cos(randomPI)*maxR)+(cos(randomPI)*ofRandom(padding))+commonAssets->elementCenterY.get();
            }
                break;
            case 2:
            {
                int direction = (int)ofRandom(0, 1);
                
                _x = (sin(randomPI)*maxR)+(sin(randomPI)*ofRandom(padding))+commonAssets->elementCenterX.get();
                _y = (direction==1)?-100:ofGetHeight()+100;
            }
                
                break;
            case 3:
                _x = (sin(randomPI)*maxR)+(sin(randomPI)*ofRandom(padding))+commonAssets->elementCenterX.get();
                _y = ofGetHeight()+100;
                break;
            case 4:
                _x = (sin(randomPI)*maxR)+(sin(randomPI)*ofRandom(padding))+commonAssets->elementCenterX.get();
                _y = -100;
                break;
            default:
                break;
        }
        points[i].set(_x, _y);
        
        
        ofPtr<ofxTween> tx = ofPtr<ofxTween>(new ofxTween);
        tx.get()->setParameters(5,easingelastic,ofxTween::easeOut,points[i].x,targets[i].x,10000,i);
        tweensX.push_back(tx);

        
        ofPtr<ofxTween> ty = ofPtr<ofxTween>(new ofxTween);
        ty.get()->setParameters(5,easingelastic,ofxTween::easeOut,points[i].y,targets[i].y,10000,i);
        tweensY.push_back(ty);
        commonAssets->setParticleVertex(i, ofVec3f(points[i].x,points[i].y,0));
        ofVec3f particleSize = ofVec3f(ofRandom(minRadius.get(), maxRadius.get() ));
        ofColor c = image.getColor(targets[i].x,targets[i].y);//ofColor::fromHsb(0, 0, 255);
        c.a = ofMap(particleSize.x,minRadius.get(), maxRadius.get(),255,10);
        commonAssets->setParticleColor(i,c );
        commonAssets->setParticleNormal(i,particleSize);
        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
    }
    count = 0;
    commonAssets->updateAttribtuteData();
}

void MyScene3::update(float dt)
{
    for(int i = 0 ; i< tweensX.size() ; i++)
    {
        float x = tweensX[i].get()->update();
        float y = tweensY[i].get()->update();
        commonAssets->setParticleVertex(i, ofVec3f(x,y,0));
        
        //        points[i].draw();
    }

}
void MyScene3::draw()
{
//    ofSetColor(255, 255, 255);
    commonAssets->draw();
}
void MyScene3::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
    init();

}
void MyScene3::sceneDidAppear()
{
    
    
}

void MyScene3::sceneDidDisappear(ofxScene *fromScreen)
{
    tweensX.clear();
    tweensY.clear();
//    while(tweensX.size()>0)
//    {
//        tweensX.erase(tweensX.begin());
//        
//    }
//    while(tweensY.size()>0)
//    {
//        tweensY.erase(tweensY.begin());
//        
//    }

}