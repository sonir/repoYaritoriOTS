//
//  Shape2Agent.cpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#include "Shape2Agent.hpp"

ag_t shape2Agent(ag_shape_t shape){
    
    ag_t ag;
    initAgentActive(&ag);
    
    ag.view = shape.edge_count * V_FIX;
    ag.size = shape.node_count * S_FIX;
    
    //limit mini
    if (ag.size < AG_SIZE_MIN)ag.size = AG_SIZE_MIN;
    
    if (shape.node_count !=0){
        ag.mov = ( (float) NODE_AVG / shape.node_count ) * M_FIX;
    } else {

        ag.mov = ( (NODE_AVG * 2) * M_FIX );
        
    }
    if(ag.mov < MOV_MINIMUM){

        ag.mov = MOV_MINIMUM;

    }
    
    //OverWrite the agent position with cetering with 3sceen
    ag.posi = makePositionToAdd();
    
    cout << "view: " << ag.view << endl;
    cout << "size: " << ag.size << endl;
    cout << "mov: " << ag.mov << endl;
    cout << "----" << endl;
    
    return ag;
    
    
}


posi_t makePositionToAdd(){
    
    posi_t posi;
    int screen_id = irand()%3;
    
    
//    cout << "@@" << screen_id << endl;
    switch(screen_id){
            
        case 0:
            posi.x = WORLD_WIDTH * ( 0.12f + ( 0.1f * frand() ) );
            break;

        case 1:
            posi.x = WORLD_WIDTH * ( 0.46f + ( 0.1f * frand() ) );
            break;

        case 2:
            posi.x = WORLD_WIDTH * ( 0.8f + ( 0.1f * frand() ) );
            break;
            
    }
    
    posi.y = ( WORLD_HEIGHT*0.4f ) + ( 0.2f * frand() ) ;
    
//    cout << "@@" << posi.x << "," << posi.y << endl;
    
    return posi;
    
    
}
