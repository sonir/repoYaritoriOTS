//
//  Fade.hpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#ifndef Fade_hpp
#define Fade_hpp

#define FADE_FPS 30
#define DEFAULT_DURATION_MS 10000

#include <stdio.h>
#include "ofxGismo.h"


class Fade {
    
    public:
        Fade();
        Fade(int ms);
        void bang();
        float update();
        void reset();
        void set(int ms);
    
        int duration_ms = 0.0f;
        int fps_in_ms;
        int count;
        int  count_end;
        float now_rate;
        bool activated;
    
    private:
        void init(int ms);
    
    
};

#endif /* Fade_hpp */
