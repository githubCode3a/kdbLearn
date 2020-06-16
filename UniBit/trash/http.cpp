
// api.somesite.com/apikey=ARG1&command=ARG2
// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o http http.cpp c.o -lpthread; ./http api.somesite.com 80 GET "/apikey=ARG1&command=ARG2"
// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o http http.cpp c.o -lpthread; ./http api.somesite.com 443 GET "/apikey=ARG1&command=ARG2"
// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o http http.cpp c.o -lpthread; ./http api.somesite.com 80 POST / "name=ARG1&value=ARG2" "Content-Type: application/x-www-form-urlencoded"
// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o http http.cpp c.o -lpthread; ./http api.somesite.com 443 POST / "name=ARG1&value=ARG2" "Content-Type: application/x-www-form-urlencoded"
// clear && printf '\e[3J';  g++ -o http http.cpp c.o -lpthread; ./http api.somesite.com 443 GET / "name=ARG1&value=ARG2" "Content-Type: application/x-www-form-urlencoded"
// api.unibit.ai/api/realtimestock/AAPL?size=10&AccessKey=demo
// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o http http.cpp c.o -lpthread; ./http api.unibit.ai 443 GET "/api/realtimestock/AAPL?size=10&AccessKey=demo"

// https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include<iostream>
using namespace std;
#define BUFFER_SIZE 128
void error(const char *msg) { perror(msg); exit(0); }


int main(int argc,char *argv[])
{
    int i;

    /* first where are we going to send it? */
    int portno = atoi(argv[2])>0?atoi(argv[2]):80;
    const char *host = strlen(argv[1])>0?argv[1]:"localhost";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message, response[4096];


    if (argc < 5) { puts("Parameters: <host> <port> <method> <path> [<data> [<headers>]]"); exit(0); }

    /* How big is the message? */
    message_size=1000;//yezheng	
	   
    

    if(!strcmp(argv[3],"GET"))
    {
    	// cout<<"===================="<<argv[3]<<"\n";
        message_size+=strlen("%s %s%s%s HTTP/1.1\r\n");        /* method         */
        message_size+=strlen(argv[3]);                         /* path           */
        message_size+=strlen(argv[4]);                         /* headers        */
        if(argc>5)
            message_size+=strlen(argv[5]);                     /* query string   */
        for(i=6;i<argc;i++)                                    /* headers        */
            message_size+=strlen(argv[i])+strlen("\r\n");
        message_size+=strlen("\r\n");                          /* blank line     */
    }
    // else
    // {
    //     message_size+=strlen("%s %s HTTP/1.1\r\n");
    //     message_size+=strlen(argv[3]);                         /* method         */
    //     message_size+=strlen(argv[4]);                         /* path           */
    //     for(i=6;i<argc;i++)                                    /* headers        */
    //         message_size+=strlen(argv[i])+strlen("\r\n");
    //     if(argc>5)
    //         message_size+=strlen("Content-Length: %d\r\n")+10; /* content length */
    //     message_size+=strlen("\r\n");                          /* blank line     */
    //     if(argc>5)
    //         message_size+=strlen(argv[5]);                     /* body           */
    // }

    /* allocate space for the message */
    message= (char*)malloc(message_size);

    /* fill in the parameters */
    if(!strcmp(argv[3],"GET"))
    {
        if(argc>5)
            sprintf(message,"%s %s%s%s HTTP/1.1\r\n",
                strlen(argv[3])>0?argv[3]:"GET",               /* method         */
                strlen(argv[4])>0?argv[4]:"/",                 /* path           */
                strlen(argv[5])>0?"?":"",                      /* ?              */
                strlen(argv[5])>0?argv[5]:"");                 /* query string   */
        else
            sprintf(message,"%s %s HTTP/1.1\r\n",
                strlen(argv[3])>0?argv[3]:"GET",               /* method         */
                strlen(argv[4])>0?argv[4]:"/");                /* path           */
        for(i=6;i<argc;i++)                                    /* headers        */
            {strcat(message,argv[i]);strcat(message,"\r\n");}
        strcat(message,"\r\n");                                /* blank line     */
    }
    // else
    // {
    //     sprintf(message,"%s %s HTTP/1.1\r\n",
    //         strlen(argv[3])>0?argv[3]:"POST",                  /* method         */
    //         strlen(argv[4])>0?argv[4]:"/");                    /* path           */
    //     for(i=6;i<argc;i++)                                    /* headers        */
    //         {strcat(message,argv[i]);strcat(message,"\r\n");}
    //     if(argc>5)
    //         sprintf(message+strlen(message),"Content-Length: %d\r\n",strlen(argv[5]));
    //     strcat(message,"\r\n");                                /* blank line     */
    //     if(argc>5)
    //         strcat(message,argv[5]);                           /* body           */
    // }

    /* What are we going to send? */
    // message = "GET /api/realtimestock/AAPL?size=10&AccessKey=demo HTTP/1.1\r\nHost: api.unibit.ai\r\nAccept-Language: en, mi\r\n";
    // strcpy(message, "GET /api/realtimestock/AAPL?size=10&AccessKey=demo HTTP/1.1\r\nHost: api.unibit.ai\r\nAccept-Language: en, mi\r\n");
    // strcpy(message, "GET /hello.txt HTTP/1.1\r\nUser-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3\r\nHost: www.example.com\r\nAccept-Language: en, mi\r\n");
    strcpy(message, "GET https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages HTTP/1.1");
    printf("Request:\n%s\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            {break;}
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    char buffer[BUFFER_SIZE];
    received = 0;
    // do {
    //     bytes = read(sockfd,buffer,total-received);
    //     if (bytes < 0)
    //         error("ERROR reading response from socket");
    //     if (bytes == 0)
    // 	{	
    // 		// cout<<"ERROR reading response from socket BYTE IS EMPTY\t\n";
	   //      break;
	   //  }
    //     received+=bytes;
    // } while (received < total);
	bzero(buffer, BUFFER_SIZE);
	cout <<"????\tSTART\t\r\n";
	int res = 1;
    while (res ){
    	res = read(sockfd, buffer, BUFFER_SIZE -1);
    	cout <<res<<"????["<<buffer<< "]\r\n";
    	// fprintf(stderr,"%s", buffer);
    	bzero(buffer, BUFFER_SIZE);
    	strcat(response, buffer );
    }

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);

    free(message);
    return 0;
}

// int main(int argc,char *argv[])
// {
//     int i;

//     /* first where are we going to send it? */
//     int portno = atoi(argv[2])>0?atoi(argv[2]):80;
//     const char *host = strlen(argv[1])>0?argv[1]:"localhost";

//     struct hostent *server;
//     struct sockaddr_in serv_addr;
//     int sockfd, bytes, sent, received, total, message_size;
//     char *message, response[4096];


//     if (argc < 5) { puts("Parameters: <host> <port> <method> <path> [<data> [<headers>]]"); exit(0); }

//     /* How big is the message? */
//     message_size=0;
	   
    

//     if(!strcmp(argv[3],"GET"))
//     {
//     	// cout<<"===================="<<argv[3]<<"\n";
//         message_size+=strlen("%s %s%s%s HTTP/1.1\r\n");        /* method         */
//         message_size+=strlen(argv[3]);                         /* path           */
//         message_size+=strlen(argv[4]);                         /* headers        */
//         if(argc>5)
//             message_size+=strlen(argv[5]);                     /* query string   */
//         for(i=6;i<argc;i++)                                    /* headers        */
//             message_size+=strlen(argv[i])+strlen("\r\n");
//         message_size+=strlen("\r\n");                          /* blank line     */
//     }
//     else
//     {
//         message_size+=strlen("%s %s HTTP/1.1\r\n");
//         message_size+=strlen(argv[3]);                         /* method         */
//         message_size+=strlen(argv[4]);                         /* path           */
//         for(i=6;i<argc;i++)                                    /* headers        */
//             message_size+=strlen(argv[i])+strlen("\r\n");
//         if(argc>5)
//             message_size+=strlen("Content-Length: %d\r\n")+10; /* content length */
//         message_size+=strlen("\r\n");                          /* blank line     */
//         if(argc>5)
//             message_size+=strlen(argv[5]);                     /* body           */
//     }

//     /* allocate space for the message */
//     message= (char*)malloc(message_size);

//     /* fill in the parameters */
//     if(!strcmp(argv[3],"GET"))
//     {
//         if(argc>5)
//             sprintf(message,"%s %s%s%s HTTP/1.1\r\n",
//                 strlen(argv[3])>0?argv[3]:"GET",               /* method         */
//                 strlen(argv[4])>0?argv[4]:"/",                 /* path           */
//                 strlen(argv[5])>0?"?":"",                      /* ?              */
//                 strlen(argv[5])>0?argv[5]:"");                 /* query string   */
//         else
//             sprintf(message,"%s %s HTTP/1.1\r\n",
//                 strlen(argv[3])>0?argv[3]:"GET",               /* method         */
//                 strlen(argv[4])>0?argv[4]:"/");                /* path           */
//         for(i=6;i<argc;i++)                                    /* headers        */
//             {strcat(message,argv[i]);strcat(message,"\r\n");}
//         strcat(message,"\r\n");                                /* blank line     */
//     }
//     else
//     {
//         sprintf(message,"%s %s HTTP/1.1\r\n",
//             strlen(argv[3])>0?argv[3]:"POST",                  /* method         */
//             strlen(argv[4])>0?argv[4]:"/");                    /* path           */
//         for(i=6;i<argc;i++)                                    /* headers        */
//             {strcat(message,argv[i]);strcat(message,"\r\n");}
//         if(argc>5)
//             sprintf(message+strlen(message),"Content-Length: %d\r\n",strlen(argv[5]));
//         strcat(message,"\r\n");                                /* blank line     */
//         if(argc>5)
//             strcat(message,argv[5]);                           /* body           */
//     }

//     /* What are we going to send? */
//     printf("Request:\n%s\n",message);

//     /* create the socket */
//     sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockfd < 0) error("ERROR opening socket");

//     /* lookup the ip address */
//     server = gethostbyname(host);
//     if (server == NULL) error("ERROR, no such host");

//     /* fill in the structure */
//     memset(&serv_addr,0,sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(portno);
//     memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

//     /* connect the socket */
//     if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
//         error("ERROR connecting");

//     /* send the request */
//     total = strlen(message);
//     sent = 0;
//     do {
//         bytes = write(sockfd,message+sent,total-sent);
//         if (bytes < 0)
//             error("ERROR writing message to socket");
//         if (bytes == 0)
//             {break;}
//         sent+=bytes;
//     } while (sent < total);

//     /* receive the response */
//     memset(response,0,sizeof(response));
//     total = sizeof(response)-1;
//     received = 0;
//     do {
//         bytes = read(sockfd,response+received,total-received);
//         if (bytes < 0)
//             error("ERROR reading response from socket");
//         if (bytes == 0)
//     	{	
//     		// cout<<"ERROR reading response from socket BYTE IS EMPTY\t\n";
// 	        break;
// 	    }
//         received+=bytes;
//     } while (received < total);

//     if (received == total)
//         error("ERROR storing complete response from socket");

//     /* close the socket */
//     close(sockfd);

//     /* process response */
//     printf("Response:\n%s\n",response);

//     free(message);
//     return 0;
// }