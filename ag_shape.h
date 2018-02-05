//
//  ag_shape.h
//  receiveTest
//
//  Created by sonir on 12/29/17.
//
//

#ifndef ag_shape_h
#define ag_shape_h

#define NODE_MAX 128
#define EDGE_MAX NODE_MAX*8

typedef struct node_t {
    
    float x;
    float y;
    
}node_t_t;


typedef struct edge_t {
    
    int node_id_a;
    int node_id_b;
    
    
}edge_t;


typedef struct ag_shape_t {

    node_t nodes[NODE_MAX];
    edge_t edges[EDGE_MAX];

    float color;    
    int node_count;
    int edge_count;
    
    
} ag_shape_t;

#endif /* ag_shape_h */
