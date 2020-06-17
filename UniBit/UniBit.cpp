// clear && printf '\e[3J'; rm UniBit; g++ -DKXVER=3 -o -std=c++11 -o UniBit UniBit.cpp c.o -lpthread -lboost_system -lcrypto -lssl -lcpprest; ./UniBit
// http://www.atakansarioglu.com/easy-quick-start-cplusplus-rest-client-example-cpprest-tutorial/




#include <iostream>
#include <cpprest/http_client.h> // sudo apt install libcpprest-dev
#include <cpprest/filestream.h>
#include <cpprest/uri.h>

#include "json2kdb.h"
// #include <cpprest/json.h>
// #include <sstream>
using namespace concurrency::streams; 
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
//   // Create a file stream to write the received file into it.
//   auto fileStream = std::make_shared<ostream>();
  
//   // Open stream to output file.
//   pplx::task<void> requestTask = fstream::open_ostream(U("users.json"))
  
//   // Make a GET request.
//   .then([=](ostream outFile) {
//     *fileStream = outFile;// 
//     // https://api.unibit.ai/v2/company/coreFinancials?tickers=ticker list&interval=A, Q or TTM&statement=see possible options&startDate=YYYY-MM-DD&endDate=YYYY-MM-DD&selectedFields=field list&dataType=json or csv&accessKey=your ke
 
//     // Create http_client to send the request.
//     http_client client(U("https://api.unibit.ai"));
//  // https://api.unibit.ai/v2/stock/historical?tickers=AAPL&interval=1&startDate=2020-01-01&endDate=2020-05-01&dataType=json&accessKey=JApS-XgN6FCqejbOq9X3dSBFiHj83-FM

//     // Build request URI and start the request.
//     // https://reqres.in/api/users/1
//     // https://api.unibit.ai/api/realtimestock/AAPL?size=10&AccessKey=demo

//     std::string mess = uri_builder(U("v2")).append_path(U("stock")).append_path(U("historical"))
//       .append_query(U("tickers"), U("AAPL"))// https://www.drdobbs.com/cloud/using-the-microsoft-c-rest-sdk/240164544?pgno=2
//       .append_query(U("interval"), U("1")) 
//       .append_query(U("startDate"), U("2020-01-01")) 
//       .append_query(U("endDate"), U("2020-05-01")) 
//       .append_query(U("dataType"), U("json")) 
//       .append_query(U("accessKey"), U("JApS-XgN6FCqejbOq9X3dSBFiHj83-FM")) 
//       .to_string();
//     std::cout<<"mess\t" <<mess<< '\n';
//     return client.request(methods::GET, mess);
//   })
 
//   // Get the response.
//   .then([=](http_response response) {
//     // Check the status code.
//     if (response.status_code() != 200) {
//       throw std::runtime_error("Returned " + std::to_string(response.status_code()));
//     }
 
//     // // Write the response body to file stream.
//     // response.body().read_to_end(fileStream->streambuf()).wait();// yezheng: this is the original one


//       ///
// // https://www.drdobbs.com/cloud/using-the-microsoft-c-rest-sdk/240164544?pgno=2
//   // Display the status code that the server returned
//         std::wostringstream stream;
//       auto bodyStream = response.body();
//         concurrency::streams::stringstreambuf sbuffer;//streams::stringstreambuf sbuffer; // error: ‘streams’ has not been declared

//         auto& target = sbuffer.collection();
 
//         bodyStream.read_to_end(sbuffer).get();
//         // std::cout<< "=====sbuffer\t"<< sbuffer<<"\t\n";
//         stream.str(std::wstring());
//         // std::cout<<"=========target.c_str()\t"<<target.c_str()<<"\r\n";
//         // stream << L"Response body: " << target.c_str();
//         std::wcout << stream.str(); // std::wcout << stream.str();
//         json2kdb(target.c_str());
 
//     // Close the file.
//     return fileStream->close();


  
//   });
 
//   // Wait for the concurrent tasks to finish.
//   try {
//     while (!requestTask.is_done()) { 
//     //  std::cout << ".";  //yezheng: comment out!!!
//     }
//   } catch (const std::exception &e) {
//     printf("Error exception:%s\n", e.what());
//   }


// --- save UniBit credit
// https://stackoverflow.com/questions/20902945/reading-a-string-from-file-c
std::string item_name, buffer;
std::ifstream nameFileout;

nameFileout.open("users.json");
while (std::getline(nameFileout, buffer))
{item_name+=buffer;
    // std::cout << item_name;
}
KDB kdb;
kdb.json2kdb(item_name, "AAPL");
nameFileout.close();



  return 0;


}