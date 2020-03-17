
#include "server.h"

void Server::StartListener(){
    // this bind() call will bind socket to the current ip address on port
    if(bind(this->sockfd, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)) < 0){
        std::cout << "ERROR BINDING SOCKET\n";
        exit(-1);
    }

    // listen for incoming connections(max queue backlog is 10)
    listen(this->sockfd,10);
    std::cout << "Listening on port: " << this->PORT << "..\n";
}

void Server::WaitAndAcceptConnection(){
    this->clilen = sizeof(this->cli_addr);
    
    //accept will write connecting client's address info into address structure
    this->newsockfd = accept(this->sockfd, (struct sockaddr *) &this->cli_addr, &clilen);
    if(this->newsockfd < 0){
        std::cout << "ERROR ACCEPTING NEW CONNECTION\n";
        exit(-1);
    }
}

void Server::ParseRequest(){
    std::memset(this->buffer,0,2048);
    this->n = read(this->newsockfd,this->buffer,2048);
    if(this->n<0){
        std::cout << "Nothing in request...\n";
    }
    std::cout << "Parsing request...\n";
}

void Server::Respond(std::string msg){
    send(this->newsockfd, msg.c_str(), msg.length(), 0);
}

void Server::StartServer(){
    std::cout << "Starting server on port: " << this->PORT << "\n";
    
    // create a socket
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;
    setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if(sockfd < 0){
        std::cout << "ERROR OPENING SOCKET! EXITING..\n";
        exit(-1);
    }

    while(1){
        // clear address structure
        std::memset((char *)&this->serv_addr,0,sizeof(this->serv_addr));

        // setup the host addr structure
        this->serv_addr.sin_family = AF_INET;
        // automatically be filled with curret host's ip address
        this->serv_addr.sin_addr.s_addr = INADDR_ANY;

        this->serv_addr.sin_port = htons(this->PORT);

        StartListener();
        WaitAndAcceptConnection();
        ParseRequest();
        Respond("Hello\n");
        close(this->newsockfd);
        break;
    }
    close(this->sockfd);
    std::cout << "Server done..\n";
}

Server::Server(){
    this->PORT = 80;
    StartServer();
}

Server::Server(int port){
    this->PORT = port;
    StartServer();
}

