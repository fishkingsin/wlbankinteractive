//
//  VideoGrabberManager.h
//  wlbankinteractive
//
//  Created by Kong king sin on 2/1/15.
//
//

#ifndef __wlbankinteractive__VideoGrabberManager__
#define __wlbankinteractive__VideoGrabberManager__
#include "ofMain.h"
#include "IPVideoGrabber.h"
#include "Constants.h"
#include "ofxXmlSettings.h"
class IPCameraDef
{
public:
    IPCameraDef()
    {
    }
    
    IPCameraDef(const std::string& url): _url(url)
    {
    }
    
    IPCameraDef(const std::string& name,
                const std::string& url,
                const std::string& username,
                const std::string& password):
    _name(name),
    _url(url),
    _username(username),
    _password(password)
    {
    }
    
    void setName(const std::string& name) { _name = name; }
    std::string getName() const { return _name; }
    
    void setURL(const std::string& url) { _url = url; }
    std::string getURL() const { return _url; }
    
    void setUsername(const std::string& username) { _username = username; }
    std::string getUsername() const { return _username; }
    
    void setPassword(const std::string& password) { _password = password; }
    std::string getPassword() const { return _password; }
    
    
private:
    std::string _name;
    std::string _url;
    std::string _username;
    std::string _password;
};
using ofx::Video::IPVideoGrabber;
using ofx::Video::SharedIPVideoGrabber;

class VideoGrabberManager
{
public:
    void setup();
    void update();
    void draw();
    std::vector<SharedIPVideoGrabber> grabbers;
    void loadCameras();
    IPCameraDef& getNextCamera();
    std::vector<IPCameraDef> ipcams; // a list of IPCameras
    int nextCamera;
    ofFbo videoFbo;
    ofVideoPlayer videoPlayer;
};

#endif /* defined(__wlbankinteractive__VideoGrabberManager__) */
