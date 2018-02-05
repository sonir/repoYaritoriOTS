//
//  RippleDrawer.hpp
//  ripple
//
//  Created by moha with hana on 2017/12/30.
//
//

#ifndef RippleDrawer_hpp
#define RippleDrawer_hpp

#include "ofMain.h"
#include "timed_interpolation.hpp"
#include "ofxGismo.h"
#include "ScreenManager.hpp"
#include "animation_setup.hpp"


class RippleDrawer{
public:
    RippleDrawer();
    void setColor(float c);
    void initVertices();
    void initStatus();
    void init();
    void update();
    void bang(float x, float y, float size_ratio, float time_ratio);
    
    
    float centerX, centerY;
    bool isRunning;
    bool colorState;
    
    static const int res = 64;
    static const int rippleNum = 2;
    int targetAg;
    
    ofVec2f verts[res * rippleNum];
    ofIndexType indices[res * rippleNum * 2];
    ofFloatColor cols[res * rippleNum];
    
private:
    void updateColor();
    void updateVertex();
    
    float lag[rippleNum];    //1. <-> duration
    float sp_noise[rippleNum];   //conf of speed for second ripple
    float duration; //sec
    float radius;    //1. <-> CANVAS_HEIGHT
    static constexpr float theta = 2. * PI * 0.015625;   // / 64
    static constexpr float fadeOutRatio = 0.4;  //1 <-> duration
    
    float size_ratio, time_ratio;
    
    TimedInterpolation interpolation;   //return 0. to 1. during "duration"
    float currentTime;
    float currentRadius;
    
    float aspect;   //aspect ratio, acquired from gismomanager
    float color;
};

#endif /* RippleDrawer_hpp */
