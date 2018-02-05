//
//  Buffer2Csv.hpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#ifndef Buffer2Csv_hpp
#define Buffer2Csv_hpp

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include "ofxGismo.h"
#include "ag_shape.h"
#include "SoundTrigger.hpp"

class Buffer2Csv {
    
    
    public:
    
        Buffer2Csv (){
            

            
        }
    
        void saveAgents(ag_t *agents, int index_count, string withFile);
        void saveShapes(ag_shape_t *shapes, int index_count, string withFile);
        void saveSounds(sound_t *sounds, int index_count, string withFile);
    
    
        //Variables
        GismoManager& gismo = GismoManager::getInstance();
    
    
    
};

#endif /* Buffer2Csv_hpp */
