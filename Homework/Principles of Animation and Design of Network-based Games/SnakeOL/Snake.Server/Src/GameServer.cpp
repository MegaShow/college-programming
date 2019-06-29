#include <chrono>
#include <iostream>
#include <WS2tcpip.h>

#include "GameServer.h"

GameServer::GameServer() {
    srand(( unsigned int)time(NULL));
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Fail to load socket library." << std::endl;
        exit(-1);
    }
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket == INVALID_SOCKET) {
        std::cout << "Fail to create socket." << std::endl;
        exit(-1);
    }
    char recvbuf = 1;
    if (setsockopt(mSocket, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(int)) == SOCKET_ERROR) {
        std::cout << "Fail to set socket buffer." << std::endl;
        exit(-1);
    }
    u_long iMode = 1;
    if (ioctlsocket(mSocket, FIONBIO, &iMode) == SOCKET_ERROR) {
        std::cout << "Fail to set BIO socket mode." << std::endl;
        exit(-1);
    }
    food.first = rand() % 10;
    food.second = rand() % 12;
}

GameServer::~GameServer() {
    closesocket(mSocket);
    WSACleanup();
}

void GameServer::serve(uint16_t port) {
    if (!isBind) {
        bindSocket(port);
        isBind = true;
    }
    SOCKADDR_IN addr;
    int addrLen = sizeof(addr);
    fd_set rfd;
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    char buf[FRAME_LEN];
    while (true) {
        auto start = std::chrono::system_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() < sendMs) {
            FD_ZERO(&rfd);
            FD_SET(mSocket, &rfd);
            int code = select(mSocket + 1, &rfd, 0, 0, &timeout);
            if (code < 0) {
                std::cout << "Fail to listen socket." << std::endl;
                exit(-1);
            } else if (code > 0) {
                memset(buf, 0, FRAME_LEN);
                recvfrom(mSocket, buf, FRAME_LEN, 0, (SOCKADDR*) & addr, &addrLen);
                switch (buf[0]) {
                case 0: // Ping
                    sendPingState(addr, buf[1] == 1);
                    break;
                case 4: // PlayerOpr
                    changeSnake(addr, static_cast<Direction>(buf[1]));
                    break;
                }
            }
            Sleep(1);
        }
        if (isRunning) {
            sendPlayerState();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdateTime).count() > updateMs) {
                lastUpdateTime = std::chrono::system_clock::now();
                update();
                if (isWin) {
                    std::cout << "Game End." << std::endl;
                    break;
                }
            }
        }
    }
}

void GameServer::bindSocket(uint16_t port) {
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(mSocket, ( SOCKADDR*) & addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        std::cout << "Fail to bind port " << port << "." << std::endl;
        exit(-1);
    }
    listen(mSocket, 10);
}

void GameServer::sendPingState(SOCKADDR_IN addr, bool isReady) {
    bool flag = false;
    for (auto& p : players) {
        if (p.addr.sin_addr.S_un.S_addr == addr.sin_addr.S_un.S_addr && p.addr.sin_port == addr.sin_port) {
            p.ready = isReady;
            flag = true;
            break;
        }
    }
    if (!flag && !isRunning) {
        Player p;
        p.id = players.size();
        p.addr = addr;
        p.ready = isReady;
        p.dir = static_cast<Direction>(rand() % 3 + 1); // ²»ÄÜÊÇLeft
        do {
            std::pair<int, int> newPos, newPos2;
            newPos.first = rand() % 10;
            newPos.second = rand() % 12;
            newPos2.first = (newPos.first + 10 - 1) % 10;
            newPos2.second = newPos.second;
            bool flag = false;
            for (auto& p2 : players) {
                if (std::find(p2.snakePos.begin(), p2.snakePos.end(), newPos) != p2.snakePos.end()
                    || std::find(p2.snakePos.begin(), p2.snakePos.end(), newPos2) != p2.snakePos.end()
                    || food == newPos
                    || food == newPos2) {
                    flag = true;
                }
            }
            if (!flag) {
                p.snakePos.push_back(newPos);
                p.snakePos.push_back(newPos2);
            }
        } while (flag);
        players.push_back(p);
        char str[20];
        inet_ntop(AF_INET, &addr.sin_addr, str, 19);
        std::cout << "Player " << p.id << " join the room, with address " << str << ":" << addr.sin_port << "." << std::endl;
    }
    flag = false;
    for (auto& p : players) {
        if (!p.ready) {
            flag = true;
        }
    }
    if (!flag) {
        isRunning = true;
    }
    char buf[FRAME_LEN];
    buf[0] = 1; // PingState
    buf[1] = isRunning ? 1 : 0; // Busy or wait
    buf[3] = players.size(); // Player size
    flag = false;
    for (int i = 0; i < players.size(); i++) {
        Player p = players[i];
        if (p.addr.sin_addr.S_un.S_addr == addr.sin_addr.S_un.S_addr && p.addr.sin_port == addr.sin_port) {
            buf[2] = p.id;
            flag = true;
        }
        buf[4 + i] = p.ready;
    }
    if (!flag) {
        buf[2] = 127;
    }
    sendto(mSocket, buf, 4 + players.size(), 0, ( SOCKADDR*) & addr, sizeof(addr));
}

void GameServer::changeSnake(SOCKADDR_IN addr, Direction dir) {
    for (auto& p : players) {
        if (p.addr.sin_addr.S_un.S_addr == addr.sin_addr.S_un.S_addr && p.addr.sin_port == addr.sin_port) {
            p.dir = dir;
        }
    }
}

void GameServer::update() {
    std::cout << "Update players' state." << std::endl;
    bool needGenFood = false;
    for (auto& p : players) {
        if (p.snakePos.size() == 0) {
            continue;
        }
        std::pair<int, int> newPos = p.snakePos.front();
        switch (p.dir) {
        case Left:
            newPos.first = (newPos.first - 1 + 10) % 10;
            break;
        case Right:
            newPos.first = (newPos.first + 1) % 10;
            break;
        case Top:
            newPos.second = (newPos.second - 1 + 12) % 12;
            break;
        case Bottom:
            newPos.second = (newPos.second + 1) % 12;
            break;
        }
        for (auto& p2 : players) {
            if (std::find(p2.snakePos.begin(), p2.snakePos.end(), newPos) != p2.snakePos.end()) {
                p.snakePos.clear();
                break;
            }
        }
        p.snakePos.push_front(newPos);
        if (needGenFood || newPos != food) {
            p.snakePos.pop_back();
        } else {
            needGenFood = true;
        }
    }
    while (needGenFood) {
        food.first = rand() % 10;
        food.second = rand() % 12;
        needGenFood = false;
        for (auto& p : players) {
            if (std::find(p.snakePos.begin(), p.snakePos.end(), food) != p.snakePos.end()) {
                needGenFood = true;
                break;
            }
        }
    }
    int alive = 0;
    for (auto& p : players) {
        if (p.snakePos.size()) {
            alive++;
        }
    }
    isWin = alive == 1 && players.size() > 1;
}

void GameServer::sendPlayerState() {
    // std::cout << "Send players' state." << std::endl;
    char buf[FRAME_LEN];
    buf[0] = 3; // PlayerState
    int len = 1;
    buf[len++] = isWin ? 1 : 0;
    for (auto& p : players) {
        buf[len++] = p.dir;
        buf[len++] = p.snakePos.size();
        for (auto& pos : p.snakePos) {
            buf[len++] = pos.first;
            buf[len++] = pos.second;
        }
    }
    buf[len++] = food.first;
    buf[len++] = food.second;
    for (auto& p : players) {
        sendto(mSocket, buf, len, 0, ( SOCKADDR*) & p.addr, sizeof(SOCKADDR));
    }
}
