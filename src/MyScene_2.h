//
//  MyScene_2.h
//  wlbankinteractive
//
//  Created by Kong king sin on 4/12/14.
//
//

#ifndef wlbankinteractive_MyScene_2_h
#define wlbankinteractive_MyScene_2_h

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxFTGLFont.h"
#include "Constants.h"

enum Presets
{
    
};
class MyFont
{
public:
    ofPoint pos;
    ofPoint pixelPos;
    ofPoint offset;
    string mChar;
    int scale;
};
class MyScene_2 : public ofxScene{
public:
    
    void setup();
    
    void update(float dt);
    void draw();
    void keyPressed(int key);
    void mousePressed( int x, int y, int button );    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    ofVideoGrabber *grabber;
    ofxFTGLFont font;
    ofFbo fbo;
    Presets presets;
    int charCount;
    float fontScale;
//    vector<string>fontFamily;
    vector<wstring>charSet;
//    vector<ofPtr<MyFont> > myFonts;

    wstring currentCharSet;
    ofParameter<float> scaleFactor;
//    ofParameter<int> characterPreset;
    bool isLive,isCapture;
    
};
#endif
