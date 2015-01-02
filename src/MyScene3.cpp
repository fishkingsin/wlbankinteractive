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
        
    }
    count = 0;
}

void MyScene3::update(float dt)
{
}
void MyScene3::draw()
{
    ofSetColor(255, 255, 255);
    for(int i = 0 ; i< MAX_POINTS ; i++)
    {
        ofCircle(tweensX[i].update(), tweensY[i].update(), 2);
        //        points[i].draw();
    }
}
void MyScene3::sceneDidAppear()
{
    init();
}