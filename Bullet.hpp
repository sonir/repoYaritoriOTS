//
//  Bullet.hpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

//#ifndef Bullet_hpp
//#define Bullet_hpp

#pragma once

#define BULLET_SIZE 0.003
#define BULLET_NUM 128//64

#include <stdio.h>
#include "ofxGismo.h"
#include "Fade.hpp"

typedef struct line_t {
    
    posi_t node_a;
    posi_t node_b;
    bool active;
    
}line_t;

typedef struct pline_t {
    
    posi_t *node_a;
    posi_t *node_b;
    bool active;

    
}pline_t;


typedef struct bullet_shape_t {
    
    posi_t posi;
    bool active;
    
} bullet_shape_t;

typedef struct bullet_shapes_t {
    
    bullet_shape_t buf[BULLET_NUM];
    
} bullet_shapes_t;


posi_t moveOnLine(float fval, float a, float b, float x, float y);


class UniBullet {
    
    public:
        UniBullet(){
            
            route.node_a.x = 0.5f;
            route.node_a.y = 0.5f;
            route.node_b.x = 1.0f;
            route.node_b.y = 0.0f;
            
            
        }
        
        line_t route;
        Fade fade;
        void bang();
        void set(int ms);
        bullet_shape_t update();
        bullet_shape_t update(pline_t aLine);
        int agid = 0;
    
};

class Bullet {
    
    public:
        Bullet(){
            
        }

    
        void setup(int agid){
         
            for(int i=0; i<BULLET_NUM; i++){
                
                buf[i].agid = agid;
                
            }
            
        }

        void bang(){
            
            //Ring buffer
            if(counter >= BULLET_NUM) counter = 0;
            buf[counter].bang();
            counter++;
            
        }
    
        void setDuration(int ms){
            
            for(int i=0; i<BULLET_NUM; i++){
                
                buf[i].set(ms);
                
            }
            
        }
    
        void update(pline_t aLine, bullet_shapes_t *bullet_shapes){
            
            for(int i=0; i<BULLET_NUM; i++){
                
                bullet_shapes->buf[i] = buf[i].update(aLine);
                
            }
                        
        }
    
        void updateWithDuration(pline_t aLine, bullet_shapes_t *bullet_shapes, int ms){
            
            setDuration(ms);
            update(aLine, bullet_shapes);
            
        }


        UniBullet buf[BULLET_NUM];
        int counter = 0;
    
};


// #endif /* Bullet_hpp */
