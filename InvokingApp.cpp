//
//  InvokingApp.cpp
//  yaritori
//
//  Created by uozm on 2018/02/06.
//
//

#include "InvokingApp.hpp"

using namespace std;

int invokingApp(string appName){
    
    char cmd[256];
    
    sprintf(cmd, "open %s", appName.c_str());
    system(cmd);
    
    return 0;
    
}


int exe(string cmd){
    
    system(cmd.c_str());
    
}
