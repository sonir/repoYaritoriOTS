//
//  Buffer2Csv.cpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#include "Buffer2Csv.hpp"

using namespace std;

void Buffer2Csv:: saveAgents(ag_t *agents ,  int index_count, string withFile){
    
    cout << "----" << endl;
    cout << "Buffer2Csv :: Export agents as " << withFile << endl;
    
    ofstream log;
    log.open(withFile , ios_base::trunc);
    
    log << "agid" << "," << "active" << "," << "posi.x" << "," << "posi.y" << "," << "size" << "," << "view" << "," << "mov" << "," << "condition" << "," << "spd.x" << "," << "spd.y" << "," << "interact_with" << endl;
    
    for(int i=0; i<index_count; i++){
        
        ag_t *elm = agents;
        log << elm->agid << "," << elm->active << "," << elm->posi.x << "," << elm->posi.y << "," << elm->size << "," << elm->view << "," << elm->mov << "," << elm->condition << "," << elm->spd.x << "," << elm->spd.y << "," << elm->interact_with << "," << endl;
        
        
        agents++;

        
    }
    
    //Close opened file
    log.close();

    //Move the created files on Resources folder in your app to "data" folder.
    char cmd[256];
    sprintf(cmd, "sh mv_agent.sh %s" , withFile.c_str());
    cout << cmd << endl;
    
    cout << "CMD2 :: " << system("ls") << endl;
    cout << "CMD1 :: " << system(cmd) << endl;
    
//    cout << "CMD1 :: " << system("sh mv_agent.sh") << endl;
    
}



void Buffer2Csv::saveShapes(ag_shape_t *shapes, int index_count, string withFile){

    
    cout << "----" << endl;
    cout << "Buffer2Csv :: Export shapes as " << withFile << endl;

    ofstream log;
    log.open(withFile , ios_base::trunc);
    
    //Set basic column
    log << "color" << "," << "node_count"<< endl;

    
    for(int i=0; i<index_count; i++){
        
        ag_shape_t *elm = shapes;
        log << elm->color << "," << elm->node_count << ",";
        
        //Add nodes
        for(int j=0; j< elm->node_count; j++){
            
            log << elm->nodes[j].x << "," <<  elm->nodes[j] .y << ",";
            
        }

        
        log << elm->edge_count;
        
        //Add edges
        for (int j=0; j<elm->edge_count; j++){
            
            log << "," << elm->edges[j].node_id_a << "," << elm->edges[j].node_id_b;
            
        }
        
        //Add terminator
        log << endl;
        
        shapes++;
        
        
    }
    
    
    //Close opened file
    log.close();
    
    //Move the created files on Resources folder in your app to "data" folder.
    char cmd[256];
    sprintf(cmd, "sh mv_agent.sh %s" , withFile.c_str());
    cout << cmd << endl;
    
    cout << "CMD2 :: " << system("ls") << endl;
    cout << "CMD1 :: " << system(cmd) << endl;

    
}



void Buffer2Csv::saveSounds(sound_t *sounds, int index_count, string withFile){
    
    cout << "----" << endl;
    cout << "Buffer2Csv :: Export sound as " << withFile << endl;

    ofstream log;
    log.open(withFile , ios_base::trunc);
    
    log << "genre" << "," << "song" << "," << "slice" << "," << "effect_val" << "," << " region" << endl;

    for(int i=0; i<index_count; i++){
        
        sound_t *elm = sounds;
        log << elm->genre << "," << elm->song << ",";
        log << elm->slice << "," << elm->effect_val << ",";
        log << elm->region << endl;
        
        
        sounds++;
        
        
    }
    
    
    //Close opened file
    log.close();
    
    //Move the created files on Resources folder in your app to "data" folder.
    char cmd[256];
    sprintf(cmd, "sh mv_agent.sh %s" , withFile.c_str());
    cout << cmd << endl;
    cout << "CMD1 :: " << system(cmd) << endl;

    
}

