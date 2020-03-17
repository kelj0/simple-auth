#include "server.h"
#include <cstdlib>

int main(int argc, char** argv){
    if(argc == 1){
        Server s1 = Server();
    }else{
        int port = atoi(argv[1]);
        if(port == 0){
            std::cout << "INVALID PORT NUMBER EXITING..\n";
            return -1;
        }
        Server s2 = Server(port);
    }
    return 0;
}

