//
//  MyScene_2.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 5/12/14.
//
//
#include "MyScene_2.h"
#include <stdio.h>
void MyScene_2::setup(){
    fbo.allocate(ofGetWidth(),ofGetHeight());
    fbo.begin();
    ofClear(0, 0, 0);
    fbo.end();
    //    ofTrueTypeFont::setGlobalDpi(72);
    
    font.loadFont("arialuni.ttf", 12, 1);
    
    //    font.setLineHeight(18.0f);
    
    
    charSet.push_back(L"ABC");
    charSet.push_back(L"•");
    charSet.push_back(L"▲▼◀◆");
    charSet.push_back(L"✖✕");
    charSet.push_back(L"@#%");
    charSet.push_back(L"oO◌◎");
    charSet.push_back(L"✦✩✪✭");
    charSet.push_back(L"◼");
    charSet.push_back(L"01");
    charSet.push_back(L"❆❇❋");
    charSet.push_back(L"/\\");
    
    
    currentCharSet = charSet[0];
    //        int step = 10;
    //        for(int i = 0 ; i < VIDEO_HEIGHT; i+=step)
    //        {
    //            for(int j = 0 ; j < VIDEO_WIDTH; j+=step)
    //            {
    //                myFonts.push_back(ofPtr<MyFont>(new MyFont));
    //                myFonts.back().get()->pos = ofPoint(j,i);
    //                myFonts.back().get()->pixelPos = ofPoint(j,i);
    //                myFonts.back().get()->offset = ofPoint(ofRandom(-5,5),ofRandom(-5,5));
    //                myFonts.back().get()->mChar = currentCharSet[(int)(ofRandom(0,currentCharSet.size()))];
    //                myFonts.back().get()->scale = ofRandom(0.1,5);
    //            }
    //        }
    isLive = true;
};


void MyScene_2::update(float dt){ //update scene 2 here
    if(NULL==grabber)
    {
        return;
        
    }
    if(isCapture || isLive)
    {
        grabber->update();
        ofPixels pixels = grabber->getPixelsRef();
        
        fbo.begin();
        
        int n = (isCapture)?10000:ofRandom(50,200);
        //    ofEnableDepthTest();
        //    ofEnableNormalizedTexCoords();
        float screenScale = ofGetWidth()*1.0f/VIDEO_WIDTH;
        for(int i = 0 ; i < n ;i++)
        {
            
            
            int x = (int)(ofRandom(0,VIDEO_WIDTH)) ;
            int y = (int)(ofRandom(0,VIDEO_HEIGHT));
            ofColor c = pixels.getColor(x,y);
            float scale = ofRandom(0.1,4);
            wstring mc;
            mc.append(currentCharSet,(int)(ofRandom(0,currentCharSet.size())),1);
            ofRectangle rect = font.getStringBoundingBox(mc, x, y);
            ofPushMatrix();
            ofTranslate((x-rect.width*0.5)*screenScale, (y+rect.height*0.5)*screenScale);
            ofScale(scale, scale);
            
            ofPushStyle();
            ofSetColor(c);
            
            font.drawString( mc,0,0);
            ofPopStyle();
            ofPopMatrix();
            
        }
        //    ofDisableNormalizedTexCoords();
        //    ofDisableDepthTest();
        fbo.end();
        isCapture = false;
    }
};


void MyScene_2::draw(){ //draw scene 2 here
    if(NULL==grabber)
    {
        return;
        
    }
    
    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
//    grabber->draw(0,0,160,120);
    //        ofPixels pixels = grabber->getPixelsRef();
    //        for(int i = 0 ; i < myFonts.size() ; i++)
    //        {
    //            ofPushStyle();
    //
    //            ofSetColor(pixels.getColor(myFonts[i].get()->pixelPos.x,myFonts[i].get()->pixelPos.y));
    //            font.drawString( myFonts[i].get()->mChar , myFonts[i].get()->pos.x , myFonts[i].get()->pos.y);
    //            ofPopStyle();
    //        }
    
};
void MyScene_2::keyPressed(int key)
{
    switch(key)
    {
        case 's':
        {
            grabber->videoSettings();
        }
            break;
        case OF_KEY_RETURN:
        {
            currentCharSet = charSet[(int)(ofRandom(0,charSet.size()))];
            wstring string_to_convert;
            
            //setup converter

            //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
            string converted_str ( currentCharSet.begin() , currentCharSet.end() );
            ofLogVerbose("Scene2") << "current uniString character set "<< converted_str;

        }
            break;
        case 'l':
            isLive = !isLive;
            if(!isLive)
            {
                isCapture = true;
            }
            break;
            case 'c':
            isCapture = true;
            break;
    }
}
void MyScene_2::mousePressed( int x, int y, int button ){
    
}

//scene notifications
void MyScene_2::sceneWillAppear( ofxScene * fromScreen ){  // reset our scene when we appear
};

//scene notifications
void MyScene_2::sceneWillDisappear( ofxScene * toScreen ){
}