//
//  ScreenManager.hpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "ofMain.h"
#include "timed_interpolation.hpp"
#include "screen_setup.h"
#include "ofxGismo.h"
#include "drawer.hpp"
#include "animation_setup.hpp"

//Define Structs
typedef struct pos_t {
    
    float x;
    float y;
    
} pos_t;


enum invert_state_e {
    INVERT_STATE_DEFAULT,
    INVERT_STATE_INVERTED,
    INVERT_STATE_FLASH,
};


typedef enum{ UP, RIGHT, DOWN, LEFT } shake_direction_e;

constexpr int WINDOW_NUM = 3;

class ScreenManager {
public:
    ScreenManager();
    void setup();
    void begin();
    void end();
    void draw();
    
    void setTrimPos(int window, float x, float y);
    void resetTrimPos(int window);
    
    void setMask(int window, int vertexId, float x, float y);
    void maskUpdate();
    void mask();
    
    void shake(int window, shake_direction_e direction);
    void swap(int window, float x, float y);
    float getSwapCurve(float val);
    void setShakeDuration(float go, float out, float back);
    
    void setBackground(float c);
    void setAllColor(float _bgColor);
    void drawBackground();
    
    
    //FullSCreen
    void setFullScreen();
    void setFullScreenConfig();
    ofColor getDrawColor();
    
    float width, height;
    
private:
    void init();
    void initFbo();
    void initStatus();
    void initMask();
    
    void shake_cal();
    void setEvents();
    
    ofVbo mask_vbo;
    ofIndexType mask_indices[6 * 4 * 3];
    ofVec2f mask_pos[4 * 3];
    ofVec2f mask_verts[8 * 3];
    ofFloatColor mask_cols[8 * 3];
    
    ofFbo fbo;
    float texture_diffPos_x[3];
    float texture_diffPos_y[3];
    float texture_pos_x[3];
    float texture_pos_y[3];
    
    pos_t pos[3];  //up-left point of window
    
    
    float shakeDur_go, shakeDur_out, shakeDur_back;    //msec
    
    pos_t startPos[3];    //pos when called as start pos
    pos_t endPos[3];
    int state_w[3];
    int state_h[3];
    TimedInterpolation interpolation_w[3];
    TimedInterpolation interpolation_h[3];

    
    //Invert of color and bg
    void updateColor();
    void updateInvert();
    TimedInterpolation invertTimer;
    float bgColor;  //Background Color;
    bool isInvert;
    bool drawFlash, drawInverted;
    invert_state_e invertState;
    bool timerOn;
    bool invertOnNext;
    float nextDuration;
//    ofShader shader;
    
    
};

#endif /* ScreenManager_hpp */
