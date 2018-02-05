//
//  DrawPerformance.cpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#include "DrawPerformance.hpp"

//
//  drawPerformance.hpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#ifndef drawPerformance_h
#define drawPerformance_h



void drawCirclesWithPositions (posi_t *positions, int position_num, float size){
    GismoManager& gismo = GismoManager::getInstance();
    
    for(int i=0; i<position_num;i++){
        
        //circle(positions[i].x, positions[i].y, size, false);
        param_u params[3];
        params[0].fval = positions[i].x;
        params[1].fval = positions[i].y;
        params[2].fval = size;
        params[3].bval = false;
        gismo.lambdaBang("/circle", params);
    }
}


void drawLines (pline_t *lines, int line_num, float width){
    
    GismoManager& gismo = GismoManager::getInstance();
    
    for(int i=0; i<line_num;i++){
        
        pline_t *tmp = &lines[i];
        
        //DrawLine when active agent
        if(tmp->active) {
            //line(tmp->node_a->x, tmp->node_a->y, tmp->node_b->x , tmp->node_b->y, width);
            param_u params[5];
            params[0].fval = tmp->node_a->x;
            params[1].fval = tmp->node_a->y;
            params[2].fval = tmp->node_b->x;
            params[3].fval = tmp->node_b->y;
            params[4].fval = width;
            gismo.lambdaBang("/line", params);
        }
    
    }
    
    
}

void drawBullets(pline_t *lines, Bullet *bullets, int bullets_num, int spd_ms){
    
    bullet_shapes_t tmp;
    GismoManager& gismo = GismoManager::getInstance();
    
    for(int i = 0; i<bullets_num; i++){
        
        bullets[i].updateWithDuration(lines[i], &tmp, spd_ms);
        
        for(int i=0; i<BULLET_NUM; i++){
            
            if(tmp.buf[i].active) {
                //circle(tmp.buf[i].posi.x, tmp.buf[i].posi.y, BULLET_SIZE, true);
                param_u params[4];
                params[0].fval = tmp.buf[i].posi.x;
                params[1].fval = tmp.buf[i].posi.y;
                params[2].fval = BULLET_SIZE;
                params[3].bval = true;
                gismo.lambdaBang("/circle", params);
            }
        }

        
    }
    
}


void drawPerformance(PerformanceManager *pPerformance){
    
    GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
    
    drawCirclesWithPositions(pPerformance->performers.position, PERFORMER_NUM, SIZE_OF_PERFORMER_INDICATE);
    drawLines(pPerformance->lines, AG_MAX, 0.1f);
    drawBullets(pPerformance->lines , pPerformance->bullets, AG_MAX, pPerformance->bulletSpd);
    drawBullets(pPerformance->invertedLines , pPerformance->reverseBullets, AG_MAX, pPerformance->bulletSpd);

    
}


#endif /* drawPerformance_h */
