//
//  shape.h
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#ifndef shape_h
#define shape_h

typedef enum shape_type {VOID, CIRCLE, TRIANGLE, SQUARE, RECT, LINE, ARC, WAVE } shape_type;

typedef struct shapeContainer {
    
    shape_type type;
    bool active;
    int uid;
    float x1;
    float y1;
    float x2;
    float y2;
    
    float size;
    float height;
    float angle;
    float freq;
    float amp;
    float phase;
    float expose;
    float thick;
    bool fill;
    
    
    
} shapeContainer;



#endif /* shape_h */
