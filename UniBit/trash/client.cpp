// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o client client.cpp c.o -lpthread; ./client api.unibit.ai 443 GET "/api/realtimestock/AAPL?size=10&AccessKey=demo"
// clear && printf '\e[3J';  g++ -std=c++14 -o client client.cpp c.o -lpthread; 
// ./client https://developer.mozilla.org /en-US/docs/Web/HTTP/Messages

#include "common2.h"

#include <iostream>
#include <zmq.hpp> // sudo apt install libzmq3-dev
#include <nlohmann/json.hpp>
// #include <sstream>
#include <string>
#include <cstdint>
// using namespace std;
// int main(int argc, char* argv[])
int main()
{
    // if (argc != 3)
    // {
    //     std::cerr << "Usage: client <host> <Message>\n";
    //     exit(1);
    // }
    // std::string   argv1(argv[1]), argv2(argv[2]);
    // char myword[] = "Hello"; 
    // char argv1[] ="developer.mozilla.org",//"https://developer.mozilla.org"
    // argv2[] = "/";// argv2[] = "/en-US/docs/Web/HTTP/Messages";
    //------------
    // char argv1[] = "www.example.com";
    // char argv2[] = "/hello.txt";
    //------------
    char argv1[] = "api.unibit.ai",
    argv2[] = "/api/realtimestock/AAPL?size=10&AccessKey=demo";
    std::cout<<"argv1\t"<<argv1<<'\t'<<typeid(argv1).name()<<"\r\n";
    std::cout<<"argv2\t"<<argv2<<'\t'<<typeid(argv2).name()<<"\r\n";
    try
    {
        
        Client  client(argv1);

        if (!client.sendMessage(argv2))
        {
            // std::stringstream message("Failed: sendMessage()\n");
            // message << strerror(errno);
            // throw std::runtime_error(message.str());
            throw std::runtime_error("Failed: sendMessage()\n");
        }

        std::string     buffer;
        if (client.getMessage(buffer))
        {
            std::cout << "Response from server: " << buffer << "\n";
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        throw;
    }
}