// This is where we write the actual instructions for creating the socket and sending the data.

#include "SimpleServer.hpp"
#include <unistd.h>
#include <cstring>

SimpleServer::SimpleServer(int port) {
    // first create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // then define the address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // then Bind the socket to the port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // listen for incoming connections
    listen(server_fd, 10); // max 10 connections in queue waiting to be accepted
}

void SimpleServer::start() {
    std::cout << "Server is running..." << std::endl;
    while (true) {
        int addrlen = sizeof(address);
        // wait and accept a new connection
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        handle_connection(client_socket);
    }
}

void SimpleServer::handle_connection(int client_socket) {
    // Read what the browser asked for
    char buffer[30000] = {0};
    read(client_socket, buffer, 30000);
    std::cout << "Request received:\n" << buffer << std::endl;

    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Everything's fine here!</h1>";
    send(client_socket, response.c_str(), response.length(), 0);

    // Hang up
    close(client_socket);
}
