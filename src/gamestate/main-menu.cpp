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
	UIButton* startButton = new UIButton(sf::Vector2f(0, 100), Resources::get(Resources::BUTTON), this, &ButtonCallback);
	startButton->getText().setProperties("data/graphics/Void_2058.ttf", 35, sf::Color::Green);
	startButton->getText().getText().setString("Start?");
	startButton->getText().getText().setOutlineColor(sf::Color::Blue);
	startButton->getText().getText().setOutlineThickness(1.5f);

	UITextElement* title = new UITextElement(sf::Vector2f(0, -200), "data/graphics/Void_2058.ttf", "Space Dungeon", 100, sf::Color::Green);
	title->getText().setOutlineColor(sf::Color::Blue);
	title->getText().setOutlineThickness(5);

	menu.addText(title);	
	menu.addButton(startButton);
	view.setCenter(0, 0);
}

void MainMenu::clear(){
	menu.clear();
}

MainMenu::MainMenu(Game* game)
: GameState(game)
, menu() {

}
