//
//  Metro.hpp
//  yaritori
//
//  Created by sonir on 1/12/18.
//
//

#ifndef Metro_hpp
#define Metro_hpp

#include <stdio.h>
#include "slMetro.h"
#include "ofxGismo.h"

class Metro : public Event{
    
public:
    
    Metro(float dur){
        
        metro = new slMetro(dur);
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        gismo.eventAdd("/fps", this);
    };
    
    int trigger(void *args){
        
        float *tmp = (float *)args;
        this->set(*tmp);
        
    }
    
    //Variables
    slMetro *metro;
    bool stop = false;
    
    //Methods
    void set(float dur);
    bool update();

    
};

#endif /* Metro_hpp */
