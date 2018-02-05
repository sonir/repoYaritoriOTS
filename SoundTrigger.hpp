//
//  SoundTrigger.hpp
//  yaritori
//
//  Created by sonir on 1/20/18.
//
//

#ifndef SoundTrigger_hpp
#define SoundTrigger_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGismo.h"
#include "ag_shape.h"


#define SOUND_HOST_FOR_TRIGGER "192.168.1.202"
//#define SOUND_HOST_FOR_TRIGGER "localhost"
#define SOUND_PORT_FOR_TRIGGER 56137

//Define for node to agent
/*

 #define GENRE0 25
#define GENRE1 20
#define GENRE2 15
#define GENRE3 10
#define GENRE4 7
#define GENRE5 5
*/


//Yaritori SPEAKER REGION :: (Num Multi Screen)
#define REGION_NUM 3


//Threath to decision genre fron shape
#define GENRE0 0.83
#define GENRE1 0.66
#define GENRE2 0.49
#define GENRE3 0.32
#define GENRE4 0.15


//EffectValue

#define PERFORMANCE_SOUND

#ifndef PERFORMANCE_SOUND
// InstallationMode //
#define EF_VAL_CALM 0.5f
#define EF_VAL_RUN 0.5f
#define EF_VAL_CHASE 0.75f
#define EF_VAL_DMG 0.25f
#define EF_VAL_DEATH 0.0f
#else
// PerformanceMode //
#define EF_VAL_CALM 0.25f//0.1f//0.0f//1.0f
#define EF_VAL_RUN 0.465f//0.25f//0.75f
#define EF_VAL_CHASE 0.68f //0.5f//0.5f
#define EF_VAL_DMG 1.0f //0.75f//0.25f
#define EF_VAL_DEATH 0.0f //1.0f//1.0f

#endif



//SpeakerPosition
typedef enum region_e {REGION_MAIN, REGION_LEFT, REGION_CENTER, REGION_RIGHT} region_e;

//Sound Data
typedef struct sound_t {
    
    int genre = 0;
    int song = 0;
    int slice = 0;
    float effect_val = 0.5f;
    region_e region = REGION_MAIN;
    
} sound_t;

typedef struct sound_unit_t {
    
    sound_t elm;
    int index;
    
}sound_unit_t;


region_e whereAmI(posi_t posi, float width);
sound_t shape2sound(ag_shape_t shape, int ag_id);
sound_t ag2sound(ag_t *ag, sound_t *snd);


class SoundTrigger {
    
    public:
    
        SoundTrigger(){
            
            sender.setup(SOUND_HOST_FOR_TRIGGER , SOUND_PORT_FOR_TRIGGER);
            
            //CreateEvents
            
            //EV :: SimpleSountTriger
            auto f = [&](void *args){ trigger(args); };
            gismo.lambdaAdd("/soundTrg" , f);

            //EV :: SoundTriggerWithAgent
            auto f2 = [&](void *args){
                
                ag_t *tmp = (ag_t *)args;
                ag2sound(tmp, &sounds[tmp->agid]);
                param_u params[4];
                params[0].ival = sounds[tmp->agid].genre;
                params[1].ival = sounds[tmp->agid].song;
                params[2].ival = sounds[tmp->agid].slice;
                params[3].fval = sounds[tmp->agid].effect_val;
                params[4].ival = (int)sounds[tmp->agid].region;
                //Send osc val
                trigger(params);
                
            };
            gismo.lambdaAdd("/soundTriggerWithAgent" , f2);
            
            
            
        }
    
    
        GismoManager& gismo = GismoManager::getInstance();
        ofxOscSender sender;
        sound_t sounds[AG_MAX];
    
        void foo();
        void trigger(void *args);
        //void setSound(int ag_id);

    
};

#endif /* SoundTrigger_hpp */
