#pragma once

#include <string>
#include <map>

#include "ofMain.h"
#include "ofxWebSocketEvents.h"

class ofxWebSocketReactor;

#include "json.h"

class ofxWebSocketProtocol
{
    friend class ofxWebSocketReactor;
    friend class ofxWebSocketServer;
    friend class ofxWebSocketClient;
    
public:
    ofxWebSocketProtocol();
    ~ofxWebSocketProtocol();
    
    virtual bool allowClient(const std::string name,
                             const std::string ip) const;
    
    void broadcast(const std::string& message);
    
    unsigned int idx;
    bool binary;
    
protected:  
    virtual void execute() {}
    
    virtual void onconnect  (ofxWebSocketEvent& args);
    virtual void onopen     (ofxWebSocketEvent& args);
    virtual void onclose    (ofxWebSocketEvent& args);
    virtual void onidle     (ofxWebSocketEvent& args);
    virtual void onmessage  (ofxWebSocketEvent& args);
    virtual void onbroadcast(ofxWebSocketEvent& args);
    
    ofEvent<ofxWebSocketEvent> onconnectEvent;
    ofEvent<ofxWebSocketEvent> onopenEvent;
    ofEvent<ofxWebSocketEvent> oncloseEvent;
    ofEvent<ofxWebSocketEvent> onidleEvent;
    ofEvent<ofxWebSocketEvent> onmessageEvent;
    ofEvent<ofxWebSocketEvent> onbroadcastEvent;
    
    bool defaultAllowPolicy;
    std::map<std::string, bool> allowRules;
    
    ofxWebSocketReactor* reactor;
    
private:
    Json::Reader reader;
    
    void _onconnect   (ofxWebSocketEvent& args);
    void _onopen      (ofxWebSocketEvent& args);
    void _onclose     (ofxWebSocketEvent& args);
    void _onidle      (ofxWebSocketEvent& args);
    void _onmessage   (ofxWebSocketEvent& args);
    void _onbroadcast (ofxWebSocketEvent& args);
    
    bool _allowClient(const std::string name,
                      const std::string ip) const;
};
