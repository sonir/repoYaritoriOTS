//
//  Csv2Buffer.cpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#include "Csv2Buffer.hpp"

void Csv2Buffer :: test () {
    
    cout << "Csv3Buffers :: test" << endl;
    
}



void Csv2Buffer::loadAgents(ag_t *agents, string withFile){
    
    
    cout << "CSV2BuF::loadAgents" << endl;
    
    //Path to the comma delimited file
    string filePath = withFile;
    

     //Load file placed in bin/data
     ofFile file(filePath);
     if(!file.exists()){
     ofLogError("The file " + filePath + " is missing");
     }
     
     ofBuffer buffer(file);
     int count = AG_NUM_OFFSET;
     
     //Read file line by line
     for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
         string line = *it;
         //Ignore first line of CSV
         if (buffer.getLines().begin() == it){
         
            continue;
         
         }
         //Split line into strings
         vector<string> words = ofSplitString(line, ",");
         //Ignore void lines
         if(words[0]=="")continue;

         
         //Store strings into a custom container
         if (words.size()>=2) {
         
             //Storage the params into a struct
             ag_t *elm = agents;
             
             elm->agid = count; //std::stoi(nullCheck(words[0]));
             elm->active = (bool)std::stoi(nullCheck(words[LOG_ACTIVE]));
             elm->posi.x = std::stof(nullCheck(words[LOG_POSI_X]));
             elm->posi.y = std::stof(nullCheck(words[LOG_POSI_Y]));
             elm->size = std::stof(nullCheck(words[LOG_SIZE]));
             elm->view = std::stof(nullCheck(words[LOG_VIEW]));
             elm->mov = std::stof(nullCheck(words[LOG_MOV]));
             elm->condition = (condition_e)std::stoi(nullCheck(words[LOG_CONDITION]));
             elm->spd.x = std::stof(nullCheck(words[LOG_SPD_X]));
             elm->spd.y = std::stof(nullCheck(words[LOG_SPD_Y]));
             elm->interact_with = std::stoi(nullCheck(words[LOG_INTERACT_WITH]));
             
             //Set the struct to vector
             agents++;
             count++;
         
         }
     } //End of for
     
//    gismo.agents.count += count;
    gismo.add.count += count;
    
}




void Csv2Buffer::loadShapes(string withFile){
    cout << "CSV2BuF::LoadShapes" << endl;

    //Path to the comma delimited file
    string filePath = withFile;
    

     //Load file placed in bin/data
     ofFile file(filePath);
     if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
     }
     
     ofBuffer buffer(file);
    
    int count = 0;
    
     //Read file line by line
     for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
         string line = *it;
         //Ignore first line of CSV
         if (buffer.getLines().begin() == it){
         
            continue;
         
         }
         
         
         
         //Split line into strings
         vector<string> words = ofSplitString(line, ",");
         //Ignore void lines
         if(words[0]=="")continue;
         
         //Store strings into a custom container
         if (words.size()>=2) {
         
             
             //Storage the params into a struct
             ag_shape_t elm;
             
             // INDEX_OF_NODE
             elm.color = std::stof(nullCheck(words[INDEX_OF_COLOR]));
             elm.node_count = std::stoi(nullCheck(words[INDEX_OF_NODE]));
             
             //EDGE INDEX
             int edge_index = (elm.node_count*2)+2;
             
             elm.edge_count = std::stoi( nullCheck(words[edge_index]) );

             int st = INDEX_OF_NODE+1;
             for(int i=0; i<elm.node_count; i++){

                elm.nodes[i].x = std::stof(nullCheck(words[st+(i*2)]));
                elm.nodes[i].y = std::stof(nullCheck(words[st+(i*2)+1]));

             }

            st = edge_index+1;
            int max = edge_index+(elm.edge_count*2);
            for(int i=0; i<elm.edge_count; i++){

                elm.edges[i].node_id_a = std::stoi(nullCheck(words[(i*2)+st]));
                
//                cout << "EDGE::" << i << " :: edge.a=" << words[(i*2)+st] << endl;
//                cout << "EDGE::" << i << " :: edge.b=" << words[(i*2)+st+1] << endl;
                elm.edges[i].node_id_b = std::stoi(nullCheck(words[(i*2)+st+1]));
                
            }

             gismo.bang("/yaritori/add_shape" , &elm);


         }
         
         
     } //End of for
     
//    gismo.agents.count += count;
//    gismo.add.count += count;
    

    
}





/*
void Csv2Buffer::loadShapes(ag_shape_t *shapes, string withFile){
    cout << "CSV2BuF::LoadShapes" << endl;

    //Path to the comma delimited file
    string filePath = withFile;
    

     //Load file placed in bin/data
     ofFile file(filePath);
     if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
     }
     
     ofBuffer buffer(file);
    
    int count = 0;
    
     //Read file line by line
     for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
         string line = *it;
         //Ignore first line of CSV
         if (buffer.getLines().begin() == it){
         
            continue;
         
         }
         
         
         
         //Split line into strings
         vector<string> words = ofSplitString(line, ",");
         //Ignore void lines
         if(words[0]=="")continue;
         
         //Store strings into a custom container
         if (words.size()>=2) {
         
             
             //Storage the params into a struct
             ag_shape_t *elm = shapes;
             
             // INDEX_OF_NODE
             elm->color = std::stof(nullCheck(words[INDEX_OF_COLOR]));
             elm->node_count = std::stoi(nullCheck(words[INDEX_OF_NODE]));
             
             //EDGE INDEX
             int edge_index = (elm->node_count*2)+2;
             
             elm->edge_count = std::stoi( nullCheck(words[edge_index]) );

             int st = INDEX_OF_NODE+1;
             for(int i=0; i<elm->node_count; i++){

                elm->nodes[i].x = std::stof(nullCheck(words[st+(i*2)]));
                elm->nodes[i].y = std::stof(nullCheck(words[st+(i*2)+1]));

             }

            st = edge_index+1;
            int max = edge_index+(elm->edge_count*2);
            for(int i=0; i<elm->edge_count; i++){

                elm->edges[i].node_id_a = std::stoi(nullCheck(words[(i*2)+st]));
                cout << "EDGE::" << i << " :: edge.a=" << words[(i*2)+st] << endl;
                cout << "EDGE::" << i << " :: edge.b=" << words[(i*2)+st+1] << endl;
                elm->edges[i].node_id_b = std::stoi(nullCheck(words[(i*2)+st+1]));
                
            }

             
             //Inc array pointer
             shapes++;
         
         }
         
         count++;
         
     } //End of for
     
//    gismo.agents.count += count;
//    gismo.add.count += count;
    

    
}
 
 */

void Csv2Buffer::loadSounds(string withFile){

    cout << "CSV2BuF::LoadSound" << endl;

    //Path to the comma delimited file
    string filePath = withFile;
    
    
    //Load file placed in bin/data
    ofFile file(filePath);
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    
    ofBuffer buffer(file);
    
    int count = 0;

    
    //Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {

        string line = *it;
        //Ignore first line of CSV
        if (buffer.getLines().begin() == it){
            
            continue;
            
        }
        
        //Split line into strings
        vector<string> words = ofSplitString(line, ",");
        //Ignore void lines
        if(words[0]=="")continue;
        
        //Store strings into a custom container
        if (words.size()>=2) {
            
            //Storage the params into a struct
            sound_t elm;
            
            elm.genre = std::stoi(nullCheck(words[0]));
            elm.song = std::stoi(nullCheck(words[1]));
            elm.slice = std::stoi(nullCheck(words[2]));
            elm.effect_val = std::stof(nullCheck(words[3]));
            elm.region = (region_e) std::stoi(nullCheck(words[4]));
            sound_unit_t unit;
            unit.elm = elm;
            unit.index = count;
            gismo.bang("/sound/push" , &unit);
            
        }
        
        count++;

        
    }

    
    
}



string Csv2Buffer::nullCheck(string word){
    
    if(word == "\0"){
        cout << "ERR : null value was detected in CSV." << endl;
        word = "0";
    }
    return word;
}
