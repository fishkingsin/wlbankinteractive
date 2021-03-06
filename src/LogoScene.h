//
//  LogoScene.h
//  wlbankinteractive
//
//  Created by James Kong on 17/1/15.
//
//

#ifndef __wlbankinteractive__LogoScene__
#define __wlbankinteractive__LogoScene__

#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "BaseScene.h"

#include "Constants.h"
#include "CommonAssets.h"
class LogoScene : public BaseScene{
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

     CommonAssets *commonAssets;
    
    ofParameter<int>timeOut;
    float counter;
    ofParameter<string>counterString;
    float prevElapse;
private:
    ofVideoPlayer messageVideo;
};
#endif /* defined(__wlbankinteractive__LogoScene__) */
