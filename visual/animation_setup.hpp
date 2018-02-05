//
//  animation_setup.hpp
//  yaritori
//
//  Created by Hana on 2018/01/19.
//
//

#ifndef animation_setup_h
#define animation_setup_h

/////////////////// GLOBAL ///////////////////
//Default colors
constexpr float BACKGROUND_COLOR_DEFAULT = 1.0;
constexpr float ANIMATION_COLOR_DEFAULT = 0.0;
//Inverted colors
constexpr float BACKGROUND_COLOR_INVERTED = 0.0;
constexpr float ANIMATION_COLOR_INVERTED = 1.0;

/////////////////// AGENT ///////////////////

//Constant Values
constexpr float M_2XPI = M_PI * 2.0;
constexpr float SIZE_FIX = 0.5;

//Modulation on each node
constexpr float STEP_MAX = M_2XPI * 6.0f;
constexpr float STEP_MIN = M_2XPI * 4.0f;

constexpr float TREMOR_RATIO = 0.09f;//180119 MODIFIED BY 137 //0.12f;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;
constexpr float MOV_FIX = 0.04; //0.08; //0.02

//Size modulation
constexpr float SIZE_MOD_STRENGTH = 0.18;
constexpr float SIZE_MOD_FLOOR = 1.0 - SIZE_MOD_STRENGTH;
constexpr float SIZE_MOD_STEP = 0.03;  //0.8;   //0.04

//Tremble configuration
constexpr float TREMBLE_TREMOR_RATIO = 0.09f;//180119 MODIFIED BY 137 //0.12f;
constexpr float TREMBLE_STAY_RATIO = 1.0 - TREMOR_RATIO;
constexpr float TREMBLE_STEP_BOOST = 70.3;


constexpr float TREMBLE_RATIO_CENTER = 0.017;    //Center position jumping
constexpr float TREMBLE_INTERVAL_CENTER = 50;   
constexpr float TREMBLE_EASING_RATIO = 0.33;    //Slow easing

constexpr float TREMBLE_SIZE_MOD_STRENGTH = 0.02;
constexpr float TREMBLE_SIZE_MOD_FLOOR = 1.0 - TREMBLE_SIZE_MOD_STRENGTH;
constexpr float TREMBLE_SIZE_MOD_STEP =  4.73;

//constexpr float dx = 0.0166f;
constexpr float EASING_RATIO = 0.1;

/////////////////// WAVEFORM ///////////////////
constexpr float cycle = 200;   //msec
constexpr float maxR = 1.0;    //Max amplitude
constexpr float minR = 0.03;    //Min amplitude
constexpr int TURN_NUM_MAX = 100;  //num of feature points
constexpr float PEAK = 0.3;  //peak point of wave amplitude
constexpr float WAVE_SIZE_RATIO = 0.5;

/////////////////// Ripple ///////////////////
constexpr float RIPPLE_ALPHA_FIX_BLACK = 0.3;
constexpr float RIPPLE_ALPHA_FIX_WHITE = 0.7;

static constexpr float radius_default = 0.15;

static constexpr float duration_default = 0.5;

static constexpr float lagMin = 0.1;
static constexpr float lagMax = 0.25;

static constexpr float sp_noiseMin = 1.5;
static constexpr float sp_noiseMax = 1.7;

/////////////////// SHAKE ///////////////////
constexpr float SHAKE_DEFAULT_TIME_OUT = 300;   //msec
constexpr float SHAKE_DEFAULT_TIME_STAY = 200;
constexpr float SHAKE_DEFAULT_TIME_IN = 300;


#endif /* animation_setup_h */
