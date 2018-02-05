//
//  EventHandler.hpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#pragma once
//#ifndef EventHandler_hpp
//#define EventHandler_hpp

#include <stdio.h>
#include <iostream>
#include <map> //Using map to use key based array
#include <cassert>
#include "Event.hpp"

using namespace std;

class EventHandler {
    
    public:
        void eventAdd(string event_name, Event *pEvent);
        int bang(string event_name);
        int bang(string event_name, void* args);

        void lambdaAdd(string event_name, function <void (void*)> lambda);
        void lambdaBang(string event_name, void* args);

    
    protected:
        map <string, Event*> events;
        map <string, function <void (void*)>> lambdas;

    
};


class EvTest : public Event {

    public:
    
        EvTest(){
            
            //Lambda test now
            auto func0 = [&](void *args){ lambdaTrigger(args);};
            
        }
    
    
        int trigger(){
            
            cout << "EvTest::Trigger" << endl;
            return 137;
            
        }

        
        int trigger(void *args){

                int *foo = (int *)args;
                assert(foo[0]==0);
                assert(foo[1]==1);
                assert(foo[2]==2);
                return 138;

        }

        void lambdaTrigger(void *args){
         
            //Lambda test now
            param_u *params = (param_u *)args;
            cout << params[0].ival <<endl;
            
        }
    
        function <void (void*)> *func;
    
};

//#endif /* EventHandler_hpp */
