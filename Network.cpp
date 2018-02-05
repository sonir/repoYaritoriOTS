//
//  Network.cpp
//  yaritori
//
//  Created by sonir on 12/23/17.
//
//

#include "Network.hpp"


void Network :: setup(){
    
    cout << "network:setup()" << endl;
    
    receiver.setup(IN_PORT);
    current_msg_string = 0;
    
}

void Network :: update(){
    
//    cout << "Newwork::update" << endl;
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/agent_control"){
            
            string adr = m.getArgAsString(0);
            int agid = m.getArgAsInt(1);
            ag_t *pAg = gismo.getAgent(agid);
            
            if(adr == "/position"){
                
                pAg->posi.x = m.getArgAsFloat(2);
                pAg->posi.y = m.getArgAsFloat(3);
                cout << "POS :: " <<  pAg->posi.x << " , " << pAg->posi.y << endl;
            
            }else if(adr=="/view"){
                
                 pAg->view = m.getArgAsFloat(2);
                cout << "VIEW:: " << pAg->view << endl;
                
                
            }else if(adr=="/mov"){
                
                 pAg->mov = m.getArgAsFloat(2);
                cout << "MOV:: " << pAg->mov << endl;
                
            }
            
        } else if (m.getAddress() == "/mask" ) {
            param_u tmp[4];
            tmp[0].ival = m.getArgAsInt(0); //Window ID
            tmp[1].ival = m.getArgAsInt(1); //Vertex ID
            tmp[2].fval = m.getArgAsFloat(2);
            tmp[3].fval = m.getArgAsFloat(3);
            gismo.bang("/mask", &tmp);
            
        } else if( m.getAddress() == "/yaritori/post" /*"/que"*/ ){ //Receiving Agents
            
            cout << "Network :: /outline received" << endl;
            
            if(gismo.agents.count >= (AG_MAX*0.9) ){
             
                cout << "agent max reached." << endl;
                return;
                
            }
            
            shape.color = m.getArgAsFloat(INDEX_OF_COLOR);
            shape.node_count = m.getArgAsInt32(INDEX_OF_NODE);
            int index_of_edge_count = (shape.node_count*2)+2;
            shape.edge_count = m.getArgAsInt32( index_of_edge_count );
            
            int node_index = 0;
            
            for(int i=INDEX_OF_NODE+1; i<(shape.node_count*2)+1; i=i+2){
                shape.nodes[node_index].x = m.getArgAsFloat(i);
                shape.nodes[node_index].y = m.getArgAsFloat(i+1);
                node_index+=1;
            }
            
            int edge_index = 0;
            for(int i=0;i<( (shape.edge_count*2) );i=i+2){

                shape.edges[edge_index].node_id_a = m.getArgAsInt32( i + (index_of_edge_count+1) );
                shape.edges[edge_index].node_id_b = m.getArgAsInt32( i + (index_of_edge_count+1) + 1 );
                edge_index+=1;
            }
            
            gismo.bang("/addAgentWithShape" , &shape);
            dispParams(shape);
            
        } else if (m.getAddress() == "/yaritori/save"){
            
            //Save now Conditions
            int flg = 1;
            gismo.bang("/yaritori/save", &flg);

            
            
        } else if ( m.getAddress() == "/fps" ) { //Set fps
            
            float fval = m.getArgAsFloat(0);
            gismo.bang("/fps", &fval );
            
        }else if (m.getAddress() == "/performance/set_position" ) {
            
            param_u args[3];
            args[0].ival = m.getArgAsInt32(0); //performer_id
            args[1].fval = m.getArgAsFloat(1); //x posi
            args[2].fval = m.getArgAsFloat(2); //y posi
            gismo.bang("/performance/set_position" , args);
            
            
        }else if (  m.getAddress() == "/ch1" ) { //Receiving bullet bang from performer
            
            
            int performer_id = m.getArgAsInt32(0);
            gismo.bang("/performance/atk" , &performer_id);
            
            
        } else if ( m.getAddress() == "/performance/mode" ){
        
            param_u mode;
            mode.ival = m.getArgAsInt32(0);
            gismo.bang("/performance/mode" , &mode);
        
        } else if ( m.getAddress() == "/performance/bullets/speed" ){
            
            param_u spd;
            spd.ival = m.getArgAsInt32(0);
            gismo.bang("/performance/bullets/speed" , &spd);
            
        } else if (  m.getAddress() == "/gismo/view_ratio") {
            
            gismo.view_ratio = m.getArgAsFloat(0);
            
        } else if (  m.getAddress() == "/gismo/mov_ratio") {
            
            gismo.mov_ratio = m.getArgAsFloat(0);
            
            
            
        }else if (  m.getAddress() == "/reset" ) { //Reset Agents
            
            int key_num = m.getArgAsInt32(0);
            if (key_num == 137) gismo.bang("/gismo/reset" , &key_num);
            
            
        } else {
            
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
            
        }
        
    }
    
}



void Network::dispParams(ag_shape_t shape){
    
    
    using namespace std;
    cout<< "nodes x " << shape.node_count << endl;
    
    
    for(int i=0;i<shape.node_count;i++){
        
        cout << i << " :  x=" << shape.nodes[i].x << " y=" << shape.nodes[i].y << endl;
        
        
    }
    
    cout<< "edges x " << shape.edge_count << endl;
    for(int i=0;i<shape.edge_count;i++){
        
        cout << i << " :  x=" << shape.edges[i].node_id_a << " y=" << shape.edges[i].node_id_b << endl;
        
        
    }
    
    cout << "color = " << shape.color << endl;
    
    cout << "----" << endl;
    
    
}

