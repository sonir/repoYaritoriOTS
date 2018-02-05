//
//  SoundTrigger.cpp
//  yaritori
//
//  Created by sonir on 1/20/18.
//
//

#include "SoundTrigger.hpp"


//C Functions
region_e whereAmI(posi_t posi, float width){
    
    
    
    float regionWidth = width/REGION_NUM;
    float here = posi.x / regionWidth;
    
    region_e result = (region_e)(here+1);
    return result;
    
}


sound_t shape2sound(ag_shape_t shape, int ag_id){
    
    sound_t snd;
    
    if ( shape.color>GENRE0 ){
        
        snd.genre = 0; //Electronic
        
    }else if( shape.color>GENRE1 ){
        
        snd.genre = 1; //pop
        
    }else if( shape.color>GENRE2 ){
        
        snd.genre = 2; //voice
        
    }else if( shape.color>GENRE3 ){
        
        snd.genre = 3; //tribe
        
    }else if( shape.color>GENRE4 ){
        
        snd.genre = 4; //jazz
        
    }else if( shape.color<GENRE4 ){
        
        snd.genre = 5; //classic
        
    }
        
    
    //SetSong
    snd.song = ag_id%1000;
    
    return snd;
    
    
}

sound_t ag2sound(ag_t *ag, sound_t *snd){
    

    snd->slice = (int)ag->condition;

    int ival;
    float fval;

    switch(ag->condition){
            
        case CALM:
            ival = 0;
            fval = EF_VAL_CALM;
            break;
            
        case RUN:
            ival = 1;
            fval = EF_VAL_RUN;
            break;
            
        case CHASE:
            ival = 2;
            fval = EF_VAL_CHASE;
            break;
            
        case DMG:
            ival = 3;
            fval = EF_VAL_DMG;
            break;
            
        case DEATH:
            ival = 4;
            fval = EF_VAL_DEATH;
            break;
            
    }
    //Set slice with condition
    snd->slice = ival;
    //Set the efval according to condition
    snd->effect_val = fval;
    //Set SpeakerRegion
    GismoManager& gismo = GismoManager::getInstance();
    snd->region = whereAmI(ag->posi, gismo.width_rate);
    
}

//soundTrigger
void SoundTrigger::trigger(void *args){
    
    
    param_u *params = (param_u *)args;
    
    ofxOscMessage m;
    m.setAddress("/sound/set");
    m.addIntArg(params[0].ival); //Set GenreID
    m.addIntArg(params[1].ival); //set SongID
    m.addIntArg(params[2].ival); //set SliceID
    m.addFloatArg(params[3].fval); //set Effect val
    m.addIntArg(params[4].ival); //set Region Num (0=Main, 1=LEFT, 2=CENTER, 3=RIGHT)
    
    //Send Created Message
    sender.sendMessage(m,false);
    
    
}


