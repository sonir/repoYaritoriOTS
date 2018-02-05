//
//  Bullet.cpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#include "Bullet.hpp"

posi_t moveOnLine(float fval, float a, float b, float x, float y){
    
    
    posi_t posi;
    
    float diff_x = x - a;
    float diff_y = y - b;
    
    posi.x = ( fval * diff_x ) + a;
    posi.y = ( fval * diff_y ) + b;
    
    //    cout << diff_x << " , " << diff_y << endl;
    //    cout << "moveOnLine::fval=" << fval << " || " << posi.x << endl;
    return posi;
    
}


////////
// Implementation of Unibullet //
///////


void UniBullet::bang(){
    
    fade.reset();
    fade.bang();
    
}

void UniBullet::set(int ms){
    
    fade.set(ms);
    
}

bullet_shape_t UniBullet::update(){


    bullet_shape_t bullet_shape;
    float fval = fade.update();
    
    //deactivate draw when star and end position of bullet
    if(fval == 1.0f || fval == 0.0f) bullet_shape.active = false;
    else bullet_shape.active = true;
    
    bullet_shape.posi = moveOnLine(fval, route.node_a.x, route.node_a.y, route.node_b.x, route.node_b.y);
    return bullet_shape;
}


bullet_shape_t UniBullet::update(pline_t aLine){
    
    bullet_shape_t bullet_shape;
    float fval = fade.update();
    
    //deactivate draw when star and end position of bullet
    if(fval == 1.0f || fval == 0.0f){
        
        
        if (fval >= 1.0f) { //When the timing of Changing from true to false
            
            //Create ripple when
            GismoManager& gismo = GismoManager::getInstance();
            float tmp[4];
            posi_t posi =  moveOnLine(fval, aLine.node_a->x, aLine.node_a->y, aLine.node_b->x, aLine.node_b->y);
            
            tmp[0] = posi.x;
            tmp[1] = posi.y;
            tmp[2] = 5.25f; // set size ratio
            tmp[3] = 1.0f; //set time ratio
            
            gismo.bang("/ripple" , &tmp);
            //Don't play sound when the bullets from ag to performance
            if(agid != -1) gismo.bang("/soundTriggerWithAgent", gismo.getAgent(agid) ); //trigger sound
            
        }
        fval == 0.0f;
        bullet_shape.active = false;
    }
    else bullet_shape.active = true;
    
    bullet_shape.posi =  moveOnLine(fval, aLine.node_a->x, aLine.node_a->y, aLine.node_b->x, aLine.node_b->y);
    
    return bullet_shape;
    
}
