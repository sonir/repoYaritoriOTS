//
//  Csv2Buffers.cpp
//  SonilabMediaController
//
//  Created by sonir on 7/22/16.
//
//

#include "Csv2Buffers.hpp"

Csv2Buffers::Csv2Buffers(){
    
    
}


void Csv2Buffers::createAgents(){
    

    std::cout << "foo" << std::endl;
     //Create a vector to storage scenes
     // vector<ag_t> scenes;
    //Path to the comma delimited file
    //string filePath = "_agents.csv";

    /*
        //Load file placed in bin/data
    ofFile file(filePath);   
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }

    ofBuffer buffer(file);
    
    //Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        //Ignore first line of CSV
        if (buffer.getLines().begin() == it){
            
            continue;
            
        }
        //Split line into strings
        vector<string> words = ofSplitString(line, ",");
        
        //Store strings into a custom container
        if (words.size()>=2) {

            //Storage the params into a struct
            ag_t *elm = agents;
            
            elm->agid = std::stoi(nullCheck(words[0]));
            elm->active = (bool)std::stoi(nullCheck(words[1]));
            elm->posi.x = std::stof(nullCheck(words[2]));
            elm->posi.y = std::stof(nullCheck(words[3]));
            elm->size = std::stof(nullCheck(words[4]));
            elm->view = std::stof(nullCheck(words[5]));
            elm->mov = std::stof(nullCheck(words[6]));
            elm->condition = (condition_e)std::stoi(nullCheck(words[7]));
            elm->spd.x = std::stof(nullCheck(words[7]));
            elm->spd.y = std::stof(nullCheck(words[8]));
            elm->interact_with = std::stoi(nullCheck(words[9]));
            
            //Set the struct to vector
            agents++;
            
        }
    } //End of for
    
*/
     
    
    
}

string Csv2Buffers::nullCheck(string word){
    
    if(word == "\0"){
        cout << "ERR : null value was detected in CSV." << endl;
        word = "0";
    }
    return word;
}


//-----------------------------
void Csv2Buffers::test(){
    
    std::cout << "CSV::TEST" << std::endl;
    
}
