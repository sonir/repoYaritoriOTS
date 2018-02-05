//
//  AgentMotion.cpp
//  yaritori
//
//  Created by Hana on 2017/12/23.
//
//

#include "AgentMotion.hpp"


AgentMotion::AgentMotion() {
    color = 0.0;
    width_rate = 1.0f;
    size = 0.03;
    center.x = -100.0;
    center.y = -100.0;
    pShape = &this->shape;
    
    resetShape();
    initModulation();
    initVbo();
    
    //shader.load("shader/shader.vert", "shader/shader.frag");
    
    animationMode = ANIMATION_MODE_NORMAL;
//    animationMode = ANIMATION_MODE_TREMBLE;
//    trembleTimer.ready();
    
//    setModValues();
    isFirst = true;
    
}

void AgentMotion::resetShape() {
    center.x = frand()-0.5;
    center.y = frand()-0.5;
    dest.x = center.x;
    dest.y = center.y;
    

    shape.node_count = 64;
    shape.edge_count = 32;
    
    for(int i = 0; i < NODE_MAX; i++) {
        shape.nodes[i].x = frand() - 0.5;
        shape.nodes[i].y = frand() - 0.5;

    }
    
    for (int i = 0; i <  shape.edge_count; i++) {
        shape.edges[i].node_id_a = 0;
        shape.edges[i].node_id_b = 1;
    }
}

void AgentMotion::initModulation() {    
    ofVec2f vel;
    for(int i = 0; i < NODE_MAX; i++) {
        vel = ofVec2f(frand() * 2.0 - 1.0, frand() * 2.0 - 1.0).getNormalized();
        velocityX[i] = vel.x;
        velocityY[i] = vel.y;
    }
    
    for(int i = 0; i < MOD_NUM; i++) {
    
        modStep[i] = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
        carStep[i] = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
        
        carPhase[i] = 0.0;
        carStep[i] = 0.0;
    }
    t = 0.0f;
    sizeMod = 0.0f;
    size_t = 0.0f;
    
    tremble = 0.01;
}


void AgentMotion::initVbo() {
    
    ofVec2f pos;
    for(int i = 0; i < pShape->node_count; i++) {
        pos.x = ( center.x + (pShape->nodes[i].x * size)) * BASE_HEIGHT;
        pos.y = ( center.y + (pShape->nodes[i].y * size)) * BASE_HEIGHT;
        
        nodePos[i] = pos;
        nodeColors[i] = ofFloatColor(color);
    }
    
    int edge_index;
    for (int i = 0; i < pShape->edge_count; i++) {
        edge_index = i*2;
        edgeIndices[edge_index] = pShape->edges[i].node_id_a;
        edgeIndices[edge_index+1] = pShape->edges[i].node_id_b;
        edgeColors[edge_index] = ofFloatColor(color);
        edgeColors[edge_index+1] = ofFloatColor(color);
    }
    
    nodeVbo.setVertexData(nodePos, NODE_MAX, GL_DYNAMIC_DRAW);
    nodeVbo.setColorData(nodeColors, NODE_MAX, GL_DYNAMIC_DRAW);

    edgeVbo.setVertexData(nodePos, NODE_MAX, GL_DYNAMIC_DRAW);
    edgeVbo.setColorData(edgeColors, EDGE_MAX * 2, GL_DYNAMIC_DRAW);
    edgeVbo.setIndexData(edgeIndices, EDGE_MAX*2, GL_DYNAMIC_DRAW);
}

void AgentMotion::updateColors() {
    for(int i = 0; i < pShape->node_count; i++) {
        nodeColors[i] = ofFloatColor(color);
    }
    int edge_index;
    for (int i = 0; i < pShape->edge_count * 2; i += 2) {
        edge_index = i * 0.5;
        edgeColors[i] = ofFloatColor(color);
        edgeColors[i+1] = ofFloatColor(color);
    }
    
//    nodeVbo.updateColorData(nodeColors, pShape->node_count);
//    edgeVbo.updateColorData(edgeColors, pShape->edge_count * 2);
}

void AgentMotion::updateCenter() {
    ofVec2f diff = dest - center;
    float length = diff.length() * BASE_HEIGHT;

    if(DISPLAY_HEIGHT * 0.8 < length) {
        center = dest;
    } else {
        switch(animationMode) {
            case ANIMATION_MODE_NORMAL:
//                center += (dest - center) * EASING_RATIO;
                center = dest;
                break;
            case ANIMATION_MODE_TREMBLE:
                //Set tremble
//                    noise.x = (frand() - 0.5 ) * 2.0 * TREMBLE_RATIO_CENTER * ( 1.0 -  pAg->size);
//                    noise.y = (frand() - 0.5 ) * 2.0 * TREMBLE_RATIO_CENTER * ( 1.0 -  pAg->size);
                noise.x = frand() * 2.0 - 1.0;  //becomes -1.0 to 1
                noise.y = frand() * 2.0 - 1.0;
                center = (dest + noise * tremble);
                break;
        }        
    }
}

void AgentMotion::updatePhase() {
    // Update Phases

    //Set least value of mov
    float fixedAgMov = pAg->mov;
    if(fixedAgMov < 0.05) {
        fixedAgMov = 0.05;
    }
    
    for(int i = 0; i < MOD_NUM; i++) {
        carPhase[i] += carStep[i] * fixedAgMov * MOV_FIX;    //Carrier
        if(M_2XPI < carPhase[i]) {
            carPhase[i] = 0.0;
        }

        modPhase[i] += modStep[i] * fixedAgMov * MOV_FIX;    //Modulater
        if(M_2XPI < modPhase[i]) {
            modPhase[i] = 0.0;
        }

        phase[i] = (sin(carPhase[i]) + sin(modPhase[i])) * 0.5 * TREMOR_RATIO;
    }
    
    sizeMod = (sin(size_t) + 1.0) * 0.5 * SIZE_MOD_STRENGTH + SIZE_MOD_FLOOR;
}



void AgentMotion::updatePosition() {
    
    ofVec2f pos;
    
    for(int i = 0; i < pShape->node_count; i++) {
        //Modulation by CPU
        float nodeX = (pShape->nodes[i].x + velocityX[i] * phase[i % MOD_NUM ] ) * pAg->size * sizeMod * SIZE_FIX;
        float nodeY = (pShape->nodes[i].y + velocityY[i] * phase[i % MOD_NUM ] ) * pAg->size * sizeMod * SIZE_FIX;
        
        pos.x = (center.x + nodeX) * BASE_WIDTH;
        pos.y = (center.y + nodeY) * BASE_HEIGHT;
        
        //Modulation by Shader
//        ofVec2f pos;
//        pos.x = ( center.x + (pShape->nodes[i].x * pAg->size)) * CANVAS_HEIGHT;
//        pos.y = ( center.y + (pShape->nodes[i].y * pAg->size)) * CANVAS_HEIGHT;
        
        //Set position into array
        nodePos[i] = pos;
    }
    nodeVbo.updateVertexData(nodePos, pShape->node_count);
    edgeVbo.updateVertexData(nodePos, pShape->node_count);
}

void AgentMotion::updateIndex() {
    for (int i = 0; i < pShape->edge_count; i++) {
        if(pShape->edges[i].node_id_a < pShape->node_count && pShape->edges[i].node_id_b < pShape->node_count) {
            int edge_index = i*2;
            
            edgeIndices[edge_index] = pShape->edges[i].node_id_a;
            edgeIndices[edge_index+1] = pShape->edges[i].node_id_b;
            edgeColors[edge_index] = ofFloatColor(color);
            edgeColors[edge_index+1] = ofFloatColor(color);
        }
    }
    edgeVbo.updateIndexData(edgeIndices, pShape->edge_count*2);
}

void AgentMotion::updateStep() {
    size_t += SIZE_MOD_STEP;
    if(M_2XPI < size_t) {
        size_t = 0.0f;
    }
}

void AgentMotion::update() {
    //For shader modulation
//    t += pAg->mov * dx;
//    if(M_2XPI < t) {
//        t = 0.0f;
//    }
    
   
    //setModValues();
    
    updateStep();
    updateCenter();
    updatePhase();
    updatePosition();
    updateIndex();
}

void AgentMotion::draw() {
    
//    shader.begin();
//    shader.setUniform1f("t", t);
//    shader.setUniform1f("color", color);
//    shader.setUniform1i("CANVAS_HEIGHT", CANVAS_HEIGHT);
//    shader.setUniform1f("size", size);
//    shader.setUniform1fv("carStep", carStep);
//    shader.setUniform1fv("modStep", modStep);
//    shader.setUniform1f("centerX", center.x*screenWidth);
//    shader.setUniform1f("centerY", center.y*screenWidth);
    
    nodeVbo.updateColorData(nodeColors, pShape->node_count);
    edgeVbo.updateColorData(edgeColors, pShape->edge_count * 2);
    
    if(pShape->node_count != 0) {
//        glEnable(GL_POINT_SMOOTH);
//        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_BLEND);
        glPointSize(getPointSize());
        nodeVbo.draw(GL_POINTS, 0, pShape->node_count);
    }
   
    if(pShape->edge_count != 0) {
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(getLineWidth());
        edgeVbo.drawElements(GL_LINES, pShape->edge_count * 2);
    }
//    shader.end();
}



float AgentMotion::getPointSize() {
    float pointSize = 3.5;
    if(size < 0.02) {
        pointSize = 2.0;
    } else if (0.02 <= size && size < 0.03) {
        pointSize = 2.0;
    } else if(0.03 <= size && size < 0.04) {
        pointSize = 2.5;
    } else if(0.04 <= size && size < 0.05) {
        pointSize = 3.0;
    } else {
        pointSize += 8.0 * size;
    }
    
    return pointSize;
}

float AgentMotion::getLineWidth() {
    float lineWidth = 0.5;
    if(size <= 0.01) {
        lineWidth = 0.05;
    } else if (0.01 < size && size < 0.02) {
        lineWidth = 0.1;
    } else if(0.02 <= size && size < 0.05) {
        lineWidth = 0.25;
    }
    
    return lineWidth;
}

void AgentMotion::setShapePtr(ag_shape_t * shapePtr) {
    pShape = shapePtr;
    
}

void AgentMotion::setColor(float c) {
    color = c;
    this->updateColors();
}


void AgentMotion::move(float x, float y) {
    if(isFirst) {
        dest.x = x;
        dest.y = y;
        center.x = x;
        center.y = y;
        isFirst = false;
    } else {
        dest.x = x;
        dest.y = y;
    }
}


void AgentMotion::setAnimationMode(animation_mode_e _animationMode) {
    animationMode = _animationMode;
    //setModValues();
}

//void AgentMotion::setModValues() {
//    switch(animationMode) {
//        case ANIMATION_MODE_NORMAL: {
//            tremorRatio = TREMOR_RATIO;
//            stayRatio = STAY_RATIO;
//            
//            sizeModStrength =SIZE_MOD_STRENGTH;
//            sizeModFloor = SIZE_MOD_FLOOR;
//            sizeModStep = SIZE_MOD_STEP;
//            modBoost = 1.0;
//            break;
//        }
//        case ANIMATION_MODE_TREMBLE: {
//            tremorRatio = TREMBLE_TREMOR_RATIO;
//            stayRatio = TREMBLE_STAY_RATIO;
//            
//            sizeModStrength = TREMBLE_SIZE_MOD_STRENGTH;
//            sizeModFloor = TREMBLE_SIZE_MOD_FLOOR;
//            sizeModStep = TREMBLE_SIZE_MOD_STEP;
//            
//            modBoost = TREMBLE_STEP_BOOST;
//            trembleTimer.bang(TREMBLE_INTERVAL_CENTER);
//        }
//    }
//}
