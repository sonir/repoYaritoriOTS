//
//  Event.cpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#include "Event.hpp"

void Event::set(){
    
    std::cout << "Event:set" << std::endl;
    
};

int  Event::trigger(){
    
    std::cout << "Event:trigger" << std::endl;
    
};

int Event::trigger(void* args){
    
        int *num = (int *) args;
        std::cout << "Event:trigger with number (" << *num << ")" << std::endl;
    
}
