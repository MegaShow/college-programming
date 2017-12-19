// Mega Show
// [10] The Werewolves of Miller's Hollow
#include <iostream>
#include "player.hpp"

Player::Player(){
  m_role = Uninitialized;
}

void Player::init(std::string name, Role role){
  m_name = name;
  m_role = role;
}

Player::~Player(){

}

Player::Role Player::role() const{
  return m_role;
}

void Player::answer() const{
  switch(m_role){
     case Werewolf: std::cout << m_name << ": Shh... I am a Werewolf." << std::endl; break;
     case Witch: std::cout << m_name << ": Shh... I am a Witch." << std::endl; break;
     case Seer: std::cout << m_name << ": Shh... I am a Seer." << std::endl; break;
     case Hunter: std::cout << m_name << ": Shh... I am a Hunter." << std::endl; break;
     case Villager: std::cout << m_name << ": I am the villager!!" << std::endl; break;
   }
}

void Player::pretend() const{
  std::cout << m_name << ": I am the villager!!" << std::endl;
}
