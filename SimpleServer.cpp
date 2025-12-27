// This is where we write the actual instructions for creating the socket and sending the data.

#include "SimpleServer.hpp"
#include <unistd.h>
#include <cstring>
#include <chrono>

SimpleServer::SimpleServer(int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);// first create the socket

    address.sin_family = AF_INET; // then define the address and port
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));//then Bind the socket to the port
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

    auto start_time = std::chrono::high_resolution_clock::now();

    char buffer[30000] = {0};
    long bytes_read = read(client_socket, buffer, 30000);

    if (bytes_read == -1) {
        std::cerr << "Error reading from client socket" << std::endl;
        close(client_socket);
        return;
    }

    std::cout << "--- RAW REQUEST START ---" << std::endl;
    std::cout << "Bytes received: " << bytes_read << std::endl;
    std::cout << buffer << std::endl;
    std::cout << "--- RAW REQUEST END ---" << std::endl;

    // SIMULATE LAG: Make the browser wait 10 seconds
    std::cout << "Client connected. SIMULATING LAG..." << std::endl;
    sleep(10);

    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Everything's fine here!</h1>";
    // \n\n - after this is actual website content
    send(client_socket, response.c_str(), response.length(), 0);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Request processed in " << duration.count() << " ms" << std::endl;

    close(client_socket);
}
