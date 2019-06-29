#include <iostream>

#include "GameServer.h"

int main() {
    GameServer server;
    std::cout << "Listen at port " << 2333 << "." << std::endl;
    server.serve(2333);
}
