//
//  CustomParticle.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 5/12/14.
//
//

#include "CustomParticle.h"
void CustomParticle::setupTheCustomData(ofColor color , int size , float _startSize , float col , float row) {
    
    // we are using a Data pointer because
    // box2d needs to have a pointer not
    // a referance
    setData(new Data());
    Data * theData = (Data*)getData();
    
    theData->id = ofRandom(0, 100);
    theData->cellCol = col;
    theData->cellRow = row;
    theData->color = color;
//    theData->image = &image;
    theData->r = ofRandom(size,size*2);
//    theData->color.a = ofMap(theData->r,size,size*2,255,10,true);
    targetR = size;
    tween.setParameters(0,easing,ofxTween::easeOut,_startSize, size,2000,0);
    ofAddListener(tween.end_E, this, &CustomParticle::tweenEnd);
}
void CustomParticle::update()
{
//    float r = getRadius()+((targetR-getRadius())*0.01);
    setRadius(tween.update());
}
void CustomParticle::draw() {
    Data* theData = (Data*)getData();
    if(theData) {
        
        // Evan though we know the data object lets just
        // see how we can get the data out from box2d
        // you would use this when using a contact listener
        // or tapping into box2d's solver.
        
        float radius = theData->r;
        ofPushMatrix();
        ofTranslate(getPosition());
        ofRotateZ(getRotation());
        ofSetColor(theData->color);
        ofPushMatrix();
        ofCircle(-radius,-radius,radius*2);
//        theData->image->draw(-radius,-radius,radius*2,radius*2);
        ofPopMatrix();
        ofPopMatrix();
    }
}
bool CustomParticle::shouldRemoveOffScreen(ofPtr<CustomParticle> shape) {
    return !ofRectangle(-100, -100, ofGetWidth()+100, ofGetHeight()+100).inside(shape.get()->getPosition());
}
void CustomParticle::tweenEnd(int &i)
{
    //        particle->setPhysics(_density,_bounce,_fiction);
    //        particle->addForce(ofVec2f(0,-1), 1);
    //        scene->createParticle(this->x , this->y, ofColor::white);
    ofLogVerbose("tweenEnd") << i;
    
}