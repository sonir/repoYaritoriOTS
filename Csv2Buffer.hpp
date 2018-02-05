//
//  Csv2Buffer.hpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#ifndef Csv2Buffer_hpp
#define Csv2Buffer_hpp

#define AG_NUM_OFFSET 0

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "ofMain.h"
#include "ag_shape.h"
#include "ofxGismo.h"
#include "Network.hpp"
#include "SoundTrigger.hpp"


typedef enum {LOG_AGID, LOG_ACTIVE, LOG_POSI_X, LOG_POSI_Y, LOG_SIZE, LOG_VIEW, LOG_MOV, LOG_CONDITION, LOG_SPD_X, LOG_SPD_Y, LOG_INTERACT_WITH} log_ag_param_e ;

class Csv2Buffer {
    
    public:
        Csv2Buffer(){
            
            
        }
        void test();
        void loadAgents(ag_t *agents, string withFile);
        void loadShapes(string withFile);
        void loadSounds(string withFile);
    
//        void loadShapes(ag_shape_t *shapes, string withFile);
    
    private:
        string nullCheck(string word);
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance


    
};

#endif /* Csv2Buffer_hpp */
