// Written by Matrix
#ifndef JUDGE_HPP_
#define JUDGE_HPP_
#include "player.hpp"

class Judge {
public:
  static const int kMaxCountOfPlayers = 9;

  Judge();
  ~Judge();

  void on(const Player* player);
  void call(Player::Role role);

private:
  const Player* m_players[kMaxCountOfPlayers];
  int m_players_count;
};

#endif
