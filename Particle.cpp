//
//  particle.cpp
//
//  Created by momoha/rin on 2017/10/13.
//
//


#define PARTICLE_ALPHA_DEFAULT 0.8
#define GRAVITY_SPD_ACC -0.00001
#define GRAVITY_SPD_LIMIT -0.008

#include "Particle.hpp"

void Particle :: setup(int w, int h){

    //Set the default screen
    screen_width = w;
    screen_height = h;
    
    for(int i = 0; i < MAX; i++){
        pos[i].set(ofRandom(0.0, 1.0), ofRandom(0.0, 1.0));
    }
    
    vbo.setVertexData(drawPos, MAX, GL_DYNAMIC_DRAW);
    
    particleNum = 0;    //0 - MAX
    attractor_x = 0.5;
    attractor_y = 0.5;
    modulation = 0.;
    mode = BROWNIAN;
    size = 0.5;
    
}

void Particle :: update(){
    
    //pos & vel are defined as 0-1
    if(particleNum > 0){
        switch (mode)
        {
            case BROWNIAN:
                blownianMotion();
                break;
                
            case GRAVITY:
                gravityMotion();
                break;
                
            case GATHERING:
                gatheringMotion();
                break;
        }
        
        for(int i = 0; i < MAX; i++){
            pos[i] += vel[i];
            
            //boundary condition
            if(pos[i].x < 0.0){
                pos[i].x = 1.0;
            }
            if(pos[i].x > 1.0){
                 pos[i].x = 0.0;
            }
            if(pos[i].y < 0.0){
                pos[i].y = 1.0;
            }
            if(pos[i].y > 1.0){
                pos[i].y = 0.0;
            }
            
            drawPos[i].x = pos[i].x * screen_width;
            drawPos[i].y = pos[i].y * screen_height;

        }
        
        vbo.updateVertexData(drawPos, MAX);
    }
    
    if(particleNum < 0){
        particleNum = 0;
    }
    if(particleNum > MAX){
        particleNum = MAX;
    }
    
}

void Particle :: draw(){
    
    if(particleNum==0){
        
        return;
    }
    
    glPointSize(size);
    glEnable(GL_BLEND);
    //enable addition synthesis(加算合成)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    glColor4f(1.0f, 1.0f, 1.0f, PARTICLE_ALPHA_DEFAULT);
    vbo.draw(GL_POINTS, 0, particleNum);
    
}

void Particle :: blownianMotion(){
    
    for(int i = 0; i < MAX; i++){
        vel[i].set(modulation * 0.002 * ofRandom(-1.0, 1.0), modulation * 0.002 * ofRandom(-1.0, 1.0));
    }
    
}

void Particle :: gravityMotion(){
    
    for(int i = 0; i < MAX; i++){
//        float a = -0.00001;
        float next_y;
        if(vel[i].y <= GRAVITY_SPD_LIMIT){
            vel[i].y = GRAVITY_SPD_LIMIT;
            next_y = vel[i].y;
        }else{
            
            next_y = vel[i].y + GRAVITY_SPD_ACC;
        }
        
        vel[i].set(modulation * 0.002 * ofRandom(-1.0, 1.0), next_y);
    }
    
}

void Particle :: gatheringMotion(){
    
    for(int i = 0; i < MAX; i++){
        float a = -0.00002;
        float theta = atan2(drawPos[i].y - attractor_y, drawPos[i].x - attractor_x);
        float dist = ofDist(drawPos[i].x, drawPos[i].y, attractor_x, attractor_y);
        if(dist < 100.0 && vel[i].length() > 0.004){
            vel[i] = vel[i].normalize() * 0.004;
        }
        vel[i].x += a * cos(theta) + modulation * 0.0002 * ofRandom(-1.0, 1.0);
        vel[i].y += a * sin(theta) + modulation * 0.0002 * ofRandom(-1.0, 1.0);
        
        //attractorの示すposを中心に単振動する。しきい値より遠い位置から近づいてくる粒に関しては、しきい値に到達した際に減速して、最終的にattractorになんとなく集まってくる感じになる。
    }
    
}
