//
//  MotionManager.cpp
//  yaritori
//
//  Created by Hana on 2018/01/05.
//
//

#include "MotionManager.hpp"
#include <cassert>

MotionManager::MotionManager() {
    //Reset solo
    soloCount = 0;
    for(int i = 0; i < AG_MAX; i++) {
        isSolo[i] = false;
        soloTimers[i].ready();
        
    }
    
    aspect = gismo.width_rate;
    
    setEvents();
}

void MotionManager::initVbo() {
    shapeBuf.nodeNum = 0;
    shapeBuf.edgeNum = 0;
    shapeBuf.color = 0.0;
    
    nodeVbo.setAttributeData(shader.getAttributeLocation("point_size"), shapeBuf.pointSize, 1, VBO_VERTS_MAX, GL_DYNAMIC_DRAW);
    nodeVbo.setVertexData(shapeBuf.nodePos, VBO_VERTS_MAX, GL_DYNAMIC_DRAW);
    nodeVbo.setColorData(shapeBuf.nodeColors, VBO_VERTS_MAX, GL_DYNAMIC_DRAW);
    
    edgeVbo.setVertexData(shapeBuf.nodePos, VBO_EDGES_MAX, GL_DYNAMIC_DRAW);
    edgeVbo.setColorData(shapeBuf.edgeColors, VBO_EDGES_MAX, GL_DYNAMIC_DRAW);
    edgeVbo.setIndexData(shapeBuf.edgeIndices, VBO_EDGES_MAX, GL_DYNAMIC_DRAW);
}



void MotionManager::addNode(ofVec2f nodePos, float size) {
    shapeBuf.nodePos[shapeBuf.nodeNum] = nodePos;
    shapeBuf.pointSize[shapeBuf.nodeNum] = size;
    shapeBuf.nodeColors[shapeBuf.nodeNum] = shapeBuf.color;
    shapeBuf.nodeNum++;
}


void MotionManager::addEdgeIndices(int id_a, int id_b) {
    shapeBuf.edgeIndices[shapeBuf.edgeNum] = id_a;
    shapeBuf.edgeNum++;
    shapeBuf.edgeIndices[shapeBuf.edgeNum] = id_b;
    shapeBuf.edgeNum++;
}

void MotionManager::setColor(float c) {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].setColor(c);
        interactLine[i].setColor(c);
    }
}


void MotionManager::setEvents() {
    GismoManager& gismo = GismoManager::getInstance();
    
    auto colorEvent = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        float c = params[0].fval;
        
        this->setColor(c);
    };
    
    gismo.lambdaAdd("/agentColor", colorEvent);
    
    
    auto trembleEvent = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        bool enable = params[0].bval;
        
        if(enable) {
            this -> setTremble(ANIMATION_MODE_TREMBLE);
        } else {
            this -> setTremble(ANIMATION_MODE_NORMAL);
        }
    };
    
    gismo.lambdaAdd("/tremble", trembleEvent);
    
    
}

void MotionManager::setShapes() {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].pShape = &pShapes[i];
        agent[i].initVbo();
    }
}

void MotionManager::solo(int _id, bool status, float duration) {
    if(status != 0) {
        addSolo(_id, duration);
    } else {
        deleteSolo(_id);
    }
}

void MotionManager::addSolo(int _id, float duration) {
    isSolo[_id] = true;
    soloTimers[_id].bang(duration * 1000.0);
    soloCount++;

}

void MotionManager::deleteSolo(int _id) {
    isSolo[_id] = false;
    soloCount--;
    soloTimers[_id].ready();
}


void MotionManager::updateSolo() {
    soloCount = 0;
    for(int i = 0; i < AG_MAX; i++){
        if(isSolo[i]) {
            float val = soloTimers[i].get();
            if (1.0 <= val) {
                deleteSolo(i);
            }
            soloCount++;
        }
    }
}

void MotionManager::update() {
    updateSolo();
}


void MotionManager::drawAll() {    
    int count = gismo.agents.count;
    ag_t* agents = gismo.getAgents(); //sets agents pointer
    ag_t* ag;
    
    for(int i = 0; i < count; i++){
        
        ag = agents; //Set agent address
        if(ag->active){
            //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
            agent[i].pAg = ag;
            agent[i].move(ag->posi.x, ag->posi.y);

            agent[i].update();
            agent[i].draw();
            
//            ofSetColor(255, 0, 0);
//            ofDrawBitmapString(i, ag->posi.x * aspect * BASE_HEIGHT, ag->posi.y * BASE_HEIGHT);
//            ofDrawCircle(ag->posi.x * BASE_HEIGHT * aspect, ag->posi.y * BASE_HEIGHT, 3);
            
            //Draw interaction
            if(ag->interact_with != -1) {
                int targetID = ag->interact_with;
                ag_t* target = gismo.getAgent(targetID);
                
                if(ag->condition == CHASE && target->condition == RUN) {
//                    lineManager.lineTo(i, agent[i].center.x, agent[i].center.y, agent[targetID].center.x, agent[targetID].center.y, agent[i].size);
                    interactLine[i].myPos.x = agent[i].center.x;
                    interactLine[i].myPos.y = agent[i].center.y;
                    interactLine[i].lineTo(agent[targetID].center.x, agent[targetID].center.y, agent[i].size);
                    
                }
            }
        }
        agents++;
    }

//    lineManager.draw();
}

void MotionManager::drawSolo() {
    int count = gismo.agents.count;
    ag_t* agents = gismo.getAgents(); //sets agents pointer
    ag_t* ag;
    
    for(int i =0; i < count; i++){
        
        ag = &agents[i];
        
        if(ag->active)  {
            agent[i].pAg = ag;
            agent[i].move(ag->posi.x, ag->posi.y);
            
            agent[i].update();
            
            if(isSolo[i]) {
                agent[i].draw();
            

                //Draw Interaction
                if(ag->interact_with != -1) {
                    int targetID = ag->interact_with;
                    ag_t* target = gismo.getAgent(targetID);
                    
                    if(ag->condition == CHASE && target->condition == RUN) {
//                        lineManager.lineTo(i, agent[i].center.x, agent[i].center.y, agent[targetID].center.x, agent[targetID].center.y, agent[i].size);
                        interactLine[i].myPos.x = agent[i].center.x;
                        interactLine[i].myPos.y = agent[i].center.y;
                        interactLine[i].lineTo(agent[targetID].center.x, agent[targetID].center.y, agent[i].size);
                        
                    }
                }
            }
        }
        //agents++;
    }
//    lineManager.draw();
}


void MotionManager::draw() {
    if(soloCount == 0) {
        drawAll();
        
    } else {
        drawSolo();
    }

//    ofSetColor(ofFloatColor(color));
//    nodeVbo.updateVertexData(vbo.nodePos, vbo.nodeNum);
//    nodeVbo.updateColorData(vbo.nodeColors,  vbo.nodeNum);
//    nodeVbo.draw(GL_POINTS, 0, vbo.nodeNum);
    
}

bool MotionManager::isSoloMode() {
    bool result = false;
    if (soloCount == 0) {
        result = false;
    } else {
        result = true;
    }
    
    return result;
}


void MotionManager::setTremble(animation_mode_e state) {
    for(int i = 0; i < AG_MAX; i++) {
        agent[i].animationMode = state;
        
    }
}


