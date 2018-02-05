//
//  cam_func.hpp
//  vSyn
//
//  Created by sonir on 9/15/17.
//
//

#ifndef cam_func_h
#define cam_func_h
#define FIXED_Z 0.65

#define POV_INIT_X -0.5
#define POV_INIT_Y -0.375
#define POV_INIT_Z 0.65

#define LOOK_INIT_X -0.5
#define LOOK_INIT_Y -0.375
#define LOOK_INIT_Z -1.0


#include "ofMain.h"

//ofVec3f initCamPosition (int w, int h);
//ofVec3f convertToPixels (ofVec3f org, int w, int h);
//
//
//ofVec3f initCamPosition (int w, int h){
//    
//    ofVec3f result;
//    
//    result.x = ( POV_INIT_X * w * (-1) );
//    result.y = POV_INIT_Y * h;
//    result.z = POV_INIT_Z * FIXED_Z;
//    
//    return result;
//    
//    
//}
//
//
//ofVec3f convertToPixels (ofVec3f org, int w, int h){
//    
//    ofVec3f result;
//    
//    result.x = ( org.x * w * (-1) );
//    result.y = org.y * h;
//    result.z = org.z * FIXED_Z;
//    
//    return result;
//    
//}

#endif /* cam_func_h */
