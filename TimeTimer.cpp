//
//  TimerTimer.cpp
//  yaritori
//
//  Created by uozm on 2018/02/08.
//
//

#include "TimeTimer.hpp"

void TimeTimer::update(){
    
    
    if(ofGetHours()==hour || hour == -1){
        
        
        if(ofGetMinutes()==minutes || minutes == -1){
            
            if(!isPrevious){
    
                int ival = 1;
                cout << "TimerEvent" << event_name << endl;
                gismo.bang(event_name, &ival);
                isPrevious = true;
                
            }
            
        }else {
            
            isPrevious = false;
            
        }
        
        
        
    }else{
        
        
        isPrevious = false;
        
        
    }
    
//    if( ofGetHours()==hour && ofGetMinutes()==minutes){
//        
//        if(!isPrevious){
//            
//            int ival = 1;
//            cout << "TimerEvent" << event_name << endl;
//            gismo.bang(event_name, &ival);
//            isPrevious = true;
//            
//        }
//        
//        
//    }else {
//        
//        isPrevious = false;
//    }
    
    
}
