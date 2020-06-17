#ifndef JSON2KDB_H
#define JSOn2KDB_H

#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp> 
#include "common.h"
class KDB{
	private:
	 I handle;  // typedef int  I; // https://code.kx.com/q/wp/capi/
	int handleQuery(char* query){
		K result= k(handle, query, (K)0);
	   if(isRemoteErr(result)) {
	        kclose(handle);
	        std::cout<<"EXIT_FAILURE\t" <<EXIT_FAILURE<<"\r\n";
	        return EXIT_FAILURE;
	    }
	   
	    r0(result);
	    r1(result);
	    kdb::Vector<int>(kK(result->k)[0],size());
	    printf("Value returned is %f\n", result->f);
	   printf("result->i\t%d\n",result->i);
	   printf("result->k\t%d\n",result->k);

	   return EXIT_SUCCESS;

	}
public:
	KDB(){
		
	    I portnumber= 12345;
	    S hostname= "localhost";
	    S usernamePassword= "kdb:pass";
	    

	    handle= khpu(hostname, portnumber,usernamePassword);
	    if(!handleOk(handle))
	        {std::cout<<"EXIT_FAILURE\t" <<EXIT_FAILURE<<"\r\n";}
	    printf("Handle value is %d\n", handle);


	    handleQuery ("2.0+3.0");
	    
// 	"date" : "2020-05-01",
	  //     "volume" : 59350841,
	  //     "high" : 299.0,
	  //     "low" : 285.85,
	  //     "adj_close" : 289.07,
	  //     "close" : 289.07,
	  //     "open" : 286.25
	    ///---------------------
	   
	   handleQuery ("quotes:([]ticker:`symbol$();date:`date$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())");
	   handleQuery ("`:/home/acer/github/kdbLearn/quotes.csv 0:.h.tx[`csv;quotes]");
	   handleQuery("quotes:(\"DSEEE\";enlist\",\")0:`:/home/acer/github/kdbLearn/quotes.csv");
	   handleQuery ("`ticker`date xkey `quotes");
	   handleQuery ("select from quotes");
	   
	    ///----------------------
	}
	
	~KDB(){
		  kclose(handle);
		}

public:
	int json2kdb(std::string s, std::string ticker){
	  // std::cout<< "=====s\t"<< s<<"\t\n";
	  /// kdb
	   
	//-----------
	    // result= k(handle, "2.0+3.0", (K)0);
	    // if(isRemoteErr(result)) {
	    //     kclose(handle);
	    //     return EXIT_FAILURE;
	    // }
	    // printf("Value returned is %f\n", result->f);

	    // r0(result);
	    nlohmann::json j;
		try{
			// j = nlohmann::json::parse("{ \"happy\": true, \"pi\": 3.141 }");
			j = nlohmann::json::parse(s)["result_data"][ticker];
			// https://github.com/nlohmann/json/issues/1561
			std::string query = "`quotes upsert ([s:";// + it["ticker"]+"`"it["date"]\
			+"]";
			for (auto it : j)
			{
	   // 	"date" : "2020-05-01",
	  //     "volume" : 59350841,
	  //     "high" : 299.0,
	  //     "low" : 285.85,
	  //     "adj_close" : 289.07,
	  //     "close" : 289.07,
	  //     "open" : 286.25
				// std::cout << it["date"] << '\t' << it["volume"] << '\t' << it["high"]
				// << '\t' << it["low"]<< '\t' << it["adj_close"]<< '\t' << it["close"] << '\t' << it["open"]
				// << '\n';

			// query+= ticker+""it["date"]+":"+it["volume"]+" "+
			// +it["high"]+" "+
			// +it["low"]+"e;"+
			// {resp.close}e;{resp.close}e)"
			}

		query+=")";

		}catch(...){
			std::cout<<"ERROR nlohmann::json\r\n";
		}

	//-----------

	  
	    return EXIT_SUCCESS;
	    
	}

};
#endif