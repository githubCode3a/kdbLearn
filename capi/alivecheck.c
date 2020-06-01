// https://code.kx.com/q/wp/capi/
// clear && printf '\e[3J';  gcc -DKXVER=3 -o alivecheck alivecheck.c c.o -lpthread
//-----------------
// The c.o header file is required for compilation.
// https://code.kx.com/q/interfaces/c-client-for-q/
// https://github.com/KxSystems/kdb/blob/master/l64/c.o


/* Filename: alivecheck.c */
#include "common.h"

int main() {
    I handle;
    I portnumber= 12345;
    S hostname= "localhost";
    S usernamePassword= "kdb:pass";
    K result;

    handle= khpu(hostname, portnumber,usernamePassword);
    if(!handleOk(handle))
        return EXIT_FAILURE;
    printf("Handle value is %d\n", handle);
    result= k(handle, "2.0+3.0", (K)0);
    if(isRemoteErr(result)) {
        kclose(handle);
        return EXIT_FAILURE;
    }
    printf("Value returned is %f\n", result->f);

    r0(result);
    kclose(handle);
    return EXIT_SUCCESS;
}
