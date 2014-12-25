//
//  CustomParticle.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 5/12/14.
//
//

#include "CustomParticle.h"
void CustomParticle::setupTheCustomData(ofColor color , ofImage &image , int size) {
    
    // we are using a Data pointer because
    // box2d needs to have a pointer not
    // a referance
    setData(new Data());
    Data * theData = (Data*)getData();
    
    theData->id = ofRandom(0, 100);
    
    theData->color = color;
    theData->image = &image;
    
}

void CustomParticle::draw() {
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
//        ofCircle(0, 0, radius);
        theData->image->draw(0,0,radius,radius);
        ofPopMatrix();
    }
}