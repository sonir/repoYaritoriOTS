//
//  drawer.cpp
//
//  Created by Hana on 2017/09/08.
//
//


#include "drawer.hpp"

int width;
int height;

void initCanvasSize(int w, int h) {
    width = w;
    height = h;
}


void circle(float x, float y, float size, int fill) {
    //Fill Setting
    if(fill == 1) {
        ofFill();
    } else {
        ofNoFill();
        ofSetLineWidth(2.0);
    }
    
    //Draw Circle
    int radius = size * width;
    ofDrawCircle(x * width, y * height, radius);
}


void triangle(float x, float y, float size, float angle, int fill) {
    //Ready Variables
    ofVec2f center, normalizedTop, normalizedLeft, normalizedRight;
    double root3 = sqrt(3.0);
    float scaledSize = width * size;
    
    //Culcrate each top
    center.set(x * width, y * height);
    normalizedTop.set(0, -root3 / 3);
    normalizedLeft.set(-0.5, root3 / 6);
    normalizedRight.set(0.5, root3 / 6);
    
    ofVec2f top = normalizedTop * scaledSize;
    ofVec2f left = normalizedLeft * scaledSize;
    ofVec2f right = normalizedRight * scaledSize;
    
    
    if(fill == 1) {
        ofFill();
    } else {
        ofNoFill();
        ofSetLineWidth(2.0);
    }
    
    ofPushMatrix();
    ofTranslate(center);
    ofRotate(360 * angle);
    ofDrawTriangle(top, left, right);
    ofPopMatrix();
}



void square(float x, float y, float size, float angle, int fill) {
    //Fill Setting
    if(fill == 1) {
        ofFill();
    } else {
        ofNoFill();
        ofSetLineWidth(2.0);
    }
    
    //Draw
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(x * width, y * height);
    ofRotate(360 * angle);
    ofDrawRectangle(0, 0, size * width, size * width);
    ofPopMatrix();
}

void rect(float x1, float y1, float x2, float y2, float angle, int fill) {
    //Fill Setting
    if(fill == 1) {
        ofFill();
    } else {
        ofNoFill();
        ofSetLineWidth(2.0);
    }
    
    //Culcurate Position and Dimension
    float centerX = width *(x1 + x2) / 2;
    float centerY = height *(y1 + y2) / 2;
    float rectWidth = width * abs(x1 - x2) ;
    float rectHeight = height * abs(y1 - y2);
    
    //Draw
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(centerX, centerY);
    ofRotate(360 * angle);
    ofDrawRectangle(0, 0, rectWidth, rectHeight);
    ofPopMatrix();
}

void line(float x1, float y1, float x2, float y2, float thick) {
    ofSetLineWidth(thick);
    ofDrawLine(width * x1, height * y1, width * x2, height * y2);
}

void arc(float x1, float y1, float x2, float y2, float arcHeight, float expose, float thick) {
    
    
    //Prepare for culculate
    ofVec2f center = ofVec2f((x1 + x2) * 0.5, (y1 + y2) * 0.5);
    float line_x = x2 - x1;
    float line_y = y2 - y1;
    
    //Get control position
    float control_x, control_y;
    float normalizedLine = 1.0 / sqrt(line_x * line_x + line_y * line_y);
    float ux = normalizedLine * line_x;
    float uy = normalizedLine * line_y;
    
    control_x = center.x - arcHeight * uy;
    
    if (arcHeight < 0) {
        control_y = center.y + abs(arcHeight * ux);
    } else {
        control_y = center.y - abs(arcHeight * ux);
    }
    
    //Ready to start drawing
    ofVec2f prevPoint = ofVec2f(x1 * width, y1 * height);
    ofVec2f control = ofVec2f(control_x * width, control_y * height);
    ofVec2f start = ofVec2f(x1 * width, y1 * height);
    ofVec2f end = ofVec2f(x2 * width, y2 * height);
    
    //Draw Arc
    ofSetLineWidth(thick);
    int division = 128;
    
    float exposed = division * expose;
    for (int i = 0; i <= exposed; i++) {
        float t = float(i) / division;
        ofVec2f tmpPoint = (1-t)*(1-t)*start + 2*(1-t)*t*control + t*t*end;
        ofDrawLine(prevPoint, tmpPoint);
        prevPoint = tmpPoint;
    }
    
}

void wave(float x1, float y1, float x2, float y2, float freq, float amplitude, float phase, float thick) {
    //Culcurate Line status
    ofVec2f start = ofVec2f(x1 * width, y1 * height);
    ofVec2f end = ofVec2f(x2 * width, y2 * height);
    ofVec2f line = end - start;
    
    int length = line.length();
    float angle = line.getNormalized().angle(ofVec2f(1,0));
    
    float division = 1024.0;
    ofSetLineWidth(thick);
    
    //Draw
    ofVec2f currentPointOnLine = ofVec2f(0, 0);
    ofVec2f currentPos = ofVec2f(0, 0);
    ofVec2f previousPos = ofVec2f(0, 0);
    
    for (float i = 0; i <= division; i += 1.0) {
        if (i == 0) {
            //currentPointOnLine = line * i / division + start;
            currentPointOnLine = start;
            previousPos = currentPointOnLine + line.getNormalized().rotate(90) * sin((i/division * PI * 2.0 * freq) + (phase * 2.0 * PI)) * width * amplitude;
        }
        currentPointOnLine = line * i / division + start;
        currentPos = currentPointOnLine + line.getNormalized().rotate(90) * sin((i/division * PI * 2 * freq) + (phase * 2 * PI)) * width * amplitude;
        ofDrawLine(previousPos, currentPos);
        previousPos = currentPos;
    }
    
}

    






















