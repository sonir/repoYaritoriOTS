//
//  Csv2Scenes.hpp
//  SonilabMediaController
//
//  Created by sonir on 7/22/16.
//
//

#ifndef Csv2Scenes_hpp
#define Csv2Scenes_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "ofMain.h"
#include "ag_shape.h"
#include "ofxGismo.h"


class Csv2Buffers{
    
    public:
    Csv2Buffers();
    void createAgents();
    void test();
    string nullCheck(string word);

    
    string currentCode;
    bool isReady;
  
    
};

#endif /* Csv2Scenes_hpp */
