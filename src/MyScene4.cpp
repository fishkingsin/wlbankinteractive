//
//  MyScene4.cpp
//  wlbankinteractive
//
//  Created by James Kong on 4/1/15.
//
//

#include "MyScene4.h"


void MyScene4::setup()
{
//    image.loadImage("bg.png");
    box2d.init();
    box2d.setGravity(0, 30);
//    box2d.createGround();
    box2d.setFPS(30.0);
//    setupEdge();
    
    
}
void MyScene4::init()
{
    setupEdge();
    image = commonAssets->bg;
//    ofDirectory *dir = &commonAssets->dir;
//    image.loadImage(dir->getFile(((int)ofRandom(dir->getFiles().size()-1))));
    col = (int)ofRandom(0, commonAssets->cellColls );
    row = (int)ofRandom(0, commonAssets->cellRows);
    for(int i = 0 ; i < 400; i++)
    {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 0.5);
        c.get()->setup(box2d.getWorld(), CANVAS_WIDTH*0.5+ofRandom(-10,10), -i, ofRandom(minRadius.get(),maxRadius.get()));
        ofVec2f pos = c.get()->getPosition();
        float r = c.get()->getRadius();

        commonAssets->setParticleVertex(i, pos);
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleNormal(i,ofVec3f(r,0,0));

        commonAssets->setParticleTexCoords(i,col,row );
        commonAssets->divAtt[i] = 1.0f/commonAssets->cellColls;

        circles.push_back(c);
    }
        commonAssets->updateAttribtuteData();
    
}
void MyScene4::update(float dt)
{
    
     box2d.update();
    for(int i=0; i<circles.size(); i++) {
        ofVec2f pos = circles[i].get()->getPosition();
        float r = circles[i].get()->getRadius();
        commonAssets->setParticleVertex(i, pos);
        commonAssets->setParticleColor(i, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleAngle(i,(circles[i]->getRotation()/360.0f)*TWO_PI);
//        commonAssets->setParticleNormal(i,ofVec3f(r*2,0,0));
//        commonAssets->setParticleTexCoords(i, (int)ofRandom(0, commonAssets->cellColls ), (int)ofRandom(0, commonAssets->cellRows));

        if(pos.x>0 && pos.x < CANVAS_WIDTH && pos.y >0 && pos.y < CANVAS_HEIGHT)
        {
            ofColor c = image.getColor(pos.x, pos.y);
            c.a = ofMap(circles[i].get()->getRadius(),minRadius.get(),maxRadius.get(),10,255);
            if(c.r > 0 && c.g > 0 && c.b > 0 )commonAssets->setParticleColor(i, c);
        }
        
    }
    commonAssets->updateAttribtuteData();
}
void MyScene4::draw()
{
    if(debugDraw.get())
    {
        ofSetColor(0);
        for(int i = 0 ; i < edges.size() ; i++)
        {
            edges[i]->draw();
        }
        ofPushStyle();
        ofNoFill();
        ofSetColor(ofColor::cyan);
        for(int i = 0 ; i < circles.size() ; i++)
        {
            circles[i]->draw();
        }
        ofPopStyle();
        
    }
    commonAssets->draw();
}
void MyScene4::keyPressed(int key)
{
    if(key == 'b') {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        c.get()->setPhysics(1, 0.5, 0.5);
        c.get()->setup(box2d.getWorld(), CANVAS_WIDTH*0.5, 0, ofRandom(2,6));
        
        circles.push_back(c);
        commonAssets->setParticleColor(circles.size()-1, ofColor::fromHsb(0, 0, 255));
        commonAssets->setParticleTexCoords(circles.size()-1,col,row );
    }
    if(key == 'c') {
        edges.clear();
    }
    if(key=='e')
    {
        setupEdge();
    }
}
void MyScene4::mousePressed( int x, int y, int button )
{
    
}
void MyScene4::sceneWillAppear( ofxScene * fromScreen )
{
    commonAssets->reset();
    
}
//scene notifications
void MyScene4::sceneWillDisappear( ofxScene * toScreen )
{
    
}
void MyScene4::sceneDidAppear()
{
    init();
}
void MyScene4::sceneDidDisappear(ofxScene *fromScreen)
{
    while(circles.size()>0)
    {
        circles.erase(circles.begin());
        
    }
    edges.clear();

}

void MyScene4::setupEdge()
{
    int density = 10;
    float radius =  CANVAS_HEIGHT*0.40;
    ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    for (int i=-180+density+25; i<180-25; i+=density) {
        float x = sin(TWO_PI*(i/360.0f))*radius+initX.get();
        float y = cos(TWO_PI*(i/360.0f))*radius+initY.get();
        edge.get()->addVertex(x, y);
        edge.get()->create(box2d.getWorld());
        
    }


    edges.push_back(edge);
    //bound
//     edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
//    edge.get()->addVertex(CANVAS_WIDTH,0);
//    edge.get()->addVertex(CANVAS_WIDTH,CANVAS_HEIGHT);
//    edge.get()->addVertex(0,CANVAS_HEIGHT);
//    edge.get()->addVertex(0,0);
//
//    edge.get()->create(box2d.getWorld());
//        edges.push_back(edge);
//
//    vector<ofPolyline> polylines = createOutlineFromImage("logo01.jpg");
//    
//    for (int i = 0 ; i < polylines.size(); i++) {
//         ofPtr <ofxBox2dEdge> _edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
//        _edge.get()->addVertexes(polylines[i]);
//        _edge.get()->create(box2d.getWorld());
//        edges.push_back(_edge);
//    }
    
    
}

vector<ofPolyline> MyScene4::createOutlineFromImage(string path)
{
    ofxCvColorImage cvImgColor;
    ofxCvGrayscaleImage cvImgGrayscale;
    ofxCvContourFinder contourFinder;
    vector<ofPolyline> polylines;
    
    ofImage image;
    image.loadImage(path);
    cvImgColor.allocate(image.getWidth(),image.getHeight());
    cvImgGrayscale.allocate(image.getWidth(),image.getHeight());
    
    cvImgColor.setFromPixels(image.getPixels(), image.getWidth(),image.getHeight());
    cvImgGrayscale.setFromColorImage(cvImgColor);
    cvImgGrayscale.threshold(125,true);
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