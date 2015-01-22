//
//  CommonAssets.h
//  wlbankinteractive
//
//  Created by Kong king sin on 29/12/14.
//
//

#ifndef __wlbankinteractive__CommonAssets__
#define __wlbankinteractive__CommonAssets__
#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "Constants.h"
typedef struct {
    ofVec2f pos;
    ofColor c;
}customeOSCData;
typedef struct {
    int sceneID;
}toNextScene;
typedef struct {
    
    string version;
    string vendor;
    string renderer;
    
    
    bool bPointSpritesSupported;
    bool bVboSupported;
    bool bShadersSupported;
    int maxTextureSize;
    int maxDimensions[2];
    int maxLights;
    
    
} commonOpenGlInfo;
class CommonAssets
{
public:
    void setup();
    
    void loadImage(string filePath = "particleGrid.png" , int col = 4, int row = 4 ,int  nParticle = 8);
    
    void draw();
    
    void setParticleColor(int i, ofColor c);
    
    void setParticleVertex(int i, ofVec3f v);
    
    void setParticleNormal(int i, ofVec3f v);
    
    void setParticleTexCoords(int i, float columnID, float rowID);
    
    void setParticleAngle(int i, float _angle);
    
    void updateAttribtuteData();
    
    string getLogoPath();
    
    string getBGPath();
    
    void nextImage();
    
    void reset();

    int kParticles;
    
    ofxAutoReloadedShader billboardShader;
    
    ofImage texture;
    
    ofVboMesh billboards;
    
    int                     cellRows;
    
    int                     cellColls;
    
    float           texW, texH;
    
    vector<float>divAtt;
    
    vector<float>moffsetXAtt;
    
    vector<float>moffsetYAtt;
    
    vector<float>angle;
//    vector<float>alpha;
    ofDirectory bgDir;
    ofDirectory logoDir;
    int imageIndex;
    ofImage logo;
    ofImage bg;
    ofParameter<int>elementCenterX;
    ofParameter<int>elementCenterY;
    
    
    ofFbo       fbo;
    ofFbo       srcFbo;
    
    ofShader    shader;
};


#endif /* defined(__wlbankinteractive__CommonAssets__) */
