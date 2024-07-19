#include "player.h"
#include <iostream>

Player::Player(std::string_view Game) : game(new std::string{Game}){}

Player::Player(const Person& p, std::string_view Game):
    game(new std::string{Game}){
        first_name = new std::string{*p.get_first()};
        last_name = new std::string{*p.get_last()};
    }

Player::~Player(){
    delete game;
}

std::ostream& operator<<(std::ostream& output, const Player& p){
    output << "Player-{name: \"" << (*(p.first_name)) + " " + (*(p.last_name))
    << "\", game: \"" << *(p.game) << '}';
    return output;
}