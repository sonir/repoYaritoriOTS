//
//  particle.hpp
//
//  Created by momoha/rin on 2017/10/13.
//
//
#ifndef particle_hpp
#define particle_hpp

#include "ofMain.h"

class Particle {
public:
    
    void setupParticle();
    void updateParticle();
    void drawParticle();
    void drawLog();
    
    void blownianMotion();
    void gravityMotion();
    void gatheringMotion();
    
    static const int MAX = 15000;   //particle max num
    ofVec2f pos[MAX], vel[MAX], drawPos[MAX];
    int particleNum;
    
    float attractor_x, attractor_y, modulation, size, attractor_a;   //0.0 - 1.0
    
    ofVbo vbo;
    
    int mode;
    bool state_log;

};

#endif /* particle_hpp */
