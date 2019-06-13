#ifndef MENU_HPP
#define MENU_HPP
#include <vector>
#include "UI-element.hpp"
#include "UI-button.hpp"
#include "UI-text-element.hpp"
#include "UI-image-element.hpp"
#include "game-state.hpp"
#include "game.hpp"
class Menu : GameState {
	public:
		virtual void update(sf::Time frameTime, sf::RenderWindow& window) = 0;
		virtual void draw(sf::RenderWindow& window)= 0;
		virtual void init() = 0;		
		virtual void clear();

		sf::View getView();
		Menu(Game* game);
		~Menu();

	protected:
		std::vector<UIButton> buttons;
		std::vector<UIImageElement> images;
		std::vector<UITextElement> texts;

		Game* game;
		sf::View view;
};

#endif
