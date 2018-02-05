//
//  VboLineRenderer.hpp
//  vboCircle
//
//  Created by Hana on 2018/01/23.
//
//

#ifndef VboLineRenderer_hpp
#define VboLineRenderer_hpp

#include "ofMain.h"
#include "ofxGismo.h"

constexpr int VBOLINE_NUM_PER_AG = 64;
constexpr int VBOLINE_NUM_MAX = VBOLINE_NUM_PER_AG * AG_MAX;
constexpr int VBOLINE_VERT_MAX = VBOLINE_NUM_MAX * 2;

class VboLineRenderer {
public:
    VboLineRenderer();
    void setup();
    void setup(float w, float h);
    void setColor(float c);
    void setColor(ofFloatColor c);
    void setLineWidth(float _thick);
    
    
    void line(float x1, float y1, float x2, float y2, float _thick);
    
    void draw();
    
private:
    void initVbo();
    void addVertex(ofVec2f pos);
    void resetCount();
    ofVec2f getPosition(float x, float y);
    
    float width, height, thick;
    ofFloatColor color;
    int lineCount, vertsCount;;
    
    //VBO
    ofVbo vbo;
    ofVec2f vertices[VBOLINE_VERT_MAX];
    ofFloatColor colors[VBOLINE_VERT_MAX];
    ofIndexType indices[VBOLINE_VERT_MAX];
    
};

#endif /* VboLineRenderer_hpp */
