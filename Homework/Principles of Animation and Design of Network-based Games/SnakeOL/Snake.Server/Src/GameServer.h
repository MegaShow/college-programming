#pragma once
#include <chrono>
#include <cstdint>
#include <list>
#include <vector>
#include <WinSock2.h>

const size_t FRAME_LEN = 1024;

enum Direction {
    Left = 0, Right = 1, Top = 2, Bottom = 3
};

struct Player {
    int id;
    bool ready = false;
    std::list<std::pair<int, int>> snakePos;
    Direction dir;
    SOCKADDR_IN addr;
};

class GameServer final {
public:
    GameServer();
    ~GameServer();

    void serve(uint16_t port);

private:
    void bindSocket(uint16_t port);

    void sendPingState(SOCKADDR_IN addr, bool isReady);
    void changeSnake(SOCKADDR_IN addr, Direction dir);
    void update();
    void sendPlayerState();

    bool isBind = false;
    SOCKET mSocket;

    std::vector<Player> players;
    std::pair<int, int> food;
    bool isRunning = false;
    bool isWin = false;

    const long long sendMs = 100;
    const long long updateMs = 800;
    std::chrono::system_clock::time_point lastUpdateTime;
};

// 第0位: 0 - Ping, 1 - PingState, 3 - PlayerState, 4 - PlayerOpr
//
// Ping
//   第1位: 0 - NotReady, 1 - Ready
//
// PingState
//   第1位: 0 - Wait, 1 - Busy
//   第2位: 当前ID
//   第3位: 玩家数量n
//   第3+i位: 第i个玩家的状态, 0 - NotWait, 1 - Wait
//
// PlayerState
//   第1位: 0 - Running, 1 - End
//   玩家数组: (长度为玩家数量)
//     第0位: Dir
//     第1位: Len
//     位置数组: (长度为Len)
//       第0位: x
//       第1位: y
//   第n-2位: FoodX
//   第n-1位: FoodY
//
// PlayerOpr
//   第1位: Left = 0, Right = 1, Top = 2, Bottom = 3
