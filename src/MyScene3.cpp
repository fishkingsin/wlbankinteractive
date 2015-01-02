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
    decay = 0.95;
    int theSize =9999;
    n = (theSize<commonAssets->kParticles)?theSize:commonAssets->kParticles;
    int maxRadius = ((ofGetWidth()>ofGetHeight())?ofGetWidth():ofGetHeight())*0.5;
    float padding = 256;
    float maxVelocity = 0;
    points.resize(n);
    target.resize(n);
    radius.resize(n);
    billboardVels.resize(n);
    for(int i = 0; i < n; i++) {
        
        float x,y,xv,yv;
        float randomPI = ofRandom(-PI,PI);
//        x = (sin(randomPI)*maxRadius)+
        x = (sin(randomPI)*ofRandom(padding))+ofGetWidth()*0.5;
//        y = (cos(randomPI)*maxRadius)+
        y = (cos(randomPI)*ofRandom(padding))+ofGetHeight()*0.5;
        points[i].set(x,y,0);
        target[i].set(ofGetWidth()*0.5,ofGetHeight()*0.5,0);
        commonAssets->setParticleVertex(i, points[i]);
        billboardVels[i]  = ofVec3f::zero();
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleNormal(i,ofVec3f(ofRandom(4, 8 ),0,0));
        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;
//        commonAssets->angle[i] = PI;
    }
    commonAssets->updateAttribtuteData();

}
void MyScene3::update(float dt)
{
    float div = 250.0;
    
    for (int i=0; i<n; i++) {
//        ofVec3f vec(0,sinf((points[i].x/div)+(dt*0.9)+TWO_PI*(i*1.0f/n)));
//        vec *=  ofGetLastFrameTime();
        ofVec3f vec = (points[i]-target[i])*0.1;
        billboardVels[i] += vec;
        points[i] += billboardVels[i];
        billboardVels[i] *= decay;
        commonAssets->setParticleVertex(i, points[i]);
        
    }
    
//    for(int i = 0; i < n; i++)
//    {
//        commonAssets->setParticleVertex(i, particles[i]);
//        if(particles[i].x>0 && particles[i].x < image.getWidth() && particles[i].y >0 && particles[i].y < image.getHeight())
//        {
//            ofColor c = image.getColor(particles[i].x, particles[i].y);
//            if(c.r > 0 && c.g > 0 && c.b > 0 )commonAssets->setParticleColor(i, c);
//            //            billboards.getNormals()[i].set(particles[i].xv*particles[i].yv, 0,0);
//        }
//    }

}
void MyScene3::draw()
{
    ofSetColor(255, 255, 255);
    
//    for (int p=0; p<n; p++){
//        
//        for (int i=0; i<n; i++){
//            if ((i != p && i%2==0 && p%2==0) || (i != p && i%2==1 && p%2==1)){
//                
//                float R             = points[p].distance(points[i]);
//                /*elimination
//                 
//                 */
//                int _radius = radius[p];
//                if (R < _radius){
//                    //numConnect++;
//                    if(R<_radius*0.1)
//                    {
//                        billboardVels[p].x           +=  (points[p].x - points[i].x) / R*0.8;
//                        billboardVels[p].y           +=  (points[p].y - points[i].y) / R*0.8;
//                        
//                        points[p] += billboardVels[p];
//                    }
//                    ofPushStyle();
//                    ofEnableBlendMode(OF_BLENDMODE_ADD);
//                    float brightness = ((p%2==1)?0.6:0.3);
//                    ofSetColor(255, ofMap(R,0,_radius,255,0)*brightness);
//                    ofSetLineWidth(1);
//                    ofLine(points[i].x, points[i].y, points[i].z, points[p].x, points[p].y, points[p].z);
//                    ofPopStyle();
//                }
//            }
//        }
//    }
    
    commonAssets->draw();
}
