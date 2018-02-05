//
//  RippleDrawer.cpp
//  ripple
//
//  Created by moha with hana on 2017/12/30.
//

#include "RippleDrawer.hpp"

RippleDrawer::RippleDrawer(){
    centerX = 0.f;
    centerY = 0.f;
    color = 0.0;
    size_ratio = 1.0;
    time_ratio = 1.0;
    
    init();
    
    GismoManager& gismo = GismoManager::getInstance();
    aspect = gismo.width_rate;
}

void RippleDrawer::setColor(float c) {
    color = c;
    
}

void RippleDrawer::initVertices() {
    //init verts
    for(int j = 0; j < rippleNum; j++){
        for(int i = 0; i < res; i++){
            verts[j * res + i].set(centerX * BASE_WIDTH, centerY * BASE_HEIGHT);
//            verts[j * res + i].set(centerX * ORIGINAL_WIDTH, centerY * ORIGINAL_HEIGHT);
            cols[j * res + i] = ofFloatColor(0., 0., 0., 1.);
        }
    }
}

void RippleDrawer::initStatus() {
    //Set default duration
    duration = duration_default * 1000. * time_ratio;   //sec -> msec
    //Set default radius
    radius = radius_default * size_ratio;
    
    lag[0] = 0.;
    sp_noise[0] = 1.;
    for(int i = 1; i < rippleNum; i++){
        lag[i] = (lagMax - lagMin) * frand() + lagMin;
        sp_noise[i] = (sp_noiseMax - sp_noiseMin) * frand() + sp_noiseMin;
    }
    currentRadius = 0.;
}

void RippleDrawer::init(){
    initVertices();
    initStatus();
}

void RippleDrawer::updateColor(){
    if(currentTime < 1.0){
        float alpha;
        if(currentTime < 1. - fadeOutRatio){
            alpha = 1.f;
        }else{
            alpha = - (currentTime - (1. - fadeOutRatio)) / fadeOutRatio + 1.;
        }
        
        
        ofFloatColor col;
        if(color == 0.0){
            alpha *= RIPPLE_ALPHA_FIX_BLACK;
            col = ofFloatColor(color, color, color, alpha);
        }else{
            alpha *= RIPPLE_ALPHA_FIX_WHITE;
            col = ofFloatColor(color, color, color, alpha);
        }
        for(int j = 0; j < rippleNum; j++){
            for(int i = 0; i < res; i++){
                cols[j * res + i] = col;
            }
        }
    }
}

void RippleDrawer::updateVertex(){
    for(int j = 0; j < rippleNum; j++){
        //integrate "r_speed = speed * (1. - currentTime);"
        currentRadius = radius * sp_noise[j] * ((currentTime - lag[j]) - 0.5 * (currentTime - lag[j]) * (currentTime - lag[j]));
        for(int i = 0; i < res; i++){
            float th = theta * i;
            if(currentTime - lag[j] > 0){
                float x = centerX * BASE_WIDTH + currentRadius * cos(th) * BASE_HEIGHT;
//                float x = centerX * ORIGINAL_WIDTH + currentRadius * cos(th) * ORIGINAL_HEIGHT;
                float y = centerY * BASE_HEIGHT + currentRadius * sin(th) * BASE_HEIGHT;
                verts[j * res + i].set(x, y);
            }
        }
    }
    
}

void RippleDrawer::update(){
    if(isRunning == true){
        currentTime = interpolation.get();  //0. - 1.
        if(currentTime < 1.0){
            updateColor();
            updateVertex();
        }else{
            isRunning = false;
        }
    }
}

void RippleDrawer::bang(float x, float y, float sz_ratio, float tm_ratio) {
    centerX = x;
    centerY = y;
    size_ratio = sz_ratio;
    time_ratio = tm_ratio;
    
    init();
    
    interpolation.bang(duration);    //msec
    isRunning = true;
}

