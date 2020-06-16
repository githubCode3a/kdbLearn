all:    client server

.PHONY:         all
.INTERMEDIATE:  %.o

CC          =  $(CXX)
CXXFLAGS    += -Wall -Wextra -Werror -pedantic -std=c++14

client: client.o common.o
server: server.o common.o

server.o:   server.cpp common.h
client.o:   client.cpp common.h
common.o:   common.cpp common.h