//
//  Performance.cpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#include "Performance.hpp"



int count_ring(int now, int max){
    
    now++;
    if (now >= max) return 0;
    else return now;
    
}


void PerformanceManager::updateLines(){
    
    ag_t *agents = gismo.getAgents();
    
    for(int i=0; i<AG_MAX; i++){
        if(agents[i].active==true)lines[i].active = true;
        else lines[i].active = false;

        lines[i].node_a = &agents[i].posi;
        lines[i].node_b = &performers.position[i%PERFORMER_NUM];
    }
}


void PerformanceManager::updateLinesInverted(){
    
    ag_t *agents = gismo.getAgents();
    
    for(int i=0; i<AG_MAX; i++){
        
        if(agents[i].active==true)lines[i].active = true;
        else lines[i].active = false;
        
        invertedLines[i].node_a = &performers.position[i%PERFORMER_NUM];
        invertedLines[i].node_b = &agents[i].posi;
        
        
    }
    
}


void PerformanceManager::performerBang(performer_e perf){

    ag_t *agents = gismo.getAgents();

    
    for(int i=0; i<AG_MAX;i++){
        
        int key = i%PERFORMER_NUM;
        if(key == perf){ //if the ag is selected performer
            
            //If the agent is active, bang it
            if(agents[i].active==true) reverseBullets[i].bang();
            
        }
        
    }
    
    
}

