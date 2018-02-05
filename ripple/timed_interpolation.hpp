//
//  timed_interpolation.hpp
//  t_agent
//
//  Created by Hana on 2017/12/12.
//
//

#ifndef timed_interpolation_hpp
#define timed_interpolation_hpp

#include <stdio.h>
#include <chrono>

class TimedInterpolation {
public:
    TimedInterpolation();
    void bang();
    void bang(double _durationMsec);
    void overBang();
    void overBang(double _durationMsec);
    double getd();
    float get();
    void ready();
    void setDuration(double _durationMsec);
    bool waiting;
    
private:

    double waitValue;
    double duration;
    std::chrono::system_clock::time_point start;
    
};

#endif /* timed_interpolation_hpp */
