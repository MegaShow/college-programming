#include <iostream>
#include <vector>
#include <WS2tcpip.h>

#include "GameClient.h"

GameClient::GameClient() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Fail to load socket library." << std::endl;
        exit(-1);
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        std::cout << "Fail to load socket library." << std::endl;
        WSACleanup();
        exit(-1);
    }
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket == INVALID_SOCKET) {
        std::cout << "Fail to create socket." << std::endl;
        exit(-1);
    }
}

GameClient::~GameClient() {
    closesocket(mSocket);
    WSACleanup();
}

bool GameClient::connect(std::string ip, uint16_t port) {
    if (isConnect) {
        return false;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr);
    if (!ping(false).size()) {
        return false;
    }
    isConnect = true;
    return true;
}

std::vector<bool> GameClient::ping(bool isReady) {
    char buf[FRAME_LEN];
    buf[0] = 0; // Ping
    buf[1] = isReady ? 1 : 0;
    if (sendto(mSocket, buf, 2, 0, ( SOCKADDR*) & addr, addrLen) == SOCKET_ERROR) {
        return std::vector<bool>();
    }
    int len = recvfrom(mSocket, buf, FRAME_LEN, 0, ( SOCKADDR*) & addr, &addrLen);
    if (len == SOCKET_ERROR) {
        return std::vector<bool>();
    }
    isBusy = buf[1] == 1;
    id = buf[2];
    playerSize = buf[3];
    if (id < playerSize) {
        isRunning = isBusy;
    }
    std::vector<bool> ready(playerSize);
    for (int i = 0; i < playerSize; i++) {
        ready[i] = buf[4 + i];
    }
    return ready;
}

bool GameClient::sync() {
    char buf[FRAME_LEN];
    int len = recvfrom(mSocket, buf, FRAME_LEN, 0, ( SOCKADDR*) & addr, &addrLen);
    if (len == SOCKET_ERROR) {
        return false;
    }
    if (buf[0] == 3) {
        int index = 1;
        isWin = buf[index++];
        snakeHead.clear();
        snakeBody.clear();
        dir.clear();
        for (int i = 0; i < playerSize; i++) {
            dir.push_back(buf[index++]);
            int len = buf[index++];
            if (len != 0) {
                snakeHead.push_back(std::make_pair(buf[index], buf[index + 1]));
                index += 2;
                for (int j = 1; j < len; j++) {
                    snakeBody.push_back(std::make_pair(buf[index], buf[index + 1]));
                    index += 2;
                }
            } else {
                dir.pop_back();
            }
        }
        food.first = buf[index++];
        food.second = buf[index++];
    }
    return true;
}

void GameClient::input(char c) {
    char buf[FRAME_LEN];
    buf[0] = 4; // PlayerOpr
    buf[1] = c;
    sendto(mSocket, buf, 2, 0, ( SOCKADDR*) & addr, sizeof(SOCKADDR));
}
