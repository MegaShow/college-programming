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

// ��0λ: 0 - Ping, 1 - PingState, 3 - PlayerState, 4 - PlayerOpr
//
// Ping
//   ��1λ: 0 - NotReady, 1 - Ready
//
// PingState
//   ��1λ: 0 - Wait, 1 - Busy
//   ��2λ: ��ǰID
//   ��3λ: �������n
//   ��3+iλ: ��i����ҵ�״̬, 0 - NotWait, 1 - Wait
//
// PlayerState
//   ��1λ: 0 - Running, 1 - End
//   �������: (����Ϊ�������)
//     ��0λ: Dir
//     ��1λ: Len
//     λ������: (����ΪLen)
//       ��0λ: x
//       ��1λ: y
//   ��n-2λ: FoodX
//   ��n-1λ: FoodY
//
// PlayerOpr
//   ��1λ: Left = 0, Right = 1, Top = 2, Bottom = 3
