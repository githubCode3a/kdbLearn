// https://code.kx.com/q/wp/capi/
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include <k.h>
//yezheng
#include"k.h"

// /* common.h */

I isRemoteErr(K x) { // typedef int  I; // https://code.kx.com/q/wp/capi/
    if(!x) {
        fprintf(stderr, "Network error: %s\n", strerror(errno));
        return 1;
    } else if(-128 == xt) {
        fprintf(stderr, "Error message returned : %s\\n", x->s); 
        r0(x);
        return 1;
    }
    return 0;
}


I handleOk(I handle)
{
    if(handle > 0)
        return 1;
    if(handle == 0)
        fprintf(stderr, "Authentication error %d\n", handle);
    else if(handle == -1)
        fprintf(stderr, "Connection error %d\n", handle);
    else if(handle == -2)
        fprintf(stderr, "Timeout error %d\n", handle);
    return 0;
}


#endif