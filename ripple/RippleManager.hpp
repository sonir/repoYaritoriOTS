//
//  rippleDrawer.hpp
//  ripple_1
//
//  Created by Momoha Matsuhashi on 2017/12/12.
//
//

#ifndef RippleManager_hpp
#define RippleManager_hpp

#include "ofMain.h"
#include "RippleDrawer.hpp"
#include "ofxGismo.h"
#include "MotionManager.hpp"

class RippleManager : public Event {
public:
    RippleManager();
    void setEvents();
    void setColor(float c);
    
    void initVertices();
    void initIndices();
    void initVbo();
    void initStatus();
    void init();
    
    void update();
    void draw();
    
    void agBang(int id, float size, float time);
    void bang(float posX, float posY, float size_ratio, float time_ratio);  //define each value as 0. - 1.
    int trigger(void *args);     // To be called from eventhandler
    
    void invert();
    
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        motion = pMotion;
    }
    
    
private:
    static constexpr float lineWidth = 200.0; //pixel
    
    static const int res = 64;
    static const int rippleNum = 2;
    static const int RIPPLE_MAX = 1000;
    static const int NUM = AG_MAX + RIPPLE_MAX; //max num of ripples that can be drawn at once
    
    bool colorState;    //true: black, false: white(ripples)
    float color;
    
    int activeNumCounter;
    
    RippleDrawer ripples[NUM];
    
    ofVec2f verts[res * rippleNum * NUM];
    ofIndexType indices[res * rippleNum * NUM * 2];
    ofFloatColor cols[res * rippleNum * NUM];
    ofVbo vbo;
    
    GismoManager& gismo = GismoManager::getInstance();
    MotionManager* motion;
};


#endif /* RippleDrawer_hpp */
