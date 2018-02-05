//
//  osc2shape.cpp
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#include "osc2shape.hpp"

void toMute(shapeContainer *elm, bool flg){
    
    elm->active = !flg;
    
}


void toCircle(shapeContainer *elm, int uid, float x, float y, float size, int fill){

    //Set System Params
    elm->type = CIRCLE;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x;
    elm->y1 = y;
    elm->size = size;
    if (fill == 1){ //Convert from int to bool
        elm->fill = true;
    }else{
        elm->fill = false;
        
    }
    
    
}

void toTriangle(shapeContainer *elm, int uid, float x, float y, float size, float angle, int fill){
    
    //Set System Params
    elm->type = TRIANGLE;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x;
    elm->y1 = y;
    elm->size = size;
    elm->angle = angle;
    if (fill == 1){ //Convert from int to bool
        elm->fill = true;
    }else{
        
        elm->fill = false;
        
    }
    
    
}


void toSquare(shapeContainer *elm, int uid, float x, float y, float size, float angle, int fill){
  
    //Set System Params
    elm->type = SQUARE;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x;
    elm->y1 = y;
    elm->size = size;
    elm->angle = angle;
    if (fill == 1){ //Convert from int to bool
        elm->fill = true;
    }else{
        
        elm->fill = false;
        
    }
    

    
}

void toRect(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float angle, int fill){
 
    //Set System Params
    elm->type = RECT;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x1;
    elm->y1 = y1;
    elm->x2 = x2;
    elm->y2 = y2;
    
    elm->angle = angle;
    elm->fill = fill;
    
    if (fill == 1){ //Convert from int to bool
        elm->fill = true;
    }else{
        
        elm->fill = false;
        
    }
    
    
}

void toLine(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float thick){
    
    //Set System Params
    elm->type = LINE;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x1;
    elm->y1 = y1;
    elm->x2 = x2;
    elm->y2 = y2;
    
    elm->thick = thick;
    
}

void toArc(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float height, float expose, float thick){

    //Set System Params
    elm->type = ARC;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x1;
    elm->y1 = y1;
    elm->x2 = x2;
    elm->y2 = y2;
    elm->expose = expose;
    elm->height = height;
    elm->thick = thick;
    
}

void toWave(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float freq, float amp, float phase, float thick){
    
    //Set System Params
    elm->type = WAVE;
//    elm->active = true;
    elm->uid = uid;
    //Shape data (position, size etc)
    elm->x1 = x1;
    elm->y1 = y1;
    elm->x2 = x2;
    elm->y2 = y2;
    elm->freq = freq;
    elm->amp = amp;
    elm->phase = phase;
    
    elm->thick = thick;

    
}

