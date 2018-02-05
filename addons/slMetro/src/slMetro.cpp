//
//  slMetro.cpp
//  printAgent
//
//  Created by isana137 on 2/5/14.
//
//

#include "slMetro.h"

slMetro::slMetro (float f_sec)
{
    //Default interval is 1000
    interval = f_sec;
    //Set now time as start time
    start = ofGetElapsedTimef();
}


void slMetro::set(float val)
{
    //Set the val as interval
    interval = val;
    //Reset the starting time
    start = ofGetElapsedTimef();
    
}

void slMetro::resetStart()
{

    start = ofGetElapsedTimef();
    stop_flg = false;
}

void slMetro::stop(){
    
    stop_flg = true;
    
}


bool slMetro::alart()
{
    
    if(stop_flg) return false;
    
    float now = ofGetElapsedTimef();
    float diff = now - start;
    
    if(diff >= interval)
    {
        start = ofGetElapsedTimef();
        return true;
    }
    else return false;
    
}

bool slMetro::alartWithoutReset()
{
    
    float now = ofGetElapsedTimef();
    float diff = now - start;
    
    if(diff >= interval)
    {
        return true; //Do not reset
    }
    else return false;
    
    
}

float slMetro::progress()
{
    float now = ofGetElapsedTimef();
    float diff = now - start;
 
    return diff;
    
}

float slMetro::remain()
{
    float now = ofGetElapsedTimef();
    float diff = now - start;
    
    return (interval - diff);
    
}