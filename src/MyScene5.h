//
//  MyScene5.h
//  wlbankinteractive
//
//  Created by James Kong on 15/1/15.
//
//

#ifndef __wlbankinteractive__MyScene5__
#define __wlbankinteractive__MyScene5__
#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "BaseScene.h"

#include "Constants.h"
#include "CommonAssets.h"
class MyScene5 : public BaseScene{
public:
    void setup();
    void init();
    void update(float dt);
    void draw();
    void keyPressed(int key);
    void mousePressed( int x, int y, int button );    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen );
    //scene notifications
    void sceneWillDisappear( ofxScene * toScreen );
    void sceneDidAppear();
    void sceneDidDisappear(ofxScene *fromScreen);

};
#endif /* defined(__wlbankinteractive__MyScene5__) */
