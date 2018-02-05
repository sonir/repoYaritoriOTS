//
//  Metro.cpp
//  yaritori
//
//  Created by sonir on 1/12/18.
//
//

#include "Metro.hpp"

void Metro::set(float dur){
    
    metro->set(dur);
    
}

bool Metro::update(){
    
    if(stop)return false;
    
    if(metro->alart()) return true;
    else return false;
    
    
}
