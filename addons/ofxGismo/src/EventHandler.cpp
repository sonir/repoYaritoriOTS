//
//  EventHandler.cpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#include "EventHandler.hpp"

void EventHandler::eventAdd(std::string event_name, Event *pEvent){
    
    events[event_name] = pEvent;
    
}


int EventHandler::bang(string event_name){
    
    if(events[event_name])
    {
        
        Event *tmp = events[event_name];
        return tmp->trigger();
        
    } else {
        
        cout << "ERR :: Unknown event named <" << event_name << "> was invoked." << endl;
        
    }
    
}


int EventHandler::bang(string event_name, void* args){

    if(events[event_name])
    {
        
        Event *tmp = events[event_name];
        return tmp->trigger(args);
        
    } else {
        
        lambdaBang(event_name, args);
//        cout << "ERR :: Unknown event named <" << event_name << "> was invoked." << endl;
        
    }
    
    
}

void EventHandler::lambdaBang(string event_name, void* args){

    if(lambdas[event_name])
    {
        
        return lambdas[event_name](args);
        
    } else {
        
        cout << "ERR :: Unknown event named <" << event_name << "> was invoked." << endl;
        return;
        
    }

    
//    return lambdas[event_name](args);
    
}

void EventHandler::lambdaAdd(string event_name, function <void (void*)> lambda) {
    
    lambdas[event_name] = lambda;
    
}
