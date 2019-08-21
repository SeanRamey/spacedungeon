#include "main-menu.hpp"
#include "resources.hpp"

void MainMenu::update(sf::Time frameTime, sf::RenderWindow& window){
	float elapsedTime = sineWaveTimer.getElapsedTime().asSeconds();
	for(int i = 0; i < titleText.size(); i++){
		const static int magnitude = 20;
		menu.getText(i)->setPosition(sf::Vector2f(menu.getText(i)->getPosition().x, -200 + (sin(elapsedTime + i)) * magnitude));
	}
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

	UITextElement* title = new UITextElement(sf::Vector2f(0, -200), "data/graphics/Void_2058.ttf", titleText, 100, sf::Color::Green);
	std::vector<UITextElement*> titleCharacters;
	for(size_t i = 0; i < titleText.size(); i++){
		std::string titleChar = titleText.substr(i, 1);
		UITextElement* titleCharacter = new UITextElement(sf::Vector2f(title->getText().findCharacterPos(i).x + title->getText().getCharacterSize()/2, -200), "data/graphics/Void_2058.ttf", titleChar, 100, sf::Color::Green);
		titleCharacter->getText().setOutlineColor(sf::Color::Blue);
		titleCharacter->getText().setOutlineThickness(5);
		menu.addText(titleCharacter);
	}

	menu.addButton(startButton);
	view.setCenter(0, 0);
}

void MainMenu::clear(){
	menu.clear();
}

MainMenu::MainMenu(Game* game)
: GameState(game)
, menu()
, titleText("Space Dungeon"){
	sf::Clock sineWaveTimer;

}
