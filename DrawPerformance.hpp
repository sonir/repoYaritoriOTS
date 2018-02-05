//
//  DrawPerformance.hpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#ifndef DrawPerformance_hpp
#define DrawPerformance_hpp



#include <stdio.h>
#include "ofMain.h"
#include "ofxGismo.h"
#include "Performance.hpp"
#include "drawer.hpp"

//FunctionPrototypes
void drawCirclesWithPositions (posi_t *positions, int position_num, float size);
void drawLines (pline_t *lines, int line_num, float size);
void drawBullets(pline_t *lines, Bullet *bullets, int bullets_num);
void drawPerformance(PerformanceManager *pPerformance);

#endif /* DrawPerformance_hpp */
