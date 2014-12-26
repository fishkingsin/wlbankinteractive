//
//  Billboard.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 26/12/14.
//
//

#include "VBOBillboard.h"

VBOBillboard::VBOBillboard() {
}


// ------------------------------------------ set texture coords
void VBOBillboard::setParticleTexCoords(int i, float columnID, float rowID) {
    
    if(i < 0)				i = 0;
    if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
    
    if(columnID > cellColls) columnID = cellColls;
    if(rowID    > cellRows)	 rowID	  = cellRows;
    
    if(columnID < 0) columnID = 0;
    if(rowID < 0)	 rowID	  = 0;
    
    
    
    // get the cell image width
    float cellWidth  = texW / cellRows;
    float cellHeight = texH / cellColls;
    
    float row = rowID;
    float col = columnID;
    
    // P1
    texcords[(i*4)+0].u = (cellWidth * row)		/ texW;
    texcords[(i*4)+0].v = (cellHeight * col)	/ texH;
    
    // P2
    texcords[(i*4)+1].u = ((cellWidth * row)	+ cellWidth)	/ texW;
    texcords[(i*4)+1].v = (cellHeight * col)	/ texH;
    
    // P2
    texcords[(i*4)+2].u = ((cellWidth * row) + cellWidth)		/ texW;
    texcords[(i*4)+2].v = ((cellHeight * col) + cellHeight)	/ texH;
    
    // P2
    texcords[(i*4)+3].u = (cellWidth * row)		/ texW;
    texcords[(i*4)+3].v = ((cellHeight * col)+cellHeight)	/ texH;
    
    //    ofLogVerbose("P1") << "u: " << texcords[(i*4)+0].u <<" w:"<< texcords[(i*4)+0].v ;
    //    ofLogVerbose("P2") << "u: " << texcords[(i*4)+1].u <<" w:"<< texcords[(i*4)+1].v ;
    //    ofLogVerbose("P3") << "u: " << texcords[(i*4)+2].u <<" w:"<< texcords[(i*4)+2].v ;
    //    ofLogVerbose("P4") << "u: " << texcords[(i*4)+3].u <<" w:"<< texcords[(i*4)+3].v ;
    
    
}

// ------------------------------------------ set color
void VBOBillboard::setParticleColor(int i, float r, float g, float b, float a) {
    
    
    if(i < 0) i = 0;
    if(i > MAX_PARTICLES) i = MAX_PARTICLES;
    
    
    // Color 1
    color[(i*4)+0].r = r;
    color[(i*4)+0].g = g;
    color[(i*4)+0].b = b;
    color[(i*4)+0].a = a;
    
    // Color 2
    color[(i*4)+1].r = r;
    color[(i*4)+1].g = g;
    color[(i*4)+1].b = b;
    color[(i*4)+1].a = a;
    
    // Color 3
    color[(i*4)+2].r = r;
    color[(i*4)+2].g = g;
    color[(i*4)+2].b = b;
    color[(i*4)+2].a = a;
    
    // Color 4
    color[(i*4)+3].r = r;
    color[(i*4)+3].g = g;
    color[(i*4)+3].b = b;
    color[(i*4)+3].a = a;
    
}

// ------------------------------------------ set position
void VBOBillboard::setParticlePos(int i, float px, float py, float pz) {
    
    if(i < 0)				i = 0;
    if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
    
    
    // P1
    pos[(i*4)+0].x = px;
    pos[(i*4)+0].y = py;
    pos[(i*4)+0].z = pz;
    
    // P2
    pos[(i*4)+1].x = px + dim[i];
    pos[(i*4)+1].y = py;
    pos[(i*4)+1].z = pz;
    
    // P2
    pos[(i*4)+2].x = px + dim[i];
    pos[(i*4)+2].y = py + dim[i];
    pos[(i*4)+2].z = pz;
    
    // P2
    pos[(i*4)+3].x = px;
    pos[(i*4)+3].y = py + dim[i];
    pos[(i*4)+3].z = pz;
    
    
    
}

// ------------------------------------------ set size of particle
void VBOBillboard::setParticleSize(int i, float particleDim) {
    
    if(i < 0)				i = 0;
    if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
    
    dim[i] = particleDim;
}

// ------------------------------------------ add to the current position
void VBOBillboard::addPosition(int i, float x, float y, float z) {
    
    if(i < 0)				i = 0;
    if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
    
    
    // P1
    pos[(i*4)+0].x += x;
    pos[(i*4)+0].y += y;
    pos[(i*4)+0].z += z;
    
    // P2
    pos[(i*4)+1].x += x;
    pos[(i*4)+1].y += y;
    pos[(i*4)+1].z += z;
    
    // P2
    pos[(i*4)+2].x += x;
    pos[(i*4)+2].y += y;
    pos[(i*4)+2].z += z;
    
    // P2
    pos[(i*4)+3].x += x;
    pos[(i*4)+3].y += y;
    pos[(i*4)+3].z += z;
    
    
    
}

// ------------------------------------------ load textures
void VBOBillboard::loadTexture(string path, int cellsInRow, int cellsInCol) {
    
    ofDisableArbTex();
    texture.loadImage(path);
    ofEnableArbTex();
    
    texW = texture.getWidth();
    texH = texture.getHeight();
    
    cellRows  = cellsInRow;
    cellColls = cellsInCol;
}



// ------------------------------------------ init
void VBOBillboard::init() {
    
    
    
    printf("-------------------------------\n");
    
    printf("Max Particles: %i\n", MAX_PARTICLES);
    printf("Pos Size: %i\n", MAX_PARTICLES*4);
    
    printf("-------------------------------\n");
    
    
    
    // Init All The Particles Values
    for(int i=0; i<MAX_PARTICLES; i++) {
        
        // Set the size of the particle
        setParticleSize(i, ofRandom(15, 20));
        
        // The Color Data
        setParticleColor(i, 1, 1, 1, 1);
        
        
        // Position and Texture
        float px = ofRandom(-100, 100);
        float py = ofRandom(-100, 100);
        float pz = ofRandom(-100, 100);
        setParticlePos(i, 0,0,0);
        
        
        // The Texture Coords
        setParticleTexCoords(i, (int)ofRandom(0, cellRows), (int)ofRandom(0, cellColls));
        
        
    }
    
    
    
    
    // Setup the VBO
    
    glGenBuffersARB(3, &particleVBO[0]);
    
    // color
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*4*sizeof(float), color, GL_STREAM_DRAW_ARB);
    
    // vertices
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*3*sizeof(float), pos, GL_STREAM_DRAW_ARB);
    
    // texture coords
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*2*sizeof(float), texcords, GL_STREAM_DRAW_ARB);
    
}


// ------------------------------------------
void VBOBillboard::update() {
    float t = (ofGetElapsedTimef()) * 0.7;
    float div = 250.0;
    float noiseStrength = 2;
    for(int i=0; i<MAX_PARTICLES; i++) {
        
//        setParticleColor(i, 1.0, 1.0, 1.0, 1.0);
        
/*        if(life[i][0] <= 0.0)
        {
            
            
            // Set the size of the particle
            setParticleSize(i, ofRandom(20.0, 40.0));
            
            // The Color Data
            setParticleColor(i, 1, 1, 1, 1);
            
            
            // Position and Texture
            float px = ofGetWidth()*0.5+ofRandom(-10, 10);
            float py = ofGetHeight()*0.5+ofRandom(-10, 10);
            float pz = ofRandom(-100, 100);
            setParticlePos(i, px, py, pz);
            
            
            // The Texture Coords
            setParticleTexCoords(i, (int)ofRandom(0, 2), (int)ofRandom(0, 2));
        }*/
    }
    
}

// ------------------------------------------ Add Particles
void VBOBillboard::addParticles(int amt, float _x, float _y, float _z) {
    
}

// ------------------------------------------
void VBOBillboard::draw() {
    
    
    
    
    
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    // bind tex coors
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]);
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*2*sizeof(float), texcords);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    
    
    // bind color
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*4*sizeof(float), color);
    glColorPointer(4, GL_FLOAT, 0, 0);
    
    
    // bind vertices [these are quads]
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*3*sizeof(float), pos);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    
    // draw the vbo
    glDisable(GL_DEPTH_TEST);
    ofEnableArbTex();	
    
    ofEnableAlphaBlending();
    texture.getTextureReference().bind();
    
    glDrawArrays(GL_QUADS, 0, MAX_PARTICLES*4);
    
    texture.getTextureReference().unbind();
    ofDisableAlphaBlending();
    
    ofDisableArbTex();
    glEnable(GL_DEPTH_TEST);
    
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glDisable(GL_TEXTURE_2D);
    
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    
    
}

