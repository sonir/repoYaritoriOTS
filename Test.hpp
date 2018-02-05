//
//  Test.hpp
//  yaritori
//
//  Created by sonir on 12/27/17.
//
//

#ifndef Test_hpp
#define Test_hpp

#include <stdio.h>
#include <cassert>
#include "ofxGismo.h"
#include "ag_shape.h"
//#include "Sound.hpp"
#include "drawAgents.hpp"
#include "RippleManager.hpp"
#include "Shape2Agent.hpp"
#include "Performance.hpp"
#include "getArraySize.h"
#include "SoundTrigger.hpp"


class Test {

    public:
        Test();
        void setup();
        void run();
        void runSubTest(void* args);

        void update();
    
        //Visual
        void runVisualTest(visual_container_t* visual);
        void invert();
        void solo();
    
    
        void createShape(ag_shape_t* shape);

    
    
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
//        Sound *sound;
//        SoundTrigger soundTest;
    


    //Visual
    RippleManager *ripple;
    EventHandler visEvents;
        bool isSolo;

    
        int arg1;
        int arg2;

    
};




#endif /* Test_hpp */
