#ifndef JSON2KDB_H
#define JSOn2KDB_H

#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp> 
int json2kdb(std::string s ){
  std::cout<< "=====s\t"<< s<<"\t\n";
  /// kdb
   I handle;  // typedef int  I; // https://code.kx.com/q/wp/capi/
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
//-----------
    // result= k(handle, "2.0+3.0", (K)0);
    // if(isRemoteErr(result)) {
    //     kclose(handle);
    //     return EXIT_FAILURE;
    // }
    // printf("Value returned is %f\n", result->f);

    // r0(result);
	try{
		nlohmann::json j = nlohmann::json::parse("{ \"happy\": true, \"pi\": 3.141 }");

	}catch(...){
		std::cout<<"ERROR nlohmann::json\r\n";
	}
//-----------

    kclose(handle);

    return EXIT_SUCCESS;
    
}

#endif