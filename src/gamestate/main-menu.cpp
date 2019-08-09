#include "main-menu.hpp"
#include "resources.hpp"

void MainMenu::update(sf::Time frameTime, sf::RenderWindow& window){
	menu.update(frameTime, window);
}

void MainMenu::draw(sf::RenderWindow& window){
	window.setView(view);
	menu.draw(window);
}

void MainMenu::ButtonCallback(MainMenu* mm){
	mm->game->changeState(1, false);
}

void MainMenu::init(){
	menu.clear();
	menu.addButton(new UIButton(sf::Vector2f(0, 0), Resources::get(Resources::BUTTON), this, &ButtonCallback));
	menu.getButton(0)->setProperties(35, sf::Color::Blue, "data/graphics/Void_2058.ttf");
	menu.getButton(0)->setText("Restart?");
	view.setCenter(0, 0);
}


void MainMenu::clear(){
	menu.clear();
}


MainMenu::MainMenu(Game* game)
: GameState(game)
, menu() {

}
