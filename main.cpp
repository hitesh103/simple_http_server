// creates an instance of our server and tells it to go!

#include "SimpleServer.hpp"

int main() {
    SimpleServer myServer(8080);
    myServer.start();
    return 0;
}
