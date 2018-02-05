//
//  osc2shape.hpp
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#ifndef osc2shape_hpp
#define osc2shape_hpp

#include <stdio.h>
#include "VSyn.hpp"


//Function prototypes

void toMute(shapeContainer *elm, bool flg);

void toCircle(shapeContainer *elm, int uid, float x, float y, float size, int fill);

void toTriangle(shapeContainer *elm, int uid, float x, float y, float size, float angle, int fill);

void toSquare(shapeContainer *elm, int uid, float x, float y, float size, float angle, int fill);

void toRect(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float angle, int fill);

void toLine(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float thick);

void toArc(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float height, float expose, float thick);

void toWave(shapeContainer *elm, int uid, float x1, float y1, float x2, float y2, float freq, float amp, float phase, float thick);

#endif /* osc2shape_hpp */
