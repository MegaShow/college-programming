// Written by Matrix
#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <string>

class Player {
public:
  enum Role { Uninitialized, Villager, Werewolf, Seer, Witch, Hunter };

  Player();
  void init(std::string name, Role role);
  ~Player();

  Role role() const;
  void answer() const;
  void pretend() const;

private:
  Role m_role;
  std::string m_name;
};

#endif
