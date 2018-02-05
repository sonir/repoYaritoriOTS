//
//  LineManager.hpp
//  yaritori
//
//  Created by Momoha Matsuhashi on 2018/01/30.
//
//

#ifndef LineManager_hpp
#define LineManager_hpp

#include "LineDrawer.hpp"
#include "ofxGismo.h"
#include "animation_setup.hpp"
#include "screen_setup.h"

class LineManager : public Event {
public:
    LineManager();
    void update();
    void draw();
    
    void lineTo(int fromId, float fromPos_x, float fromPos_y, float toPos_x, float toPos_y, float size);
    
    LineDrawer interactLine[AG_MAX];
    
private:
    void init();
    void initVbo();
    void reset();
        
    ofVec2f verts[(TURN_NUM_MAX + 2) * AG_MAX];
    ofFloatColor cols[(TURN_NUM_MAX + 2) * AG_MAX];
    ofIndexType indices[((TURN_NUM_MAX + 2) * 2) * AG_MAX];
    ofVbo vbo;
    
    int vertsCounter;
    int indicesCounter;
};


#endif /* LineManager_hpp */
