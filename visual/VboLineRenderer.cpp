//
//  VboLineRenderer.cpp
//  vboCircle
//
//  Created by Hana on 2018/01/23.
//
//

#include "VboLineRenderer.hpp"

VboLineRenderer::VboLineRenderer() {
    lineCount = 0;
    vertsCount = 0;
    thick = 1.0;
}

void VboLineRenderer::setup() {
    width = ofGetWidth();
    height = ofGetHeight();
    
    initVbo();
}

void VboLineRenderer::setup(float w, float h) {
    width = w;
    height = h;
    
    initVbo();
}


void VboLineRenderer::setColor(float c) {
    color = ofFloatColor(c);
}

void VboLineRenderer::setColor(ofFloatColor c) {
    color = c;
}


void VboLineRenderer::setLineWidth(float _thick) {
    thick = _thick;
}

void VboLineRenderer::initVbo() {
    vbo.setVertexData(vertices, VBOLINE_VERT_MAX, GL_DYNAMIC_DRAW);
    vbo.setColorData(colors, VBOLINE_VERT_MAX, GL_DYNAMIC_DRAW);
    vbo.setIndexData(indices, VBOLINE_VERT_MAX, GL_DYNAMIC_DRAW);
}

void VboLineRenderer::line(float x1, float y1, float x2, float y2, float _thick) {
    addVertex(this->getPosition(x1, y1));
    addVertex(this->getPosition(x2, y2));
    thick = _thick;
    
    lineCount++;
}


void VboLineRenderer::draw() {
    vbo.updateVertexData(vertices, vertsCount);
    vbo.updateColorData(colors, vertsCount);
//    vbo.updateIndexData(indices, vertsCounter);
    glLineWidth(thick);
    
    vbo.draw(GL_LINES, 0, vertsCount);

    resetCount();
}

void VboLineRenderer::addVertex(ofVec2f pos) {
    vertices[vertsCount] = pos;
    colors[vertsCount] = color;
    vertsCount++;
}

ofVec2f VboLineRenderer::getPosition(float x, float y) {
    ofVec2f pos = ofVec2f(x * width, y * height);
    return pos;
}

void VboLineRenderer::resetCount() {
    lineCount = 0;
    vertsCount = 0;
}
