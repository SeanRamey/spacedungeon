#include "game-state.hpp"
#include "game.hpp"

///////////////////////////
GameState::GameState(Game* game) :
view(){
	this->game = game;
}

///////////////////////////
GameState::~GameState(){

}

///////////////////////////
sf::View GameState::getView(){
	return view;
}
