#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <WinSock2.h>

const size_t FRAME_LEN = 1024;

class GameClient final {
public:
    GameClient();
    ~GameClient();

    bool connect(std::string ip, uint16_t port);
    std::vector<bool> ping(bool isReady);
    bool sync();
    void input(char c);

    int id;
    bool isWin = false;
    bool isRunning = false;
    bool isBusy;

    std::vector<std::pair<int, int>> snakeBody;
    std::vector<std::pair<int, int>> snakeHead;
    std::vector<int> dir;
    std::pair<int, int> food;

private:
    bool isConnect;
    SOCKET mSocket;
    SOCKADDR_IN addr;
    int addrLen = sizeof(SOCKADDR);

    int playerSize;
};
