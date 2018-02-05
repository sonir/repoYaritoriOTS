//
//  Shape2Agent.hpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#ifndef Shape2Agent_hpp
#define Shape2Agent_hpp

//Convert Contstants
#define V_FIX 0.005 //Basic param for View
#define S_FIX 0.0055 //0.00017 //Basic param for Size
#define M_FIX 0.035 //0.0005 //Basic param for move
#define NODE_AVG 20
#define AG_SIZE_MIN 0.05f
#define MOV_MINIMUM 0.0005f


#include <stdio.h>
#include "ag_shape.h"
#include "ofxGismo.h"

ag_t shape2Agent(ag_shape_t shape);



#endif /* Shape2Agent_hpp */
