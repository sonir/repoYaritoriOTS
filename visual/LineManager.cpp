//
//  LineManager.cpp
//  yaritori
//
//  Created by Momoha Matsuhashi on 2018/01/30.
//
//

#include "LineManager.hpp"

LineManager::LineManager(){
    init();
}

void LineManager::init(){
    initVbo();
}

void LineManager::initVbo(){
    vbo.setIndexData(indices, ((TURN_NUM_MAX + 2) * 2) * AG_MAX, GL_DYNAMIC_DRAW);
    vbo.setColorData(cols, (TURN_NUM_MAX + 2) * AG_MAX, GL_DYNAMIC_DRAW);
    vbo.setVertexData(verts, (TURN_NUM_MAX + 2) * AG_MAX, GL_DYNAMIC_DRAW);
}

void LineManager::update(){
    for(int j = 0; j < AG_MAX; j++){
        if(interactLine[j].isRunning){
            int ag = j;
            int vertsNum = interactLine[ag].turn_num + 2;
            for(int i = 0; i < vertsNum; i++){
                verts[vertsCounter].set(interactLine[ag].verts[i]);
                
                if(i < (vertsNum - 1)){
                    indices[indicesCounter] = vertsCounter;
                    cols[indicesCounter] = interactLine[ag].cols[i];
                    indicesCounter++;
                    
                    indices[indicesCounter] = vertsCounter + 1;
                    cols[indicesCounter] = interactLine[j].cols[i];
                    indicesCounter++;
                }
                vertsCounter++;
            }
        }
    }
    
    vbo.updateVertexData(verts, vertsCounter);
    vbo.updateColorData(cols, indicesCounter);
    vbo.updateIndexData(indices, indicesCounter);
}

void LineManager::reset(){
    indicesCounter = 0;
    vertsCounter = 0;
    
    for(int i = 0; i < AG_MAX; i++){
        interactLine[i].isRunning = false;
    }
}

void LineManager::draw(){
    update();
    glLineWidth(0.02);
    vbo.drawElements(GL_LINES, indicesCounter);
    
    
    reset();
}

void LineManager::lineTo(int _fromId, float _fromPos_x, float _fromPos_y, float _toPos_x, float _toPos_y, float _size){
    interactLine[_fromId].myPos.x = _fromPos_x;
    interactLine[_fromId].myPos.y = _fromPos_y;
    interactLine[_fromId].lineTo(_toPos_x, _toPos_y, _size);
    
    interactLine[_fromId].isRunning = true;
}
