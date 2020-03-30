#include "main-menu.hpp"
#include "resources.hpp"
#include "level.hpp"

///////////////////////////
MainMenu::MainMenu(Game* game)
: GameState(game)
, menu() {

}

///////////////////////////
MainMenu::~MainMenu() {

}

///////////////////////////
void MainMenu::init(){
	menu.clear();
	menu.addButton(new UIButton(sf::Vector2f(0, 0), Resources::getTexture(Resources::TextureID::BUTTON), this, &ButtonCallback));
	menu.getButton(0)->setProperties(35, sf::Color::Blue, "data/graphics/Void_2058.ttf");
	menu.getButton(0)->setText("Restart?");
	view.setCenter(0, 0);
}

///////////////////////////
void MainMenu::update(sf::Time frameTime){
	menu.update(frameTime);
}

///////////////////////////
void MainMenu::draw(sf::RenderWindow& window){
	window.setView(view);
	menu.draw(window);
}

///////////////////////////
void MainMenu::ButtonCallback(MainMenu* mm){
	std::shared_ptr<Level> level = std::make_shared<Level>(mm->game, "data/levels/test-map.map", "data/levels/test-map.dat", "data/graphics/tileset-2-wall.png", "data/graphics/tileset-2-floor.png", 32);
	mm->game->pushState(level);
}

///////////////////////////
void MainMenu::clear(){
	menu.clear();
}
