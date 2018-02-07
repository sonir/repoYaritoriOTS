//
//  TimerTimer.hpp
//  yaritori
//
//  Created by uozm on 2018/02/08.
//
//

#ifndef TimerTimer_hpp
#define TimerTimer_hpp

#define QUIT_HOUR 18
#define QUIT_MINUTES 0


#include <stdio.h>
#include "ofMain.h"
#include "ofxGismo.h"

class TimeTimer {
    
public:
    TimeTimer(int h, int m, string e_name){
        
        hour = h;
        minutes = m;
        event_name = e_name;
        
        // -1 is wild card of hour and minutes 
        
    }
    
    void update();
    
    GismoManager& gismo = GismoManager::getInstance();
    int hour;
    int minutes;
    string event_name;
    bool isPrevious = false;
    
    
};

#endif /* TimerTimer_hpp */
