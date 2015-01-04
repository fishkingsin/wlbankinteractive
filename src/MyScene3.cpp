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
    image.loadImage("bg.png");
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
    tweensX.resize(MAX_POINTS);
    tweensY.resize(MAX_POINTS);
    
    

}
void MyScene3::init()
{
       vector <ofPoint> points;
    vector <ofPoint> targets;
    points.resize(MAX_POINTS);
    targets.resize(MAX_POINTS);
    int maxRadius = ((ofGetWidth()>ofGetHeight())?ofGetWidth():ofGetHeight());
    float padding = 256;
    int  i= 0 ;
    for (int y = 0 ; y < image.height; y+=step)
    {
        for (int x = 0 ; x < image.width; x+=step) {
            if(image.getColor(x, y).getHue()>0)
            {
                targets[i].set(x,y);
                
                i++;
                
            }
        }
    }
    
    for(int i = 0 ; i< MAX_POINTS ; i++)
    {
        float randomPI = ofRandom(-PI,PI);
        float r = ofRandom(maxRadius);
        float _x = (sin(randomPI)*maxRadius)+(sin(randomPI)*ofRandom(padding))+ofGetWidth()*0.5;
        float _y = (cos(randomPI)*maxRadius)+(cos(randomPI)*ofRandom(padding))+ofGetHeight()*0.5;
        points[i].set(_x, _y);
        
        
        tweensX[i].setParameters(5,easingelastic,ofxTween::easeOut,points[i].x,targets[i].x,10000,i);
        tweensY[i].setParameters(5,easingelastic,ofxTween::easeOut,points[i].y,targets[i].y,10000,i);
        commonAssets->setParticleVertex(i, ofVec3f(points[i].x,points[i].y,0));
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleNormal(i,ofVec3f(ofRandom(4, 8 ),0,0));
        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
    }
    count = 0;
}

void MyScene3::update(float dt)
{
    for(int i = 0 ; i< MAX_POINTS ; i++)
    {
        float x = tweensX[i].update();
        float y = tweensY[i].update();
        commonAssets->setParticleVertex(i, ofVec3f(x,y,0));
        
        //        points[i].draw();
    }

}
void MyScene3::draw()
{
    ofSetColor(255, 255, 255);
    commonAssets->draw();
}
void MyScene3::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();

}
void MyScene3::sceneDidAppear()
{
    
    init();
}