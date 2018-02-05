//
//  Performance.hpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

//#ifndef Performance_hpp
//#define Performance_hpp

#pragma once

#define PERFORMER_NUM 5
#define POINT_MAX 8

#include <stdio.h>
#include "ofxGismo.h"
#include "Bullet.hpp"

//DRAWING PARAMS
#define SIZE_OF_PERFORMER_INDICATE 0.01f

//Default speed of bullet
#define BULLET_SPD_DEFAULT 250

//SETUP PERFORMERS POSITION
#define PIANO_X 0.0f
#define PIANO_Y 0.0f
#define TROMBONE_X 0.25f
#define TROMBONE_Y 0.25f
#define GUITAR_X 0.5f
#define GUITAR_Y 0.5f
#define BASS_X 0.75f
#define BASS_Y 0.75f
#define DRUMS_X 1.0f
#define DRUMS_Y 1.0f



//Function Prototypes
int count_ring(int now, int max);

//
typedef enum performer_e { PIANO, TROMBONE, GUITAR, BASS, DRUMS } performer_e;
typedef enum performance_mode_e { INSTALLATION , PHASE1_AG_MASTER , PHASE1_AG_SLAVE , PHASE2_CLIMAX } performance_mode_e;


class Performers : public Event{
    
    public:

        posi_t position[PERFORMER_NUM];
    
        Performers(){ // Constructor
            
            //Init performers positions
            position[PIANO].x = PIANO_X;
            position[PIANO].y = PIANO_Y;

            position[TROMBONE].x = TROMBONE_X;
            position[TROMBONE].y = TROMBONE_Y;
            
            position[GUITAR].x = GUITAR_X;
            position[GUITAR].y = GUITAR_Y;
            
            position[BASS].x = BASS_X;
            position[BASS].y = BASS_Y;

            position[DRUMS].x = DRUMS_X;
            position[DRUMS].y = DRUMS_Y;
            
        }
    
        int trigger(void *args){ //Event for set performers' position
            
            param_u *params = (param_u *)args;
            performer_e perf = (performer_e)params[0].ival;
            position[perf].x = params[1].fval;
            position[perf].y = params[2].fval;
            
        }

    
};

class PerformanceManager : public Event {
    
    public:

        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Performers performers;
        performance_mode_e mode = INSTALLATION;
        pline_t lines[AG_MAX];
        pline_t invertedLines[AG_MAX];
        Bullet bullets[AG_MAX];
        Bullet reverseBullets[AG_MAX];
        int bulletSpd = BULLET_SPD_DEFAULT;
    
        PerformanceManager (){
            
            //set agid to each unuBullets
            for(int i=0; i<AG_MAX; i++){
                
                bullets[i].setup(-1);
                reverseBullets[i].setup(i);
                
            }
            
            gismo.eventAdd("/performance/set_position" , &performers);
            gismo.eventAdd("/performance/atk" , this);
            
            
            //SetupEvents
            
            //bullet_bang
            auto f = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;
                int bang_id = params[0].ival;
                if(mode == PHASE1_AG_MASTER) bullets[bang_id].bang(); //Bang when AG_MASTER MODE
            };
            gismo.lambdaAdd("/bullet_from_agent", f);

            //bullet_bang_reverse_direction
            auto f2 = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;
                performer_e pfm = (performer_e)params[0].ival;
                performerBang(pfm);
            };
            gismo.lambdaAdd("/bullet_to_agent", f2);
            
            //Setting Performance Mode
            auto f3 = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;
                performance_mode_e tmp = (performance_mode_e)params[0].ival;
                mode = tmp;
            };
            gismo.lambdaAdd("/performance/mode", f3);

            //Test Shake
//            auto f4 = [&](void* args){ //<- keep this desctiption
//                //draw your code
//                param_u *params = (param_u *)args;
//                int x = (int)params[1].ival;
//                int y = (int)params[2].ival;
//                cout << x << " , " << y << endl;
//            };
//            gismo.lambdaAdd("/visual/shake", f4);
            
            //Set Bullet Speed
            auto f5 = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;
                bulletSpd = (int)params[0].ival;
                
            };
            gismo.lambdaAdd("/performance/bullets/speed", f5);

            
        }
    
        void updateLines();
        void updateLinesInverted();
        void performerBang(performer_e perf);
    
    
        int trigger(void *args){ //Event for set performers' position
            
            //Code for EVENT "/performance/atk"
            param_u *param = (param_u *)args;
            performer_e perf = (performer_e)param->ival;

            if(mode == PHASE1_AG_SLAVE) {
                gismo.bang("/bullet_to_agent" , &perf);
                
            } else if(mode == PHASE2_CLIMAX){
                
                /*
                param_u newArgs[3];
                newArgs[0].ival = 0; //set all as shaking screen
                newArgs[1].ival = 0; //set X_direction as NOMOVE
                
                if (performers.position[perf].y>0.5) newArgs[2].ival = -1;
                else newArgs[2].ival = 1;
                gismo.bang("/visual/shake" , newArgs);
                */
                
                performer_e perf = (performer_e)param->ival;
                param_u flg;
                flg.bval = true;
                
                if( perf==PIANO || perf==TROMBONE ) flg.bval = true;
                else if( perf==DRUMS || perf==BASS ) flg.bval = false;
                else if(perf==GUITAR){
                    
                    if(brand())flg.bval = true;
                    else flg.bval =false;
                    
                }
                gismo.bang("/yaritori/run" , &flg);
                
                
            }
            
        }

    
};

//#endif /* Performance_hpp */
