//
//  MyScene9.cpp
//  wlbankinteractive
//
//  Created by James Kong on 24/1/15.
//
//

#include "MyScene9.h"
void MyScene9::setup()
{
    
}

void MyScene9::update(float dt)
{
    
    
}
void MyScene9::draw()
{
    ofPushStyle();
    ofNoFill();
    ofSetColor(0);
    for(int i= 0 ; i < triangleMesh.size() ;i++)
    {
        triangleMesh[i].draw();
    }
    ofPopStyle();
    
}
void MyScene9::sceneWillAppear(ofxScene *fromScreen)
{
    image = commonAssets->bg;
    triangleMesh = tirangulateFromImage();
}
vector<ofxTriangleMesh> MyScene9::tirangulateFromImage()
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
    vector<ofxTriangleMesh> new_triangleMesh;
     for(unsigned int i = 0; i < polylines.size(); i++) {
         ofxTriangleMesh mesh;
         mesh.triangulate(polylines[i]);
         new_triangleMesh.push_back(mesh);
     }
    
    return new_triangleMesh;
}