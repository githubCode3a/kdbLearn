#ifndef COMMON2_H
#define COMMON2_H

#include <string>
#include <cstdint>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

class Socket
{
    protected:
        int socketId;
    public:
        Socket(int socketId);
        ~Socket();
        Socket(Socket&&);
        Socket& operator=(Socket&&);
        Socket(Socket const&)               = delete;
        Socket& operator=(Socket const&)    = delete;

        virtual bool sendMessage(std::string const& buffer);
        bool getMessage(std::string& buffer);
};

class Client: public Socket
{
    public:
        // Client(std::string const& host);
        Client(char * host);
        virtual bool sendMessage(std::string const& buffer) override;
};

class Server: public Socket
{
    public:
        Server();
        Socket accept();
};

#endif