
// How to Use from your src
//      GismoManager& gismo = GismoManager::getInstance();
//      cout << gismo.foo << endl;
//      gismo.foo = 139;



#pragma once

//SETUP FLAGS
//#define KILL_RIPPLES


//AG BUF SETUPS
#define AG_MAX 9000 //9000
#define SEED_MAX 63

//World Rate of Space
#define WORLD_WIDTH 5.433//2.9f //for 3screens //1.0f
#define WORLD_HEIGHT 1.0f

//Agent Default Parameters
#define AG_DEF_SIZE 0.001f//0.0034f
#define AG_DEF_MOV 0.2f//0.002f
#define AG_DEF_VIEW 0.01f//0.07f//0.03f //0.05f(for slow) //0.3f(for test)
#define AG_DEF_SIZE_FIX 0.005f //Scaling factor for frand(0.0-1.0)
#define DEAD_THREATH 0.0005f
#define DEFAULT_INTERACT_WITH -1

// PARAMS SET MACROS
#define AG_DMG 0.000017f//0.000034f
#define ATK_DIST AG_DEF_SIZE
#define SPD_LIMIT 0.016f //0.02f(for slow) ,, 0.03f
#define SPD_FIX 0.007f //0.01f
#define SPD_RANDOM_WALK_FIX 0.1f

#define DEFAULT_VIEW_RATIO 4.94f//14.35f //1.0f
#define DEFAULT_MOV_RATIO 9.25f //1.0f


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "agTypes.h"
#include "Event.hpp"
#include "EventHandler.hpp"


//Function Prototypes
//Inits
void initAgent(ag_t *ags);
void initAgentActive(ag_t *ags);
void initAgents(ag_t *ags);
void initAgentBuff(agent_buf_t *ags);
//AgentOperation
void addAgentToBuff(ag_t ag, agent_buf_t put_buf);
void agBuffReset(agent_buf_t *agents);
//InteractionTool
float distance(posi_t p1, posi_t p2);
int seekNearest(int ag_id, agent_buf_t *agbuf);
bool isViewRange(ag_t *ag, float distance);
int isLarge(float f1, float f2);
void move(ag_t *ag, posi_t *posi);
void randomMove(ag_t *ag);
float limitter(float val, float limit);
void running(ag_t *ag, posi_t *enemy);
bool conditionCheck(condition_e cond1, condition_e cond2);
bool attackCheck(float distance, float *f_param);
bool deadCheck(float *size, bool *active);
void interactWith(ag_t *focus , ag_t *target);
void makeInteracts(agent_buf_t *agents);
//void positionLoop(posi_t *position);
bool positionLoop(posi_t *position, float w_max, float h_max);
float logistic(float fval=0.5);
void setSeed(int seed);
float frand();
int irand();
bool brand();
//SetSound
int setSound(int sound_id);
void reacted(ag_t *focus);

//Class for Data management

class GismoManager : public EventHandler {
    
    public:
        //Kill methods related with duplication of instance
        GismoManager(const GismoManager&) = delete;
        GismoManager& operator=(const GismoManager&) = delete;
        GismoManager(GismoManager&&) = delete;
        GismoManager& operator=(GismoManager&&) = delete;
    
        static GismoManager& getInstance(){
            static GismoManager instance; //Invoke privated constructor
            return instance;
        }
    
        const char* getString(){
            return "Hello world!";		//to invoke, write " Singleton::getInstance().getString(); " 
        }
    
        //Variables fixed
        agent_buf_t agents;
        agent_buf_t add;
        Event *sound;
    
        //Store the screen rate
        float width_rate = WORLD_WIDTH;
        float height_rate = WORLD_HEIGHT;

        //Global param control
        float view_ratio = DEFAULT_VIEW_RATIO;
        float mov_ratio = DEFAULT_MOV_RATIO;
    
    
        //Methods
        void setup();
        ag_t* getAgents();
        ag_t* getAgent(int aid);
        void addAgent(ag_t tmp);
        void addSync(); //Sync actual agent array and add_buffer

    
    private:
        GismoManager();
        ~GismoManager() = default;
    
    
    
};


