//
//  particle.cpp
//
//  Created by momoha/rin on 2017/10/13.
//
//


#include "particle.hpp"

void Particle :: setupParticle(){
    
    for(int i = 0; i < MAX; i++){
        pos[i].set(ofRandom(0.0, 1.0), ofRandom(0.0, 1.0));
    }
    
    vbo.setVertexData(drawPos, MAX, GL_DYNAMIC_DRAW);
    
    particleNum = 0;    //0 - MAX
    attractor_x = 0.5;
    attractor_y = 0.5;
    modulation = 0.;
    mode = 1;
    size = 0.5;
    
}

void Particle :: updateParticle(){
    
    //pos & vel are defined as 0-1
    if(particleNum > 0){
        switch (mode)
        {
            case 1:
                blownianMotion();
                break;
                
            case 2:
                gravityMotion();
                break;
                
            case 3:
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
            
            drawPos[i].x = pos[i].x * ofGetWidth();
            drawPos[i].y = pos[i].y * ofGetHeight();

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

void Particle :: drawParticle(){
    
    glPointSize(size);
    glEnable(GL_BLEND);
    //enable addition synthesis(加算合成)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    vbo.draw(GL_POINTS, 0, particleNum);
    
}

void Particle :: blownianMotion(){
    
    for(int i = 0; i < MAX; i++){
        vel[i].set(modulation * 0.002 * ofRandom(-1.0, 1.0), modulation * 0.002 * ofRandom(-1.0, 1.0));
    }
    
}

void Particle :: gravityMotion(){
    
    for(int i = 0; i < MAX; i++){
        float a = -0.00001;
        vel[i].set(modulation * 0.002 * ofRandom(-1.0, 1.0), vel[i].y + a);
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
