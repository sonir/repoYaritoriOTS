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
    
    cout << "view: " << ag.view << endl;
    cout << "size: " << ag.size << endl;
    cout << "mov: " << ag.mov << endl;
    cout << "----" << endl;
    
    return ag;
    
    
}
