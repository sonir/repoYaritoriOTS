 //
//  particle.hpp
//
//  Created by momoha/rin on 2017/10/13.
//
//
#ifndef particle_hpp
#define particle_hpp

#include "ofMain.h"


typedef enum mode_e {BROWNIAN, GRAVITY, GATHERING} mode_e;

class Particle {
    
public:
    
    
    int screen_width;
    int screen_height;

    void setup(int w, int h);
               
    void update();
    void draw();
    void drawLog();
    
    void blownianMotion();
    void gravityMotion();
    void gatheringMotion();
    
    static const int MAX = 15000;   //particle max num
    ofVec2f pos[MAX], vel[MAX], drawPos[MAX];
    int particleNum;
    
    float attractor_x, attractor_y, modulation, size, attractor_a;   //0.0 - 1.0
    
    ofVbo vbo;
    
//    int mode;
    mode_e mode;
    bool state_log;

};

#endif /* particle_hpp */
