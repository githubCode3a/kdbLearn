// clear && printf '\e[3J';  g++ -std=c++11 -o UniBit UniBit.cpp c.o -lpthread -lboost_system -lcrypto -lssl -lcpprest; ./UniBit
// http://www.atakansarioglu.com/easy-quick-start-cplusplus-rest-client-example-cpprest-tutorial/



#include <iostream>
#include <cpprest/http_client.h> // sudo apt install libcpprest-dev
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
// #include <cpprest/json.h>
// #include <sstream>
using namespace concurrency::streams; 
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

 
int main() {
  // Create a file stream to write the received file into it.
  auto fileStream = std::make_shared<ostream>();
  
  // Open stream to output file.
  pplx::task<void> requestTask = fstream::open_ostream(U("users.json"))
  
  // Make a GET request.
  .then([=](ostream outFile) {
    *fileStream = outFile;
 
    // Create http_client to send the request.
    http_client client(U("https://api.unibit.ai"));
 
    // Build request URI and start the request.
    // https://reqres.in/api/users/1
    // https://api.unibit.ai/api/realtimestock/AAPL?size=10&AccessKey=demo


    return client.request(methods::GET, uri_builder(U("api")).append_path(U("realtimestock")).append_path(U("AAPL"))
      .append_query(U("size"), U("10"))// https://www.drdobbs.com/cloud/using-the-microsoft-c-rest-sdk/240164544?pgno=2
      .append_query(U("AccessKey"), U("demo")) 
      .to_string());
  })
 
  // Get the response.
  .then([=](http_response response) {
    // Check the status code.
    if (response.status_code() != 200) {
      throw std::runtime_error("Returned " + std::to_string(response.status_code()));
    }
 
    // // Write the response body to file stream.
    // response.body().read_to_end(fileStream->streambuf()).wait();// yezheng: this is the original one


      ///
// https://www.drdobbs.com/cloud/using-the-microsoft-c-rest-sdk/240164544?pgno=2
  // Display the status code that the server returned
        std::wostringstream stream;
      auto bodyStream = response.body();
        concurrency::streams::stringstreambuf sbuffer;//streams::stringstreambuf sbuffer; // error: ‘streams’ has not been declared

        auto& target = sbuffer.collection();
 
        bodyStream.read_to_end(sbuffer).get();
        std::cout<< "=====sbuffer\t"<< sbuffer<<"\t\n";
        stream.str(std::wstring());
        stream << L"Response body: " << target.c_str();
        std::wcout << stream.str(); // std::wcout << stream.str();
        
 
    // Close the file.
    return fileStream->close();


  
  });
 
  // Wait for the concurrent tasks to finish.
  try {
    while (!requestTask.is_done()) { 
    //  std::cout << ".";  //yezheng: comment out!!!
    }
  } catch (const std::exception &e) {
    printf("Error exception:%s\n", e.what());
  }



  return 0;


}