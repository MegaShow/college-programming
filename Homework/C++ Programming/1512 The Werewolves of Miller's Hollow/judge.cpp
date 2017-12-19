// Mega Show
// [10] The Werewolves of Miller's Hollow
#include <iostream>
#include "judge.hpp"

Judge::Judge(){
  m_players_count = 0;
}

Judge::~Judge(){

}

void Judge::on(const Player* player){
  m_players[m_players_count++] = player;
}

void Judge::call(Player::Role role){
  switch(role){
     case Player::Villager: std::cout << "Calling: Villager" << std::endl; break;
     case Player::Werewolf: std::cout << "Calling: Werewolf" << std::endl; break;
     case Player::Seer: std::cout << "Calling: Seer" << std::endl; break;
     case Player::Witch: std::cout << "Calling: Witch" << std::endl; break;
     case Player::Hunter: std::cout << "Calling: Hunter" << std::endl; break;
   }
  for(int i = 0; i < m_players_count; i++){
     if(m_players[i]->role() == role)
           m_players[i]->answer();
     else if(role == Player::Villager)
           m_players[i]->pretend();
   }
}
