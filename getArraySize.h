//
//  getArraySize.h
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#ifndef getArraySize_h
#define getArraySize_h

#include <iostream>

template
<
typename TYPE,
std::size_t SIZE
>
std::size_t getArraySize(const TYPE (&)[SIZE])
{
    return SIZE;
}


#endif /* getArraySize_h */
