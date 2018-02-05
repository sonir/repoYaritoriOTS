#include "ofxGismo.h"

using namespace std;

//Imlementations of C Functions

void initAgent(ag_t *tmp){
    
    tmp->agid = -1;
    tmp->active = false;
    tmp->posi.x = frand()*WORLD_WIDTH;
    tmp->posi.y = frand()*WORLD_HEIGHT;
    tmp->size = AG_DEF_SIZE;
    tmp->view = AG_DEF_VIEW;
    tmp->mov = AG_DEF_MOV;

    tmp->spd.x = 0.0f;
    tmp->spd.y = 0.0f;
    
    tmp->condition = CALM;
    tmp->interact_with = DEFAULT_INTERACT_WITH;
    
    
}

void initAgentActive(ag_t *tmp){
    
    initAgent(tmp);
    tmp->active = true;
    
}


void initAgents(ag_t *ags){ //Init all agents with default paramas
    
    printf("initAgents\n");
    for (int i=0; i<AG_MAX; i++){
        
        initAgent(ags);
        ags++; //Increment the index
        
    }
        
    
}


void initAgentBuff(agent_buf_t *ags){
    
    ags->count = 0;
    initAgents(ags->buf);
    
}



void addAgentToBuff(ag_t ag, agent_buf_t *put_buf){ //Put agent to buff
    
    put_buf->buf[put_buf->count] = ag;
    put_buf->count += 1;
    
}


void agBuffReset(agent_buf_t *agents){
    
    for(int i=0; i<AG_MAX;i++){
        
        agents->buf[i].active = false;
        
    }
    agents->count = 0;
    
}




//Interaction Tool Kits
float distance(posi_t p1, posi_t p2){
    
    posi_t tmp1, tmp2;
    // calc differences
    tmp1.x = p2.x - p1.x;
    tmp1.y = p2.y - p1.y;
    
    tmp2.x = tmp1.x*tmp1.x;
    tmp2.y = tmp1.y*tmp1.y;
    
    //	pythagoras theorem
    return (float)( sqrt(tmp2.x+tmp2.y) );
    
    
}


int seekNearest(int ag_id, agent_buf_t *agbuf){
    
    ag_t *forcus = &agbuf->buf[ag_id];
    ag_t *target;
    int nearest_id = -1;
    float nearest_val = 999.0f;
    float val = 0.0f;
    for(int i=0; i<agbuf->count;i++){
        target = &agbuf->buf[i];
        if (target->active == false || ag_id == i){ //Ignore dead or void agent or myself
            
            continue;
            
        }
        val = distance(forcus->posi, target->posi);
        
        if(val < nearest_val){ //If find tmpolary longest
            
            nearest_id = i; //store the id
            nearest_val = val; //update the lon
        }
        
    } // end of for
    
    return nearest_id;
    
    
}


bool isViewRange(ag_t *ag, float distance){
    
    GismoManager& gismo = GismoManager::getInstance();
    
    if( (ag->view*gismo.view_ratio) > distance) return true;
    else if ( (ag->view*gismo.view_ratio) <= distance) return false;
    
}


int isLarge(float f1, float f2){
    
    if (f1>f2)return 1;
    else if (f1<f2) return 0;
    else if (f1==f2){
        
        return -1;
        
    }
    
}



void move(ag_t *ag, posi_t *posi){

    GismoManager& gismo = GismoManager::getInstance();

    //decision X
    float x_move = frand()*ag->mov*SPD_FIX;
    if ( isLarge(ag->posi.x, posi->x) ) ag->spd.x -= x_move; //WHEN LARGE change xspd to negative
    else ag->spd.x += x_move; //WHEN SMALL change xspd to negative
    
    ag->spd.x = limitter(ag->spd.x, SPD_LIMIT); //LimitCheck
    ag->posi.x += ( ag->spd.x * gismo.mov_ratio); //Move with the refleshed sppd

    //decision Y
    float y_move = frand()*ag->mov*SPD_FIX;
    if ( isLarge(ag->posi.y, posi->y) ) ag->spd.y -= y_move; //WHEN LARGE change xspd to negative
    else ag->spd.y += y_move; //WHEN SMALL change xspd to negative
    
    ag->spd.y = limitter(ag->spd.y, SPD_LIMIT); //LimitCheck
    ag->posi.y += ( ag->spd.y * gismo.mov_ratio ); //Move with the refleshed sppd

    
    //Stop when mov= 0
    if(ag->mov == 0.0f)
    {
        ag->spd.x = 0.0f;
        ag->spd.y = 0.0f;
        
    }

}



void randomMove(ag_t *ag){

    GismoManager& gismo = GismoManager::getInstance();
    
    //Set next target position with random
    posi_t rand;
    rand.x = frand()*WORLD_WIDTH;
    rand.y = frand()*WORLD_HEIGHT;
    
    //decision X
    float x_move = frand()*ag->mov*SPD_FIX*SPD_RANDOM_WALK_FIX;
    if ( isLarge(ag->posi.x, rand.x) ) ag->spd.x -= x_move; //WHEN LARGE change xspd to negative
    else ag->spd.x += x_move; //WHEN SMALL change xspd to negative
    
    ag->spd.x = limitter(ag->spd.x, SPD_LIMIT*SPD_RANDOM_WALK_FIX); //LimitCheck
    ag->posi.x += ( ag->spd.x * gismo.mov_ratio ); //Move with the refleshed sppd
    
    
    //decision Y
    float y_move = frand()*ag->mov*SPD_FIX*SPD_RANDOM_WALK_FIX;
    if ( isLarge(ag->posi.y, rand.y) ) ag->spd.y -= y_move; //WHEN LARGE change xspd to negative
    else ag->spd.y += y_move; //WHEN SMALL change xspd to negative

    ag->spd.y = limitter(ag->spd.y, SPD_LIMIT*SPD_RANDOM_WALK_FIX); //LimitCheck
    ag->posi.y += ( ag->spd.y * gismo.mov_ratio ); //Move with the refleshed sppd

    
    //Stop when mov= 0
    if(ag->mov == 0.0f)
    {
        ag->spd.x = 0.0f;
        ag->spd.y = 0.0f;
        
    }

    
    
}



float limitter(float val, float limit){
    
    //get abs
    float abs;
    if (val < 0)
    {
        
        abs= val * (-1);
        
    } else
    {
        
        abs = val;
        
    }
    
    
    if ( abs<limit ){

        return val;
        
    }else{
        
        if ( val < 0 ) return ( limit * (-1) ); //val was negative, return negative abs
        else return limit; // val was positive, return positive abs
        
    }
    
}



void running(ag_t *ag, posi_t *enemy){
    
    //decision X
    float x_move = frand()*ag->mov*SPD_FIX;
    if ( isLarge(ag->posi.x, enemy->x) )
    {
        ag->spd.x += x_move; //WHEN LARGE change xspd to negative
        
    } else {
        ag->spd.x -= x_move; //WHEN SMALL change xspd to negative
        
    }
    
    ag->spd.x = limitter(ag->spd.x, SPD_LIMIT); //LimitCheck
    ag->posi.x += ag->spd.x; //Move with the refleshed sppd
    
    //decision Y
    float y_move = frand()*ag->mov*SPD_FIX;
    if ( isLarge(ag->posi.y, enemy->y) )
    {
        ag->spd.y += y_move; //WHEN LARGE change xspd to negative
        
    } else {
        ag->spd.y -= y_move; //WHEN SMALL change xspd to negative
        
    }
    
    ag->spd.y = limitter(ag->spd.y, SPD_LIMIT); //LimitCheck
    ag->posi.y += ag->spd.y; //Move with the refleshed sppd
    
    
    //Stop when mov= 0
    if(ag->mov == 0.0f)
    {
        ag->spd.x = 0.0f;
        ag->spd.y = 0.0f;
        
    }
    
    
}



bool conditionCheck(condition_e cond1, condition_e cond2){
    
    if (cond1==cond2) return true;
    else return false;
    
    
}



bool attackCheck(float distance, float *f_param){
    
    if(distance <= ATK_DIST)
    {
        *f_param -= AG_DMG;
        return true;
        
    }else
    {
        
        return false;
        
    }
    
}


bool deadCheck(float *size, bool *active){
    
    if(*size < DEAD_THREATH ){
        
        *size = 0.0f;
        *active = false;
        return true;
        
    }else{
        
        return false;
        
    }
    
}


void interactWith(ag_t *focus , ag_t *target){
    
    GismoManager& gismo = GismoManager::getInstance();
    
    float dist = distance(focus->posi, target->posi);
    if (isViewRange(focus, dist)){
        
        //Check size check
        int size_check = isLarge(focus->size, target->size);
        
        //Do action according to the result of size check
        if( size_check == 1){ //Is larger

            move(focus, &target->posi);
            
            condition_e cond = CHASE;
            if ( attackCheck( distance(focus->posi, target->posi) , &target->size) ) cond = DMG;
            if ( deadCheck(&target->size, &target->active) ) cond = DEATH;
            
            if( !conditionCheck(focus->condition, cond) ){
                
                focus->condition=cond;
                gismo.bang("/soundTriggerWithAgent", focus); //trigger sound
                gismo.bang("/bullet_from_agent", &focus->agid); //trigger bullet
                reacted(focus); //notice the agent reacted
                
            }else{
                
                focus->condition=cond;
                
            }

            
        } else if (size_check == (-1) ) { //Is same size
        
            if( brand() ) {
                
                target->size-=AG_DMG; //decrease the target size in 50% rate.
                focus->size+=AG_DMG; //Increasing the atacked agent
                reacted(focus); //notice the agent reacted

            }
            
            
        } else { //RUN CASE

            running(focus, &target->posi);
            if( !conditionCheck(focus->condition, RUN) ){
                
                //do running code
                focus->condition=RUN;
                reacted(focus); //notice the agent reacted
                gismo.bang("/soundTriggerWithAgent", focus);
                
                
            }
            focus->condition=RUN;

        }
        
    }else{

        randomMove(focus);
        focus->condition=CALM;
        
    }
    

}


void makeInteracts(agent_buf_t *agents){

    
    //Get singleton to get width rate
    GismoManager& gismo = GismoManager::getInstance();

    
    int nearest = -1;
    
    if (agents->count==1){
        
        randomMove(&agents->buf[0]);
        return; //when an agent only, do randomwalk.
        
    }
    
    for(int i=0; i<agents->count;i++){
                
        nearest = seekNearest(i, agents);
        if(nearest != -1)
        {
            //Interact
            interactWith(&agents->buf[i], &agents->buf[nearest]);
            //Loop of World
            if ( positionLoop(&agents->buf[i].posi, gismo.width_rate, gismo.height_rate) ){
                
                agents->buf[i].condition = CALM;
                
            }
            //Set who is interacted agent
            if(agents->buf[i].condition != CALM) agents->buf[i].interact_with = nearest;
            else agents->buf[i].interact_with = DEFAULT_INTERACT_WITH;
        
        }
        
    }
    
    
    
}


bool positionLoop(posi_t *position, float w_max, float h_max){
    
    bool looped = false;
    
    if(position->x > w_max)
    {
        
        position->x = 0.0f;
        looped = true;
        
    } else if (position->x <= 0.0f)
    {
        
        position->x = w_max;
        looped = true;
        
    }
    
    if(position->y > h_max)
    {
        
        position->y = 0.0f;
        looped = true;
        
    } else if (position->y <= 0.0f)
    {
        
        position->y = h_max;
        looped = true;
        
    }
    
    return looped;
    
}


float logistic(float fval){
    
    float tmp = 1.0f-fval;
    tmp = (tmp*fval)*3; //3 is constant
    return tmp;
    
}

void setSeed(int seed){
    
    srand(seed);
    
}

float frand(){
    
    //return ( ( (float)( rand()%10 ) ) * 0.1 );
    return ( ( (float)( rand()%10000 ) ) * 0.0001 );

    
}

int irand(){
    
    return ( ( rand()%100 ) );
    
}

bool brand(){
    
    if (rand()%2==0)return true;
    else return false;
    
}

int setSound(int sound_id){
    
    //Get singleton
    GismoManager& gismo = GismoManager::getInstance();
    gismo.bang("/snd" , &sound_id);

    return sound_id;

    
}

void reacted(ag_t *focus){
    

    //Get singleton to get width rate
    GismoManager& gismo = GismoManager::getInstance();
    
    param_u arg;
    arg.ival = focus->agid;
    
    gismo.bang("/gismo/reacted" , &arg);
    
}



//Definication of GismoManager :::::::::::

GismoManager::GismoManager() //Constructor
{
    setSeed(137);
    initAgents(agents.buf);
    agents.count = 0;
    agent_buf_t add;
    initAgentBuff(&add);
    
}

void GismoManager::setup(){
    
    cout << "GismoManager setup" <<endl;
    
}


ag_t* GismoManager::getAgents()
{
    
    return agents.buf;
    
}

ag_t* GismoManager::getAgent(int aid)
{
    
    return &agents.buf[aid];
    
}

void GismoManager::addAgent(ag_t tmp){
    
    addAgentToBuff(tmp, &add);
    
}


void GismoManager::addSync(){
    
    
    for(int i=0; i<add.count;i++){
        
        agents.buf[agents.count]=add.buf[i];
        agents.buf[agents.count].agid = agents.count;

        param_u arg;
        arg.ival = agents.count;
        
        this->bang("/gismo/added" , &arg);

        agents.count++;
        
    }
    add.count = 0; //reset add_buf count
    
}

