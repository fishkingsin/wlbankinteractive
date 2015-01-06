//
//  VideoGrabberManager.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 2/1/15.
//
//

#include "VideoGrabberManager.h"
void VideoGrabberManager::setup()
{
    loadCameras();
    // initialize connection
    for(std::size_t i = 0; i < ipcams.size(); i++)
    {
        IPCameraDef& cam = getNextCamera();
        
        SharedIPVideoGrabber c = IPVideoGrabber::makeShared();
        
        // if your camera uses standard web-based authentication, use this
        // c->setUsername(cam.username);
        // c->setPassword(cam.password);
        
        // if your camera uses cookies for authentication, use something like this:
        // c->setCookie("user", cam.username);
        // c->setCookie("password", cam.password);
        
        c->setCameraName(cam.getName());
        c->setURI(cam.getURL());
        c->connect(); // connect immediately
        
        // if desired, set up a video resize listener
        //        ofAddListener(c->videoResized, this, &ofApp::videoResized);
        
        grabbers.push_back(c);
        
    }
    
    videoFbo.allocate(VIDEO_WIDTH*3,VIDEO_HEIGHT,GL_RGB);
    //videoPlayer.loadMovie("movies/background.mp4");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    videoPlayer.play();
    
}

//------------------------------------------------------------------------------

IPCameraDef& VideoGrabberManager::getNextCamera()
{
    nextCamera = (nextCamera + 1) % ipcams.size();
    return ipcams[nextCamera];
}

//------------------------------------------------------------------------------

void VideoGrabberManager::loadCameras()
{
    
    // all of these cameras were found using this google query
    // http://www.google.com/search?q=inurl%3A%22axis-cgi%2Fmjpg%22
    // some of the cameras below may no longer be valid.
    
    // to define a camera with a username / password
    //ipcams.push_back(IPCameraDef("http://148.61.142.228/axis-cgi/mjpg/video.cgi", "username", "password"));
    
    ofLog(OF_LOG_NOTICE, "---------------Loading Streams---------------");
    
    ofxXmlSettings XML;
    
    if(XML.loadFile("streams.xml"))
    {
        
        XML.pushTag("streams");
        std::string tag = "stream";
        
        int nCams = XML.getNumTags(tag);
        
        for(std::size_t n = 0; n < nCams; n++)
        {
            
            IPCameraDef def(XML.getAttribute(tag, "name", "", n),
                            XML.getAttribute(tag, "url", "", n),
                            XML.getAttribute(tag, "username", "", n),
                            XML.getAttribute(tag, "password", "", n));
            
            
            std::string logMessage = "STREAM LOADED: " + def.getName() +
            " url: " +  def.getURL() +
            " username: " + def.getUsername() +
            " password: " + def.getPassword();
            
            ofLogNotice() << logMessage;
            
            ipcams.push_back(def);
            
        }
        
        XML.popTag();
        
    }
    else
    {
        ofLog(OF_LOG_ERROR, "Unable to load streams.xml.");
    }
    
    ofLog(OF_LOG_NOTICE, "-----------Loading Streams Complete----------");
    
    nextCamera = ipcams.size();
}
void VideoGrabberManager::update()
{
    videoPlayer.update();
    // update the cameras
    for(std::size_t i = 0; i < grabbers.size(); i++)
    {
        grabbers[i]->update();
    }
    
    videoFbo.begin();
    ofSetColor(ofColor::white);
    for(std::size_t i = 0; i < grabbers.size(); i++)
    {
        grabbers[i]->draw(i*VIDEO_WIDTH, 0,VIDEO_WIDTH,VIDEO_HEIGHT);
    }
    videoFbo.end();
}
void VideoGrabberManager::draw()
{
    
    ofSetColor(ofColor::white);
    videoFbo.draw(0,0,ofGetWidth(),ofGetHeight());
    
}