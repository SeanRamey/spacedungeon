#include "menu.hpp"
void Menu::clear(){
	buttons.clear();
	images.clear();
	texts.clear();
}
Menu::Menu(Game* game) : GameState(game){

}
Menu::~Menu(){
	clear();
}
