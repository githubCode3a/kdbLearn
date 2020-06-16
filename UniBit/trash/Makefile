all:    client

.PHONY:         all
.INTERMEDIATE:  %.o

CC          =  $(CXX)
CXXFLAGS    += -Wall -Wextra -Werror -pedantic -std=c++14

client: client.o common2.o

client.o:   client.cpp common2.h
common2.o:   common2.cpp common2.h