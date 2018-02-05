//
//  DrawAgentsWithChar.cpp
//  yaritori
//
//  Created by sonir on 1/13/18.
//
//

#include "DrawAgentsWithChar.hpp"

void DrawAgentsWithChar::draw(GismoManager *gismo, float screen_w, float screen_h){
    
    
    int count = gismo->agents.count;
    ag_t *agents = gismo->getAgents(); //sets agents pointer
    ag_t *ag;
    string cond_flg;
    
    for(int i =0; i<count; i++){
        
        ag = agents; //Set agent address
        
        if(ag->active){
            
            int tmp_x = (int)( ag->posi.x * (float)screen_w );
            int tmp_y = (int)( ag->posi.y * (float)screen_h );
            
            switch(ag->condition){
                    
                case CALM:
                    cond_flg = "+";
                    //cond_flg = to_string(ag->mov);
                    ofSetColor(50,255,50);
                    break;
                    
                case CHASE:
                    cond_flg = "C";
                    ofSetColor(255,255, 50);
                    break;
                    
                case RUN:
                    cond_flg = "R";
                    ofSetColor(200, 50, 50);
                    break;
                    
                case DMG:
                    cond_flg = "D";
                    ofSetColor(255, 100, 100);
                    break;
                    
                case DEATH:
                    cond_flg = "x";
                    ofSetColor(100, 100, 100);
                    break;
                    
                default:
                    break;
                    
                    
            }
            
            //square(ag->posi.x, ag->posi.y, ag->size*10.0f, 0.0f, false);
            ofDrawBitmapString( cond_flg, tmp_x/gismo->width_rate, tmp_y/gismo->height_rate);
            //circle(ag->posi.x+0.0078f, ag->posi.y+0.00078f, ag->view,false);
            ofSetColor(255,255,255);
        }
        agents++;
        
    }

    
    
}
