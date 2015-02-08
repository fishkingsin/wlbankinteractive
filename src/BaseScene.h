//
//  BaseScene.h
//  wlbankinteractive
//
//  Created by James Kong on 23/1/15.
//
//

#ifndef __wlbankinteractive__BaseScene__
#define __wlbankinteractive__BaseScene__
#include "ofxScene.h"
#include "ofMain.h"
typedef struct {
    int sceneID;
}toNextScene;
class BaseScene : public ofxScene
{
    public :
    virtual void createParticle(float x , float y , ofColor color){};
    ofParameterGroup paraGroup;
    ofEvent<toNextScene>toNextSceneEvent;

};

#endif /* defined(__wlbankinteractive__BaseScene__) */
