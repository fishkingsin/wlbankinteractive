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
typedef struct {
    ofVec2f pos;
    ofColor c;
}customeOSCData;
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
    
    void updateAttribtuteData();
    
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
    
//    vector<float>angle;
//    vector<float>alpha;

};


#endif /* defined(__wlbankinteractive__CommonAssets__) */
