#ifndef SERVER_H
#pragma SERVER_H

#include <iostream>
#include <cstring>
#include <cstddef>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

class Server{
    private:
        int PORT;
        int sockfd;
        int newsockfd;
        socklen_t clilen;
        struct sockaddr_in serv_addr;
        struct sockaddr_in cli_addr;
        char buffer[2048];
        int n;
        struct user{
            std::string username;
            std::string password;
        };
        void StartListener();
        void WaitAndAcceptConnection();
        void ParseRequest();
        void Respond(std::string msg);
    public:
        Server();
        Server(int port);
        void StartServer();
};

#endif
