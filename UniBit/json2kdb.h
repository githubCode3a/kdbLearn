#ifndef JSON2KDB_H
#define JSOn2KDB_H

#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp> 
#include "common.h"
#include "include/kdb_cpp.h"
#define HOST_ADDR "127.0.0.1"
#define HOST_PORT 12345

#include <boost/algorithm/string.hpp>


class KDB{
	private:
	 I handle;  // typedef int  I; // https://code.kx.com/q/wp/capi/
	 kdb::Connector kcon;
	 std::string filenameQuotes, ticker;
	 char* querySaveQuotes, *queryLoadQuotes;

	// int handleQuery(char* query){
	// 	K result= k(handle, query, (K)0);
	//    if(isRemoteErr(result)) {
	//         kclose(handle);
	//         std::cout<<"EXIT_FAILURE\t" <<EXIT_FAILURE<<"\r\n";
	//         return EXIT_FAILURE;
	//     }
	   
	//     r0(result);
	//     r1(result);
	//     printf("Value returned is %f\n", result->f);
	//    printf("result->i\t%d\n",result->i);
	//    printf("result->k\t%d\n",result->k);

	//    return EXIT_SUCCESS;

	// }
	int string2charStarMalloc(const std::string &qStr){

		
    	char *q  = (char *) malloc(qStr.size()+1);
    	bzero(q, qStr.size()+1);
    	strcpy(q, qStr.c_str());
    	kcon.sync(q);
    	free(q);
    	
    	return 0;

	}

	int getTable(char *querySelect){
		kdb::Result res = kcon.sync(querySelect);
	    kdb::Table tbl = res.get_table();

	    // Read header
	    kdb::Vector<kdb::Type::Symbol> header = tbl.get_header();
	    std::cout << "=======================================\nHeaders: ";
	    int cnt =0;
	    for (auto const &it : header) {
	        std::cout << it << '\t'<<cnt;
	        cnt++;
	    }
	    std::cout << '\n';

	    // Traverse a column
	    kdb::Vector<kdb::Type::Long> column = tbl.get_column<kdb::Type::Long>(0);
	    std::cout << "=======================================\nColumn 0: ";
	    for (auto const &it : column) {
	        std::cout << it << ' ';
	    }
	    std::cout << '\n';

	    // Access cells by rows
	    std::cout << "=======================================\nPrinting a table:\n";
	    std::cout << "|| ";
	    for (auto const &it : header) {
	        std::cout << it << "\t|| ";
	    }
	    std::cout << "tbl.ncol()\t"<<tbl.ncol()<<"\n";
	    for (long long row = 0; row < tbl.nrow(); ++row) {
	        std::cout << "|  ";
	        std::cout<< tbl.get<kdb::Type::Long>(row, 0) << "\t|  ";
	        for (int i=1;i!=tbl.ncol(); i++){
	            std::cout<< tbl.get<kdb::Type::Long>(row, i) << "\t|  ";
	        } 
	        std::cout<<"\n";
	    }
	    return 0;//success
	    
	}

	// int getTable(const std::string &querySelectStr){
	// 	char * querySelect   = (char *) malloc(querySelectStr.size()+1);
 //    	bzero(querySelect, querySelectStr.size()+1);
 //    	strcpy(querySelect, querySelectStr.c_str());
    	

	// 	kdb::Result res = kcon.sync(querySelect);
	// 	free(querySelect);
	//     kdb::Table tbl = res.get_table();

	//     // Read header
	//     kdb::Vector<kdb::Type::Symbol> header = tbl.get_header();
	//     std::cout << "=======================================\nHeaders: ";
	//     for (auto const &it : header) {
	//         std::cout << it << ' ';
	//     }
	//     std::cout << '\n';

	//     // Traverse a column
	//     kdb::Vector<kdb::Type::Long> column = tbl.get_column<kdb::Type::Long>(0);
	//     std::cout << "=======================================\nColumn 0: ";
	//     for (auto const &it : column) {
	//         std::cout << it << ' ';
	//     }
	//     std::cout<<"[END] getTable-------------\r\n";

	//     // Access cells by rows
	//     std::cout << "=======================================\nPrinting a table:\n";
	//     std::cout << "|| ";
	//     for (auto const &it : header) {
	//         std::cout << it << "\t|| ";
	//     }
	//     std::cout << "\n";
	//     for (long long row = 0; row < tbl.nrow(); ++row) {
	//         std::cout << "|  " << tbl.get<kdb::Type::Long>(row, 0) << "\t|  "
	//                   << tbl.get<kdb::Type::Float>(row, 1) << "\t|  "
	//                   << tbl.get<kdb::Type::Symbol>(row, 2) << "\t|\n";
	//     }
	    
	// }
	int connectLoadTickerCSV(){
		 if (FILE *file = fopen(filenameQuotes.c_str(), "r")) { // 
        fclose(file);
        // return true;
    } else {
    	// Create a table
 
		// string2charStarMalloc(ticker+ "quotes:([]date:`date$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())",q);	
		string2charStarMalloc(ticker+ "quotes:([]date:`date$();volume:`real$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())");	
		

        kcon.sync(querySaveQuotes);
    } 
    string2charStarMalloc("`date xkey `"+ticker+"quotes");

	}
	int testCodyFengKdb2(){
	std::cout<<"testCodyFengKdb-------------\r\n";
	// if (!kcon.connect(HOST_ADDR, HOST_PORT))// do not reconnect!!
 //        return -1;
	
    if (false ) {// FILE *file = fopen(filenameQuotes.c_str(), "r")
        // fclose(file);
        // return true;
    } else {
    	// Create a table
 
		// string2charStarMalloc(ticker+ "quotes:([]date:`date$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())",q);	
		string2charStarMalloc(ticker+ "quotes:([]date:`date$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())");	
		// AAPLquotes:([]date:`date$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())
		// trades:([]date:`date$();time:`time$();sym:`symbol$();price:`real$();size:`int$(); cond:`char$())
		std::cout<<"hello-------------\r\n";
		// https://code.kx.com/q/learn/startingkdb/tables/
		// `trades insert (2013.07.01;10:03:54.347;`IBM;20.83e;40000;"N")
		// `trades insert (2013.07.01;10:04:05.827;`MSFT;88.75e;2000;"B")
		// `AAPLquotes upsert (date:2000.01.01;high:0.0e;low:0.0e;adj_close:0.0e;close:0.0e;open:0.0e)
		
		// `AAPLquotes insert (2000.01.01;0.0e;0.0e;0.0e;0.0e;0.0e) #works!!
		string2charStarMalloc("`date xkey `"+ticker+"quotes");	
		// `AAPLquotes upsert (2000.01.01;0.0e;0.0e;0.0e;0.0e;0.0e)
		// `AAPLquotes upsert ([date:2000.01.01]0.0e;0.0e;0.0e;0.0e;0.0e)
		// `AAPLquotes upsert ([2000.01.01]0.0e;0.0e;0.0e;0.0e;0.0e)
		// `AAPLquotes upsert ([date:2000.01.01]high:0.0e;low:0.0e;adj_close:0.0e;close:0.0e;open:0.0e)
		// AAPLquotes upsert ([2000.01.01]high:0.0e;low:0.0e;adj_close:0.0e;close:0.0e;open:0.0e)
		// http://www.timestored.com/kdb-guides/errors/rank
		// 'rank
	    // string2charStarMalloc("`"+ticker+"quotes upsert (2000.01.01;0.0e;0.0e;0.0e;0.0e;0.0e)");

		kcon.sync(queryLoadQuotes);
        kcon.sync(querySaveQuotes);
    } 

    // kcon.sync("tbl_test:([]col1:`first`second`third`first:1.1 2.2 3.3 4.4f;col3:`first`second`third`fourth)");
    // kcon.sync("tbl_test:([]col1:1 2 3 4;1.1 2.2 3.3 4.4f;col3:`first`second`third`fourth)");
    // tbl_test:([]col1:1 2 3 4;col2:1.1 2.2 3.3 4.4f;col3:`first`second`third`fourth)
    // tbl_test:([]date:2020.01.01 2020.01.02 2020.01.03 2020.01.04;col2:1.1 2.2 3.3 4.4f;col3:`first`second`third`fourth)
    // tbl_test:([]date:2020.01.01 2020.01.02;col2:1.1 3.3f;col3:`first`second) // WORKS!!
    // tbl_test:([]date:2020.01.01 2020.01.02;col2:3.3f;col3:`second) // NOT WORK

    // test:([]date:2000.01.01 2000.01.01;high:0.0 0.0f;col3:`first`second) // WORKS!!
    // test:([]date:2000.01.01 2000.01.01;high:0.0 0.0f;low:0.0 0.0f;adj_close:0.0 0.0f;close:0.0 0.0f;open:0.0 0.0f) 
    kcon.sync("test:([]dateTEST:2000.01.01 2000.01.01;high:0.0 0.0f;low:0.0 0.0f;adj_close:0.0 0.0f;close:0.0 0.0f;open:0.0 0.0f) ");
    // kcon.sync("tbl_test:([]date:`2000.01.01:high:0.0e;low:0.0e)");
    kcon.sync(queryLoadQuotes);

	// string2charStarMalloc("`date xkey `"+ticker+"quotes");	// if I set this one, I cannot getTable!!!!!
    
	// {
	// 	char *q;
	// 	string2charStarMalloc(ticker+"quotes upsert([s:`2010-0-0]0.0;0.0;0.0;0.0;0.0)",q);	
 //    	kcon.sync(q);
 //    	free(q);
	// }


	    getTable("select from test");
	    {
	    	std::string querySelectStr = "select from "+ticker+"quotes";
			char * querySelect   = (char *) malloc(querySelectStr.size()+1);
	    	bzero(querySelect, querySelectStr.size()+1);
	    	strcpy(querySelect, querySelectStr.c_str());
	    	getTable(querySelect);
	    	free(querySelect);
	    }
	}
// 	int queryHandleOldVersion(){
// 		// KDB tutorial old fashioned!! // https://code.kx.com/q/interfaces/capiref/
// 	    // I portnumber= HOST_PORT;
// 	    // S hostname= HOST_ADDR;
// 	    // S usernamePassword= "kdb:pass";
	    

// 	    // handle= khpu(hostname, portnumber,usernamePassword);
// 	    // if(!handleOk(handle))
// 	    //     {std::cout<<"EXIT_FAILURE\t" <<EXIT_FAILURE<<"\r\n";}
// 	    // printf("Handle value is %d\n", handle);


// 	    // handleQuery ("2.0+3.0");
	    
// // 	"date" : "2020-05-01",
// 	  //     "volume" : 59350841,
// 	  //     "high" : 299.0,
// 	  //     "low" : 285.85,
// 	  //     "adj_close" : 289.07,
// 	  //     "close" : 289.07,
// 	  //     "open" : 286.25
// 	    ///---------------------

// 	    if (FILE *file = fopen(filenameQuotes.c_str(), "r")) {
// 	        fclose(file);
// 	        // return true;
// 	    } else {
// 	    	// Create a table
// 	    	handleQuery ("quotes:([]ticker:`symbol$();date:`date$();high:`real$();low:`real$();adj_close:`real$();close:`real$();open:`real$())");
// 	    	handleQuery (querySaveQuotes);
	    	
// 	        // return false;
// 	    } 
	
	   
// 	   handleQuery(queryLoadQuotes);
// 	   handleQuery ("`ticker`date xkey `quotes");
// 	   handleQuery ("select from quotes");
// 	}
public:
	KDB(char * ticker_){
		ticker = ticker_;
		filenameQuotes = "/home/acer/github/kdbLearn/quotes/"+ticker+".csv";
		{
			std::string q= "`:" + filenameQuotes +" 0:.h.tx[`csv;"+ticker+"quotes]";
			querySaveQuotes = (char *)malloc(q.size()+1);
			bzero(querySaveQuotes, q.size()+1);
			strcpy(querySaveQuotes, q.c_str());
			// std::cout<<"[KDB()] querySaveQuotes\t"<<querySaveQuotes<<"\r\n";
		}
		{
			std::string q= ticker+"quotes:(\"DSEEE\";enlist\",\")0:`:" +filenameQuotes ;
			queryLoadQuotes = (char *)malloc(q.size()+1);
			bzero(queryLoadQuotes, q.size()+1);
			strcpy(queryLoadQuotes, q.c_str());
			// std::cout<<"[KDB()] queryLoadQuotes\t"<<queryLoadQuotes<<"\r\n";
		}
		if (!kcon.connect(HOST_ADDR, HOST_PORT))
		{std::cout<<"EXIT_FAILURE\t" <<EXIT_FAILURE<<"\r\n";}
        
       handle = kcon.handle();

	   
		// queryHandleOldVersion();

		// testCodyFengKdb();
	   
	    ///----------------------
	}
	
	~KDB(){
		// char q[] = querySaveQuotes.c_str();
		// https://stackoverflow.com/questions/43631415/using-shared-ptr-with-char
		// std::shared_ptr<char> q(new char[querySaveQuotes.size()], std::default_delete<char[]>());
		// std::cout<<"[~KDB()] querySaveQuotes\t"<<querySaveQuotes<<"\r\n";
		  // handleQuery (querySaveQuotes);
		  kcon.sync(querySaveQuotes);
		  free(querySaveQuotes);
		  free(queryLoadQuotes);
		  kclose(handle);
	}

public:
	int json2kdb(std::string s){

		connectLoadTickerCSV();
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
			std::string query = "`"+ticker+"quotes upsert (",//I have to have "`"+
			date = "", volume ="", high= "", low= "",adj_close="",close = "", open="";
		// AAPLquotes upsert([date:2020.05.01]59350841;299.0;0.0;0.0;0.0;0.0) /// NOT WORK
		// AAPLquotes upsert(2020.05.01 ;59350841e ;299.0e ;0.0e ;0.0e ;0.0e ;0.0e )
			// AAPLquotes upsert ([date:2020.05.01 2020.04.30]volume:59350841 37537233e;high:299.0 294.52e;low:285.85 288.36e;adj_close:289.07 293.8e;close:289.07 293.8e;open:286.25 289.96e)
			int cnt =0;
			for (auto it : j)
			{
				cnt++;
				// if (3 == cnt){break;}
	   // 	"date" : "2020-05-01",
	  //     "volume" : 59350841,
	  //     "high" : 299.0,
	  //     "low" : 285.85,
	  //     "adj_close" : 289.07,
	  //     "close" : 289.07,
	  //     "open" : 286.25
			// https://github.com/nlohmann/json/issues/1061
			// std::cout << it["date"] << '\t' << it["volume"] << '\t' << it["high"]
			// << '\t' << it["low"]<< '\t' << it["adj_close"]<< '\t' << it["close"] << '\t' << it["open"]
			// << '\n';
			std::string d = it["date"].dump();
			d = d.substr(1, d.size()-2);

				// https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/

			std::vector<std::string> yearMonthDay;

		 
			boost::split(yearMonthDay, d, [](char c){return c == '-';});
			// std::cout<<"yearMonthDay.size()\t" <<yearMonthDay.size()<<"\r\n";
			d = yearMonthDay[0]+"."+ yearMonthDay[1]+"."+ yearMonthDay[2];
			date= date+d+" ";
			volume= volume+it["volume"].dump()+" ";
			high= high+it["high"].dump()+" ";
			low= low+it["low"].dump()+" ";
			adj_close= adj_close+it["adj_close"].dump()+" ";
			close= close+it["close"].dump()+" ";
			open= open+it["open"].dump()+" ";
			}

		query=query +"[date:"+ date.substr(0,date.size()-1)+"]volume:"+ volume.substr(0,volume.size()-1)+"e;high:"+ high.substr(0,high.size()-1)
		+"e;low:"+ low.substr(0,low.size()-1) +"e;adj_close:"+ adj_close.substr(0,adj_close.size()-1)
		+"e;close:"+ close.substr(0,close.size()-1)
		+"e;open:"+open.substr(0,open.size()-1)+"e)";
		 // std::cout<<"query UPSERT\t"<<query<<"\r\n";
		string2charStarMalloc(query);
		}catch(...){
			std::cout<<	"ERROR nlohmann::json\r\n";
		}

		kcon.sync(querySaveQuotes);

	//-----------

	  
	    return EXIT_SUCCESS;
	    
	}

};
#endif