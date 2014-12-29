//
//  CommonAssets.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 29/12/14.
//
//

#include "CommonAssets.h"

void CommonAssets::setup()
{

    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    
    
    billboardShader.setGeometryInputType(GL_POINT);
    billboardShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    billboardShader.setGeometryOutputCount(4);
    if(ofGetGLProgrammableRenderer()){
        billboardShader.load("shadersGL3/Billboard");
    }else{
        billboardShader.load("shadersGL2/Billboard");
    }
    
    divAtt.resize(kParticles * 1024);
    offSetXAtt.resize(kParticles * 1024);
    offSetYAtt.resize(kParticles * 1024);
    angle.resize(kParticles * 1024);
    alpha.resize(kParticles * 1024);
    billboards.getVertices().resize(kParticles * 1024);
    billboards.getColors().resize(kParticles * 1024);
    billboards.getNormals().resize(kParticles * 1024,ofVec3f(0));
    int n = kParticles * 1024;

    billboardShader.begin();
    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().setAttributeData(divAttLoc,  &divAtt[0], 1, n,  GL_DYNAMIC_DRAW);
    int offsetXAttLoc = billboardShader.getAttributeLocation("offsetXAtt");
    billboards.getVbo().setAttributeData(offsetXAttLoc, &offSetXAtt[0], 1, n, GL_DYNAMIC_DRAW);
    int offsetYAttLoc = billboardShader.getAttributeLocation("offsetYAtt");
    billboards.getVbo().setAttributeData(offsetYAttLoc, &offSetYAtt[0], 1, n, GL_DYNAMIC_DRAW);
    int angleAttLoc = billboardShader.getAttributeLocation("angle");
    billboards.getVbo().setAttributeData(angleAttLoc, &angle[0], 1, n, GL_DYNAMIC_DRAW);

    int alphaAttLoc = billboardShader.getAttributeLocation("alphaAtt");
    billboards.getVbo().setAttributeData(alphaAttLoc, &alpha[0], 1, n, GL_DYNAMIC_DRAW);

    
    billboardShader.end();
}
void CommonAssets::updateAttribtuteData()
{
    int n = kParticles * 1024;
    billboardShader.begin();
    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().updateAttributeData(divAttLoc,  &divAtt[0], n);
    int offsetXAttLoc = billboardShader.getAttributeLocation("offsetXAtt");
    billboards.getVbo().updateAttributeData(offsetXAttLoc, &offSetXAtt[0], n);
    int offsetYAttLoc = billboardShader.getAttributeLocation("offsetYAtt");
    billboards.getVbo().updateAttributeData(offsetYAttLoc, &offSetYAtt[0], n);
    int angleAttLoc = billboardShader.getAttributeLocation("angle");
    billboards.getVbo().updateAttributeData(angleAttLoc, &angle[0], n);
    int alphaAttLoc = billboardShader.getAttributeLocation("alphaAtt");
    billboards.getVbo().updateAttributeData(alphaAttLoc, &alpha[0], n);
    
    billboardShader.end();
}
void CommonAssets::loadImage(string filePath , int col , int row ,int  nParticle)
{
    
    texture.loadImage(filePath);
    
    texW = texture.getWidth();
    texH = texture.getHeight();
    
    cellRows  = col;
    cellColls = row;
    kParticles = nParticle;
}
void CommonAssets::draw()
{
    ofSetColor(255);
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
}

void CommonAssets::setParticleColor(int i, ofColor c)
{
    if(i < 0)                               i = 0;
    if(i > kParticles * 1024)   i = kParticles * 1024;
    billboards.setColor(i, c);
//    alpha[i] = c.a;
}
void CommonAssets::setParticleVertex(int i, ofVec3f v)
{
    if(i < 0)                               i = 0;
    if(i > kParticles * 1024)   i = kParticles * 1024;
    billboards.getVertices()[i] = v;
}

void CommonAssets::setParticleNormal(int i, ofVec3f v)
{
    if(i < 0)                               i = 0;
    if(i > kParticles * 1024)   i = kParticles * 1024;
     billboards.setNormal(i,v);
}

void CommonAssets::setParticleTexCoords(int i, float columnID, float rowID)
{
    
    if(i < 0)                               i = 0;
    if(i > kParticles * 1024)   i = kParticles * 1024;
    
    if(columnID > cellColls) columnID = cellColls;
    if(rowID    > cellRows)  rowID    = cellRows;
    
    if(columnID < 0) columnID = 0;
    if(rowID < 0)    rowID    = 0;
    
    
    
    // get the cell image width
    float cellWidth  = texW / cellRows;
    float cellHeight = texH / cellColls;
    
    float row = rowID;
    float col = columnID;
    offSetXAtt[i] = (cellWidth * row) / texW;
    offSetYAtt[i] = (cellHeight * col) / texH;
//        ofLogVerbose(__PRETTY_FUNCTION__) << "offSetXAtt :" << offSetXAtt[i] <<  " offSetYAtt :" << offSetYAtt[i];
    // P1
    //    billboards.getTexCoords()[(i*4)+0].set( (cellWidth * row) / texW,(cellHeight * col) / texH);
    //    ofLogVerbose(ofToString(i)) << billboards.getTexCoords()[(i*4)+0];
    
    // P2
    //    billboards.getTexCoords()[(i*4)+1].x = ((cellWidth * row)  +   cellWidth)    / texW;
    //    billboards.getTexCoords()[(i*4)+1].y = (cellHeight * col)        / texH;
    //
    //    // P2
    //    billboards.getTexCoords()[(i*4)+2].x = ((cellWidth * row) + cellWidth)           / texW;
    //    billboards.getTexCoords()[(i*4)+2].y = ((cellHeight * col) + cellHeight) / texH;
    //
    //    // P2
    //    billboards.getTexCoords()[(i*4)+3].x = (cellWidth * row)         / texW;
    //    billboards.getTexCoords()[(i*4)+3].y = ((cellHeight * col)+cellHeight)   / texH;
    
    
    
}

