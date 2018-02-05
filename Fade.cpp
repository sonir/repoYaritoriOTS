//
//  Fade.cpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#include "Fade.hpp"

using namespace std;

Fade::Fade(){
    
    init(DEFAULT_DURATION_MS);
    
}

Fade :: Fade(int ms){
    
    init(ms);
    
}


void Fade :: init (int ms){
    
    activated = false;
    this->set(ms);
    count = 0;
    now_rate = 0.0f;
    
}


float Fade::update(){
    
    if(!activated) return 0.0f;

    
    count ++;
    now_rate = (float)count / (float)count_end;
    
    //Limit until 1.0
    now_rate = limitter(now_rate, 1.0f);
    //If fade was end, deactivated
    if (now_rate == 1.0) activated = false;
    return now_rate;
    
}

void Fade::reset(){
    
    count = 0;
    activated = false;
    
}

void Fade::bang(){
    
//    this->reset();
    activated = true;
    
}


void Fade::set(int ms){
    
    duration_ms = ms;
    fps_in_ms = 1000 / FADE_FPS;
    count_end = duration_ms / fps_in_ms;
    
}
