//
//  Network.hpp
//  yaritori
//
//  Created by sonir on 12/23/17.
//
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include "ofxOsc.h"
#include "ofxGismo.h"
#include "ag_shape.h"

// listen on port 12345
#define IN_PORT 57140 //8002//56138
#define NUM_MSG_STRINGS 20

//Sending something
#define OUT_PORT 8001
#define OUT_IP "127.0.0.1"

//Decodeing incoming shapes
#define INDEX_OF_COLOR 0
#define INDEX_OF_NODE 1

//Duration Time
#define INVERT_DURATION 0.5

typedef struct system_state_t{
    
    int ag_count=0;
    int end_hour = 18;
    int end_minutes = 1;
    
}system_state_t;



class Network {
    
    public:
        //ofxOscReceiver sender;
        void setup();
        void update();
    
        ofTrueTypeFont font;
        ofxOscReceiver receiver;
        
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
        
        int mouseX, mouseY;
        string mouseButtonState;
        
        ofImage receivedImage;
    
    
        //Sending
        ofxOscSender sender;
//        void sendAgentCount(int num);
        void sendSystemState(system_state_t states);

    
        void setShapePtr(ag_shape_t* _pShapes) {
            pShapes = _pShapes;
        }
    
    
    
    
    

    
    private:
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        ag_shape_t shape; // for shape receiving
        void dispParams(ag_shape_t shape); //For receiving test of shape from server
    
    ag_shape_t* pShapes;    //Pointer of shape container

    
};


#endif /* Network_hpp */

