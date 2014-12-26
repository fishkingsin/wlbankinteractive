//
//  MyScene3.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 8/12/14.
//
//

#include "MyScene3.h"
void MyScene3::setup()
{
    image.loadImage("bg.png");
    ofDisableArbTex();
    
    ofEnableAlphaBlending();
#if USE_OFVBO
    texture.loadImage("particleGrid.png");
    texW = texture.getWidth();
    texH = texture.getHeight();
    
    cellRows  = 4;
    cellColls = 4;
    kParticles = 8;
#endif
    ofSetWindowShape(image.getWidth(), image.getHeight());
    
    
    float padding = 256;
    float maxVelocity = 0;
#if USE_OFVBO

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
    billboards.getVertices().resize(kParticles * 1024);
    billboards.getColors().resize(kParticles * 1024);
//    billboards.getTexCoords().resize(kParticles * 1024);
    billboards.getNormals().resize(kParticles * 1024,ofVec3f(0));
    for(int i = 0; i <kParticles * 1024; i++) {
#else
        billboard.loadTexture("particleGrid.png", 4, 4  );
        billboard.init();
        
        for(int i = 0; i <MAX_PARTICLES; i++) {
#endif
        float x,y,xv,yv;
        int n = ofRandom(0,4);
        switch(n)
        {
            case 0:
                x = -ofRandom(0, padding);
                y = ofRandom(0, ofGetHeight() );
                
                break;
            case 1:
                x = ofGetWidth()+ofRandom(0, padding);
                y = ofRandom(0, ofGetHeight() );
                
                break;
            case 2:
                x = ofRandom(0, ofGetWidth() );
                y = -ofRandom(0, padding);
                
                break;
            case 3:
                x = ofRandom(0, ofGetWidth());
                y = ofGetHeight()+ofRandom(0, padding);
                
                break;
        }
            
        xv = ofRandom(-maxVelocity, maxVelocity);
        yv = ofRandom(-maxVelocity, maxVelocity);
        Particle particle(x, y, xv, yv);
        particleSystem.add(particle);
        

#if USE_OFVBO
        billboards.setColor(i, ofColor::fromHsb(0, 0, 255));
        billboards.setNormal(i,ofVec3f(ofRandom(16, 64 ),0,0));
//        billboards.setTexCoord(i,ofVec2f((int)ofRandom(0, 2 ), (int)ofRandom(0, 2)));
        setParticleTexCoords(i, (int)ofRandom(0, cellColls ), (int)ofRandom(0, cellRows));
        divAtt[i] = 1.0f/cellColls;
            
#else

        billboard.setParticlePos(i, particle.x, particle.y);
#endif
        
    }
/*
 attribute float divAtt;
 attribute float offsetXAtt;
 attribute float offsetYAtt;
 int pointAttLoc = shader.getAttributeLocation("pointSize");
	vbo.setAttributeData(pointAttLoc, pointSizes, 1, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
 
 shader.begin();
	int pointAttLoc = shader.getAttributeLocation("pointSize");
	vbo.setAttributeData(pointAttLoc, pointSizes, 1, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
 
	// rotate the snow based on the velocity
	int angleLoc = shader.getAttributeLocation("angle");
	vbo.setAttributeData(angleLoc, rotations, 1, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	shader.end();
 */
        
    billboardShader.begin();
    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().setAttributeData(divAttLoc,  &divAtt[0], 1, kParticles*1024,  GL_STATIC_DRAW);
        int offsetXAttLoc = billboardShader.getAttributeLocation("offsetXAtt");
    billboards.getVbo().setAttributeData(offsetXAttLoc, &offSetXAtt[0], 1, kParticles*1024, GL_STATIC_DRAW);
        int offsetYAttLoc = billboardShader.getAttributeLocation("offsetYAtt");
    billboards.getVbo().setAttributeData(offsetYAttLoc, &offSetYAtt[0], 1, kParticles*1024, GL_STATIC_DRAW);
    billboardShader.end();
    particleSystem.setTimeStep(1);
    
    
    
    
    ofBackground(0, 0, 0);

    isStart = false;
}

void MyScene3::update(float dt)
{
    if(!isStart)
    {
        return;
    }
    particleSystem.setupForces();
    
    // apply per-particle forces
    for(int i = 0; i < particleSystem.size(); i++) {
        Particle& cur = particleSystem[i];
        // global force on other particles
        particleSystem.addRepulsionForce(cur, 3, 1);
        // forces on this particle
        //        cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());
        cur.addDampingForce();
    }
    // single global forces
    particleSystem.addAttractionForce(ofGetWidth() / 2, ofGetHeight() / 2, 1500, 0.01);
    //    particleSystem.addRepulsionForce(mouseX, mouseY, 100, 2);
    particleSystem.update();
    vector<Particle> &particles = particleSystem.getParticles();
    int n = particles.size();
    for(int i = 0; i < n; i++)
    {
#if USE_OFVBO
        billboards.getVertices()[i] = particles[i];
#else
        billboard.setParticlePos(i, particles[i].x, particles[i].y);
#endif
        if(particles[i].x>0 && particles[i].x < image.getWidth() && particles[i].y >0 && particles[i].y < image.getHeight())
        {
            ofColor c = image.getColor(particles[i].x, particles[i].y);
#if USE_OFVBO
            if(c.r > 0 && c.g > 0 && c.b > 0 )billboards.setColor(i, c);
#else
            if(c.r > 0 && c.g > 0 && c.b > 0 )billboard.setParticleColor(i, c.r, c.g, c.b , c.a);
#endif
            //            billboards.getNormals()[i].set(particles[i].xv*particles[i].yv, 0,0);
        }
    }
}
#if USE_OFVBO

void MyScene3::setParticleTexCoords(int i, float columnID, float rowID)
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
//    ofLogVerbose(__PRETTY_FUNCTION__) << "offSetXAtt :" << offSetXAtt[i] <<  " offSetYAtt :" << offSetYAtt[i];
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
#endif
void MyScene3::draw()
{
    if(!isStart)
    {
        return;
    }
    ofSetColor(255, 255, 255);
    ofFill();
    //	particleSystem.draw();
#if USE_OFVBO
    billboardShader.begin();

    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites(); // not needed for GL3/4

    billboardShader.end();
    ofDrawBitmapString(ofToString(kParticles*1024) + "k particles", 32, 32);
#else
    billboard.draw();
    ofDrawBitmapString(ofToString(MAX_PARTICLES) + "k particles", 32, 32);
#endif

    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
}
void MyScene3::keyPressed(int key)
{
    if(key == ' ')
    {
        isStart = !isStart;
    }
}
void MyScene3::mousePressed( int x, int y, int button )
{
}    //scene notifications
void MyScene3::sceneWillAppear( ofxScene * fromScreen )
{
}
//scene notifications
void MyScene3::sceneWillDisappear( ofxScene * toScreen )
{
    
}

void MyScene3::sceneDidAppear()
{
    //    printf("ofxScene::sceneDidAppear() :: %d\n", sceneID);
    //    isStart = true;
}