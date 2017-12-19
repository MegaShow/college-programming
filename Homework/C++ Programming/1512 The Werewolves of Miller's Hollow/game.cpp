// Written by Matrix
#include "judge.hpp"
#include "player.hpp"
#include <cassert>
#include <iostream>
#include <string>
using std::cin;

void RunAllTests() {
  Judge judge;
  Player players[Judge::kMaxCountOfPlayers];
  std::string name;
  Player::Role role;

  for (int i = 0; i < Judge::kMaxCountOfPlayers; ++i) {
    switch (i) {
      case 0:
      case 1:
      case 2: { role = Player::Villager; break; }
      case 3:
      case 4:
      case 5: { role = Player::Werewolf; break; }
      case 6: { role = Player::Seer; break; }
      case 7: { role = Player::Witch; break; }
      case 8: { role = Player::Hunter; break; }
      default: assert(false);
    }

    cin >> name;
    players[i].init(name, role);
    judge.on(&players[i]);
  }

  int role_index;
  cin >> role_index;
  judge.call(static_cast<Player::Role>(role_index));

}

int main() {
  RunAllTests();
  return 0;
}

/*
Two probable tests:
input0:

Kathy
Julie
Kenneth
Albert
William
Jack
Lisa
Carol
Harold
2

output0:

Calling: Werewolf
Albert: Shh... I am a Werewolf.
William: Shh... I am a Werewolf.
Jack: Shh... I am a Werewolf.

=========================================
input1:

Lisa
Albert
Julie
Harold
Jack
Carol
William
Kenneth
Kathy
1

output1:

Calling: Villager
Lisa: I am the villager!!
Albert: I am the villager!!
Julie: I am the villager!!
Harold: I am the villager!!
Jack: I am the villager!!
Carol: I am the villager!!
William: I am the villager!!
Kenneth: I am the villager!!
Kathy: I am the villager!!

*/
