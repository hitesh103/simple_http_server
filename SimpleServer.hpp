// the blueprint
// This file tells the computer what our server looks like and what it can do, without getting into the messy details yet.

#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class SimpleServer {
private:
    int server_fd;
    struct sockaddr_in address;

public:
    SimpleServer(int port);

    void start();

    void handle_connection(int client_socket);
};

#endif
