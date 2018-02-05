//
//  MotionEvents.hpp
//  yaritori
//
//  Created by Hana on 2018/01/05.
//
//

#ifndef MotionEvents_hpp
#define MotionEvents_hpp

#include "MotionManager.hpp"
#include "RippleManager.hpp"
//#include "Sound.hpp"


class Solo : public Event {
public:
    Solo() {
        //sender.setup(SOUND_HOST, SOUND_PORT);
    }
    
    int trigger(void *arg) {        
        param_u *params = (param_u *)arg;
        int id = params[0].ival;
        float duration = params[1].fval;
        
        motionManager->addSolo(id, duration);
        
        return 1;
    };
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        motionManager = pMotion;
    }
    
private:
    MotionManager* motionManager;
    //ofxOscSender sender;
};


class MotionEvents : public Event {
public:
    Solo solo;
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        solo.setMotionManagerPtr(pMotion);
    }
};


#endif /* MotionEvents_hpp */
