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
	mm->game->changeState(1, true);
}

void MainMenu::init(){
	menu.addButton(new UIButton(sf::Vector2f(0, 100), Resources::get(Resources::BUTTON), this, &ButtonCallback));
	menu.getButton(0)->getText().setProperties("data/graphics/Void_2058.ttf", 35, sf::Color::Green);
	menu.getButton(0)->getText().getText().setString("Start?");
	menu.getButton(0)->getText().getText().setOutlineColor(sf::Color::Blue);
	menu.getButton(0)->getText().getText().setOutlineThickness(1.5f);
	menu.addText(new UITextElement(sf::Vector2f(0, -200), "data/graphics/Void_2058.ttf", "Space Dungeon", 100, sf::Color::Green));
	menu.getText(0)->getText().setOutlineColor(sf::Color::Blue);
	menu.getText(0)->getText().setOutlineThickness(5);
	view.setCenter(0, 0);
}


void MainMenu::clear(){
	menu.clear();
}


MainMenu::MainMenu(Game* game)
: GameState(game)
, menu() {

}
