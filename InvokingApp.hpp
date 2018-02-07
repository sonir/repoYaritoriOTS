//
//  InvokingApp.hpp
//  yaritori
//
//  Created by uozm on 2018/02/06.
//
//

#ifndef InvokingApp_hpp
#define InvokingApp_hpp

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

int invokingApp(string appName);
int exe(string cmd);

//appName should include the its path
//Ex.     invokingApp("/Users/uozm/Documents/boxes/dev_box/of_v0.9.8_osx_release/apps/myApps/yaritoriOTS/bin/data/mi.app");


#endif /* InvokingApp_hpp */
