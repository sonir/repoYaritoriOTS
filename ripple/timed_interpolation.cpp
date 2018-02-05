//
//  timed_interpolation.cpp
//  t_agent
//
//  Created by Hana on 2017/12/12.
//
//

#include "timed_interpolation.hpp"

using namespace std::chrono;

TimedInterpolation::TimedInterpolation() {
    waiting = true;
    waitValue = 0.0;
}

void TimedInterpolation::setDuration(double _durationMsec) {
    duration = _durationMsec;
    waitValue = 0.0;
    waiting = true;
}

void TimedInterpolation::bang() {
    if (waiting) {
        waiting = false;
        waitValue = 1.0;
        start = system_clock::now();
    }
}

void TimedInterpolation::ready() {
    waiting = true;
    waitValue = 0.0;
}

void TimedInterpolation::bang(double _durationMsec) {
    if (waiting) {
        duration = _durationMsec;
        waiting = false;
        start = system_clock::now();
    }
}

void TimedInterpolation::overBang() {
    this->ready();
    this->bang();
}

void TimedInterpolation::overBang(double _durationMsec) {
    duration = _durationMsec;
    waiting = false;
    start = system_clock::now();
}

double TimedInterpolation::getd() {
    double result = 0.0;
    if (waiting) {
        result = waitValue;
    } else {
        system_clock::time_point now = system_clock::now();
        
        double elapsed = duration_cast<milliseconds>(now-start).count();
        result = elapsed / duration;
        if (1.0 < result) {
            result = 1.0;
            waitValue = result;
            waiting = true;
        }
    }
    
    return result;
}


float TimedInterpolation::get() {
    double result = 0.0;
    if (waiting) {
        result = waitValue;
    } else {
        system_clock::time_point now = system_clock::now();
        
        float elapsed = duration_cast<milliseconds>(now-start).count();
        result = elapsed / duration;
        if (1.0 < result) {
            result = 1.0;
            waitValue = result;
            waiting = true;
        }
    }
    
    return result;
}

