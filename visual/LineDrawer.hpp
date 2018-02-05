//
//  LineDrawer.hpp
//  ccma_line
//
//  Created by Momoha Matsuhashi on 2018/01/05.
//
//

#ifndef LineDrawer_hpp
#define LineDrawer_hpp

#include "ScreenManager.hpp"
#include "ofMain.h"
#include "timed_interpolation.hpp"
#include "ofxGismo.h"
#include "animation_setup.hpp"


constexpr int VERT_NUM = TURN_NUM_MAX * 6 + 2;  //6 mins a bit more than aspect(5.4333)

class LineDrawer{
public:
    LineDrawer();
    
    void lineTo(float target_x, float target_y, float size);
    void invert();
    void setColor(float _c);
    void setEvents();
    
    posi_t myPos, targetPos;
    
    bool colorState;
    ofFloatColor color;
    
private:
    void update();
    
    int turn_num;
    float size;
    float currentPhase, preCurrentPhase, theta;
    
    ofVec2f verts[TURN_NUM_MAX + 2]; // + myPos + targetPos
    ofFloatColor cols[TURN_NUM_MAX + 2];
    ofVbo vbo;
    
    TimedInterpolation interpolation;
    
    float aspect;
};



#endif /* LineDrawer_hpp */
