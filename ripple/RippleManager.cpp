//
//  Ripple.cpp
//  ripple
//
//  Created by Momoha Matsuhashi on 2017/12/09.
//
//

#include "RippleManager.hpp"

RippleManager::RippleManager(){
    init();
    
    colorState = true;
    for(int i = 0; i < NUM; i++){
        ripples[i].isRunning = false;
        ripples[i].colorState = colorState;
    }
    
    setEvents();
}

void RippleManager::setEvents() {
    GismoManager& gismo = GismoManager::getInstance();
    
    auto colorEvent = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        float c = params[0].fval;
        
        this->setColor(c);
    };
    
    gismo.lambdaAdd("/rippleColor", colorEvent);
    
    auto agRipple = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        float id = params[0].ival;
        float size = params[1].fval;
        float time = params[2].fval;
        
        this->agBang(id, size, time);   //FIRE!!!!!!!!!!!!!!!!
    };
    
    gismo.lambdaAdd("/ag_ripple", agRipple);
}

void RippleManager::setColor(float c) {
    for(int i = 0; i < NUM; i++){
        ripples[i].setColor(c);
    }
}


void RippleManager::initVertices(){
    for(int k = 0; k < NUM; k++){
        for(int j = 0; j < rippleNum; j++){
            for(int i = 0; i < res; i++){
                verts[k * res * rippleNum + j * res + i].set(0.5 * ORIGINAL_HEIGHT, 0.5 * ORIGINAL_HEIGHT);
                cols[k * res * rippleNum + j * res + i] = ofFloatColor(0., 0., 0., 1.);
            }
        }
    }
}

void RippleManager::initIndices(){
    //Set indices
    int n = 0;
    for(int k = 0; k < NUM; k++){
        for(int j = 0; j < rippleNum; j++){
            for(int i = 0; i < res - 1; i++){
                indices[n] = k * res * rippleNum + res * j + i;
                n++;
                indices[n] = k * res * rippleNum + res * j + i + 1;
                n++;
            }
            indices[n] = k * res * rippleNum + res * (j+1) - 1;
            n++;
            indices[n] = k * res * rippleNum + res * j;
            n++;
        }
    }
}

void RippleManager::initVbo(){
    initVertices();
    initIndices();
    
    vbo.setIndexData(indices, res * rippleNum * NUM * 2, GL_STATIC_DRAW);
    vbo.setColorData(cols, res * rippleNum * NUM, GL_DYNAMIC_DRAW);
    vbo.setVertexData(verts, res * rippleNum * NUM, GL_DYNAMIC_DRAW);
}

void RippleManager::initStatus(){
    activeNumCounter = 0;
}

void RippleManager::init(){
    initVbo();
    initStatus();
}

void RippleManager::update(){
    for(int i = 0; i < NUM; i++){
        ripples[i].update();
    }
    
    if(motion->isSoloMode()) { //When solo, update only ag ripples
        activeNumCounter = 0;
        for(int j = 0; j < AG_MAX; j++){
            if(ripples[j].isRunning && motion->isSolo[ripples[j].targetAg]){
                for(int i = 0; i < res * rippleNum; i++){
                    verts[activeNumCounter * res * rippleNum + i] = ripples[j].verts[i];
                    cols[activeNumCounter * res * rippleNum + i] = ripples[j].cols[i];
                }
                activeNumCounter++;
            }
        }
    } else {
        activeNumCounter = 0;
        for(int j = 0; j < NUM; j++){
            if(ripples[j].isRunning == true){
                for(int i = 0; i < res * rippleNum; i++){
                    verts[activeNumCounter * res * rippleNum + i] = ripples[j].verts[i];
                    cols[activeNumCounter * res * rippleNum + i] = ripples[j].cols[i];
                }
                activeNumCounter++;
            }
        }
    }
    
    vbo.updateVertexData(verts, res * rippleNum * activeNumCounter);
    vbo.updateColorData(cols, res * rippleNum * activeNumCounter);
}
void RippleManager::draw(){
    update();
    glLineWidth(lineWidth);
    vbo.drawElements(GL_LINES, res * rippleNum * activeNumCounter * 2);
}

void RippleManager::agBang(int id, float size, float time) {
    int index = 0;
    
    while (ripples[index].isRunning) {
        index++;
        if (AG_MAX <= index) {
            index = 0;
            break;
        }
    }
    
    
    
    ag_t* ag = gismo.getAgent(id);
    ripples[index].targetAg = id;
    ripples[index].bang(ag->posi.x, ag->posi.y, size, time);
}

void RippleManager::bang(float posX, float posY, float size_ratio, float time_ratio){
    int index = AG_MAX;
    while(ripples[index].isRunning == true){
        index++;
        if(index > NUM){
            index = AG_MAX;
            break;
        }
    }
    
    ripples[index].bang(posX, posY, size_ratio, time_ratio);
}
void RippleManager::invert(){
    colorState = !colorState;
    for(int i = 0; i < NUM; i++){
        ripples[i].colorState = colorState;
    }
}


int RippleManager::trigger(void* args) {    // To call from eventhandler
    float *val = (float *)args;
    
    this->bang(val[0], val[1], val[2], val[3]); //FIRE!!!!!!!!!!!!!!
    
    return 1;
}
