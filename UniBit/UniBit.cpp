// clear && printf '\e[3J'; rm UniBit; g++ -DKXVER=3 -o -std=c++11 -o UniBit include/internal/*.cpp UniBit.cpp c.o -lpthread -lboost_system -lcrypto -lssl -lcpprest; ./UniBit
// http://www.atakansarioglu.com/easy-quick-start-cplusplus-rest-client-example-cpprest-tutorial/

//***C++11 Style:***
#include <chrono>




#include <iostream>
#include <cpprest/http_client.h> // sudo apt install libcpprest-dev
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include "UniBitapi.h"
#include "json2kdb.h"

// #include <cpprest/json.h>
// #include <sstream>
#include<vector>
int main() {

  std::vector<std::string> tickers, failedTickers;
  std::string buffer;
  std::ifstream infile;
  infile.open("/home/acer/github/kdbLearn/companylist.csv");

  std::getline(infile, buffer);
  std::cout<<"first line/header\t"<<buffer<<"\r\n";
  while (std::getline(infile, buffer)) {
    // http://www.cplusplus.com/reference/string/string/find/
    std::size_t idx = buffer.find(',');
    std::string t = buffer.substr(1,idx-2);
tickers.push_back(t);
    // std::cout<<t<<"\r\n";
  }
  infile.close();
// return 0;
  int done = 0;
  // http://www.cplusplus.com/reference/algorithm/sort/
  std::sort(tickers.begin(),tickers.end());
  // https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time 
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  std::vector<std::string>::iterator it = tickers.begin();
  for(; it != tickers.end(); ++it) {
    if( 0== (*it).compare(std::string("CAPR") )){
      begin = std::chrono::steady_clock::now();
      done++; 
      it++;
      break;
    }
    done++; 
    
    /* std::cout << *it; ... */
  }

  for (; it != tickers.end(); ++it){
    std::string tmp = (*it);
    try{
    char *tkr;
    tkr = (char *)malloc(tmp.size()+1);
    bzero(tkr, tmp.size()+1);
    strcpy(tkr, tmp.c_str());
    UniBitapi api(tkr);// "AAPL"
    // --- save UniBit credit
    // https://stackoverflow.com/questions/20902945/reading-a-string-from-file-c
    std::string item_name = api.getJsonStr();
    
    KDB kdb(tkr);//"AAPL"
    free(tkr);
    kdb.json2kdb(item_name);
    done++;
    std::cout<< "==========Done\t"<<tmp<<"\t"<<done<<"/"<<tickers.size()<<"\r\n";
  }catch(...){
    std::cout<< "==========FAIL\t"<<tmp<<"\t"<<done<<"/"<<tickers.size()<<"\r\n";
    failedTickers.push_back(tmp);
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;



  }
  return 0;

// READ FROM users.json -- temporary test!!
  // if (false){
  //     std::string buffer;
  //     std::ifstream nameFileout;
  
  //     nameFileout.open("users.json");
  //     while (std::getline(nameFileout, buffer))
  //     {item_name+=buffer;
  //         // std::cout << item_name;
  //     }
  //     nameFileout.close();
  //   }
}