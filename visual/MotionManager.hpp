//
//  MotionManager.hpp
//  yaritori
//
//  Created by Hana on 2018/01/05.
//
//

#ifndef MotionManager_hpp
#define MotionManager_hpp

#include "ofMain.h"
#include "ofxGismo.h"
#include "ag_shape.h"
#include "AgentMotion.hpp"
#include "LineManager.hpp"
#include "timed_interpolation.hpp"
//#include "Sound.hpp"

constexpr int VBO_VERTS_MAX = NODE_MAX * AG_MAX;
constexpr int VBO_EDGES_MAX = EDGE_MAX * 2 * AG_MAX;

struct shape_buf_t {
    int nodeNum, edgeNum;
    
    ofFloatColor color;
    ofVec2f nodePos[VBO_VERTS_MAX];
    ofFloatColor nodeColors[VBO_VERTS_MAX];
    //ofVec2f edgePos[NODE_MAX * AG_MAX];
    ofIndexType edgeIndices[VBO_EDGES_MAX];
    ofFloatColor edgeColors[VBO_EDGES_MAX];
    
    GLint uSizeOffset;
    float pointSize[VBO_VERTS_MAX];
};

class MotionManager : public Event {
public:
    MotionManager();
    AgentMotion agent[AG_MAX];
    int soloCount = 0;
    bool isSolo[AG_MAX];
    void setShapes();
    
    void initVbo();
    void addShape(ag_shape_t& shape);
    void addNode(ofVec2f nodePos, float size);
    void addEdgeIndices(int id_a, int id_b);
    
    void setColor(float c);
    void setEvents();
    
    void updateSolo();
    void update();
    void solo(int _id, bool status, float duration = 1.0);
    void addSolo(int _id, float duration);
    void deleteSolo(int _id);
    void draw();
    void drawAgent(ag_t* ag);
    void drawAll();
    void drawSolo();
    bool isSoloMode();
    void setTremble(animation_mode_e state);
    float aspect;
    
    
    //Method to set pointer;
    inline void setShapePtr(ag_shape_t* _pShapes) {
        pShapes = _pShapes;
        this->setShapes();
    }
    
    shape_buf_t shapeBuf;
    
private:
    GismoManager& gismo = GismoManager::getInstance();
    ag_shape_t* pShapes;

//    LineManager lineManager;
    LineDrawer interactLine[AG_MAX];
    ofShader shader;
    TimedInterpolation soloTimers[AG_MAX];
    
    bool bSolo;
    
    ofVbo nodeVbo, edgeVbo;
//    int nodeCount, edgeCount;
//    ofVec2f nodePos[NODE_MAX * AG_MAX];
//    ofFloatColor nodeColors[NODE_MAX * AG_MAX];
//    ofVec2f edgePos[NODE_MAX * AG_MAX];
//    ofIndexType edgeIndices[EDGE_MAX * 2 * AG_MAX];
//    ofFloatColor edgeColors[EDGE_MAX * 2 * AG_MAX];

};



#endif /* MotionManager_hpp */
