//
//  VSyn.hpp
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#ifndef VSyn_hpp
#define VSyn_hpp

//Set running mode
//#define DEBUG_MODE
#define DUMMY_AG_A_NUM 0//1000
#define DUMMY_AG_B_NUM 0//5//1000

#define PERFORMANCE_MODE
#define GISMO_UPDATE_INTERVAL 0.033


//SYSTEMS
#define SYS_UPDATE_INTERVAL 10.0f
#define SAVE_INTERVAL 3600.0f

//#define DEBUG_MODE
#define DUMMY_AG_A_NUM 0
#define DUMMY_AG_B_NUM 0

//SCREEN SETUP
#define SC_WIDTH 1024
#define SC_HEIGHT 768

//OSC
#define PORT 57139
#define NUM_MSG_STRINGS 20

//#define CONTAINER_MAX 128 //Size of Buffer for Shapes
#define CONTAINER_MAX AG_MAX*128 //Size of Buffer for Shapes

//Ripple
#define DEFAULT_RIPPLE_SIZE 1.0f
#define DEFAULT_RIPPLE_TIME 1.0f
//SOLO MODE when incoming an agent
#define SOLO_DURATION 8.0
#define SOLO_RIPPLE_TIME SOLO_DURATION*2.4f //18.0f
#define SOLO_RIPPLE_SIZE SOLO_DURATION*2.4f //18.0f//14.0f


/// Includes ///

//Basics
#include <stdio.h>
#include <cassert>
#include "ofMain.h"

//Addons
#include "ofxOsc.h"

//Gismo
#include "ofxGismo.h"

//vSyn
#include "shape.h"
#include "osc2shape.hpp"
#include "drawer.hpp"
#include "cam_func.hpp"
#include "Particle.hpp"


/// Yaritori Modules ///

// Receiving message from network
#include "Network.hpp"

//Convert from shape_t to agent
#include "Shape2Agent.hpp"

//Test Class
#include "Test.hpp"

//Metro
#include "Metro.hpp"


//AudioTriger with OSC
//#include "Sound.hpp"

//Drawing
#include "drawAgents.hpp"
#include "DrawPerformance.hpp"
#include "DrawAgentsWithChar.hpp"
#include "RippleManager.hpp"
#include "VboRenderer.hpp"

//Sound
#include "SoundTrigger.hpp"

//DataStore
#include "Csv2Buffer.hpp"
#include "Buffer2Csv.hpp"

//To invoke osc-hub
#include "InvokingApp.hpp"

//Timer to close this app
#include "TimeTimer.hpp"




class VSyn : public Event {
 
    public:
        VSyn(){
            
            //Boot osc-hub
            exe("sh boot.sh"); //This code must be write here, before instanciate Network.cpp.
            ofSleepMillis(2000);
            
            //SetupEvents
            
            //event for added agent
            auto f = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;

                param_u soloArg[2];
                soloArg[0].ival = params[0].ival; //set agid
                soloArg[1].fval = (SOLO_DURATION * durationRatioWhenAdd); //set duration
                gismo.bang("/solo" , soloArg); //bang solo
                
                param_u dur;
                dur.fval = (SOLO_DURATION * durationRatioWhenAdd); //set duration
                gismo.bang("/visual/timed_invert", &dur); //bang timed invert
                
                param_u rpl[3];
                rpl[0].ival = params[0].ival; //agid
                rpl[1].fval = SOLO_RIPPLE_SIZE; //size ratio
                rpl[2].fval = ( SOLO_RIPPLE_TIME * durationRatioWhenAdd );//2.4f; //time ratio
                gismo.bang("/ag_ripple" , rpl);

                
            };
            gismo.lambdaAdd("/gismo/added", f);

            
            
            //ripplle by reacted
            auto f2 = [&](void* args){ //<- keep this desctiption
                param_u *params = (param_u *)args;
                int agid = params[0].ival; //ID
                
                //Sending ripple
                param_u rippleArg[3];
                rippleArg[0].ival = agid;
                rippleArg[1].fval = DEFAULT_RIPPLE_SIZE; //X
                rippleArg[2].fval = DEFAULT_RIPPLE_TIME; //Y
                gismo.bang("/ag_ripple" , rippleArg);
                
                //Trigger Sound
                float dice = frand();

                float actuate_rate_sjq;
                float rate;
                rate = ((float)gismo.agents.count/800.0f);
                actuate_rate_sjq = SOUND_SJQ_RATE * rate;

                if(dice<= actuate_rate_sjq){
                    gismo.bang( "/soundTriggerWithPerformer", gismo.getAgent(agid) );

                }else{
                    gismo.bang( "/soundTriggerWithAgent", gismo.getAgent(agid) ); //trigger sound
                    
                }

                
                
            };
            gismo.lambdaAdd("/gismo/reacted", f2);
            
            
            
            //Run or Stop gismodel in PHASE2
            auto f3 = [&](void* args){ //<- keep this desctiption
                param_u *params = (param_u *)args;
                
                bool flg = (bool)params->bval;
                
                if(flg){

                    //metro->resetStart();
                    metro->stop = false;
                    param_u param ;
                    param.bval = false;
//                    gismo.lambdaBang("/invert", &param);
                    gismo.lambdaBang("/tremble", &param);
                    
                } else if (!flg){
                    //metro->stop();
                    metro->stop = true;
                    param_u param ;
                    param.bval = true;
//                    gismo.lambdaBang("/invert", &param);
                    gismo.lambdaBang("/tremble", &param);
                    
                }
                
            };
            gismo.lambdaAdd("/yaritori/run", f3);
            
            
            
            //event for agent save
            auto f4 = [&](void* args){ //<- keep this desctiption
                cout << "EVENT :: /yaritori/save was invoked." <<endl;
                //draw your code
                param_u *params = (param_u *)args;
                buffer2csv.saveAgents(gismo.agents.buf,gismo.agents.count, "0-agent.csv");
                buffer2csv.saveShapes(ag_shapes, gismo.agents.count, "0-shape.csv");
                
            };
            gismo.lambdaAdd("/yaritori/save", f4);

            
            
            //event for agent backup
            auto f4b = [&](void* args){ //<- keep this desctiption
                cout << "EVENT :: /yaritori/save was invoked." <<endl;
                //draw your code
                
                char ag_bak_file_src[256];
                char shape_bak_file_src[256];
                sprintf(ag_bak_file_src, "%d_%d_%d_%d-agent.csv" , ofGetMonth(), ofGetDay(),ofGetHours(), ofGetMinutes());
                string ag_bak_file(ag_bak_file_src);
                
                sprintf(shape_bak_file_src, "%d_%d_%d_%d-shape.csv" , ofGetMonth(), ofGetDay(),ofGetHours(), ofGetMinutes());
                string shape_bak_file(shape_bak_file_src);

                
                param_u *params = (param_u *)args;
                buffer2csv.saveAgents(gismo.agents.buf,gismo.agents.count, ag_bak_file);
                buffer2csv.saveShapes(ag_shapes, gismo.agents.count, shape_bak_file);
                
            };
            gismo.lambdaAdd("/yaritori/backup", f4b);

            
            
            //Loading agents and shapes
            auto f5 = [&](void* args){ //<- keep this desctiption
                
                //draw your code
                param_u *params = (param_u *)args;
                int val =1;
                gismo.bang("/gismo/reset", &val);
                csv2buffer.loadShapes("0-shape.csv");
                csv2buffer.loadAgents(gismo.add.buf , "0-agent.csv");
                
            };
            gismo.lambdaAdd("/yaritori/load", f5);
            
            
            
            //Loading agents and shapes
            auto f5b = [&](void* args){ //<- keep this desctiption
                
                //draw your code
                param_u *param = (param_u *)args;
                durationRatioWhenAdd = param->fval;
                
            };
            gismo.lambdaAdd("/yaritori/add_duration", f5b);

            
            
            //reset agents and shapes
            auto f6 = [&](void* args){ //<- keep this desctiption
                
                param_u *params = (param_u *)args;
                agBuffReset(&gismo.agents);
                agBuffReset(&gismo.add);
                ag_shapes_count = 0;
                
                
            };
            gismo.lambdaAdd("/gismo/reset", f6);

            
            
            //reset agents and shapes
            auto f7 = [&](void* args){ //<- keep this desctiption
                
                ag_shape_t *tmp = (ag_shape_t *)args;
                ag_shape_t shape = *tmp;
                addAgShape(shape);
                
            };
            gismo.lambdaAdd("/yaritori/add_shape", f7);

            
          
            //reset agents and shapes
            auto f8 = [&](void* args){ //<- keep this desctiption
                
                sound_unit_t *tmp = (sound_unit_t *)args;
                sound_unit_t snd = *tmp;
                soundTrigger.sounds[snd.index]=snd.elm;
                
            };
            gismo.lambdaAdd("/sound/push", f8);
            
            
            //Make QuiteEvent
            auto f9 = [&](void* args){ //<- keep this desctiption
                cout << "EVENT :: /yaritori/quite was invoked." <<endl;
                ofExit();
                
            };
            gismo.lambdaAdd("/yaritori/quite", f9);
            
            
            
            //Make Event to set EndTime
            auto f10 = [&](void* args){ //<- keep this desctiption
                cout << "EVENT :: /yaritori/endt_time was invoked." <<endl;
                param_u *params = (param_u *)args;
                
                quitTimer->hour = params[0].ival;
                quitTimer->minutes = params[1].ival;
                
                cout << quitTimer->hour << " : " << quitTimer->minutes << endl;

                
            };
            gismo.lambdaAdd("/yaritori/end_time", f10);
            
            
        }
    
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
        void initWindowSize();
        int trigger(void *args){ //Definicatinon of an event named "/addAgentWithShape"
            
            ag_shape_t *tmp = (ag_shape_t *)args;
            ag_shape_t tmp2 = *tmp;
            addAgShape(tmp2);
            gismo.addAgent( shape2Agent(tmp2) ); //add agent from shape
            //make sound
            int index = gismo.agents.count;
            sound_t snd = shape2sound(tmp2, index); //Song genre and song with the shape and ag_id
            soundTrigger.sounds[index]= snd; //Store sound int sound buffer
            
        }
    
        //Variables for VSyn
        shapeContainer shapes[CONTAINER_MAX];
        ofColor colors[CONTAINER_MAX];
        ofxOscReceiver receiver;
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        //ScreenManagement
        int screen_w;
        int screen_h;
        ScreenManager scManager;
    
        //Particle
        Particle particle;
    
        //CAMERA CONTROL
        ofEasyCam cam;
        bool cam_flg;
        ofVec3f pov;
        ofVec3f look;
    
    //CCMA
    //To store the received shape
    ag_shape_t ag_shapes[AG_MAX];
    int ag_shapes_count = 0;
    void addAgShape(ag_shape_t shape);
    
        //For Performance
        PerformanceManager performanceManager;
        //DrawPerformance drawPerformance;
        line_t aLine;
        Bullet *bullet;
        Metro *metro;
        Metro *sysEventInterval;
        Metro *saveInterval;
    
        //Yaritori Core
        Csv2Buffer csv2buffer;
        Buffer2Csv buffer2csv;

    
    
    private:
        void initShapes(int max_num);
        void initColors(int max_num);
        void test(); //Method for Any Test
        //Variables
        Test *myTest; //Test Instance
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        DrawAgentsWithChar drawAgentsWithChar;
    
        //Sound sound; //AudioTrigger with OSC
        //Sound
        SoundTrigger soundTrigger;    

        //AGENT VISUAL
        RippleManager ripple;
        visual_container_t visual;
    
        VboRenderer renderer;
    
        //SystemManagement
        TimeTimer *quitTimer = new TimeTimer(QUIT_HOUR, QUIT_MINUTES, "/yaritori/quite"); //timer to quite
        TimeTimer *bakTimer = new TimeTimer(BAK_HOUR, BAK_MINUTES, "/yaritori/backup"); //timer to quite
    
        //Animation
        float durationRatioWhenAdd = 1.0f;

    
};

#endif /* VSyn_hpp */
