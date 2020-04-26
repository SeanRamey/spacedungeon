#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP
#include "ui-element.hpp"
#include "game-state.hpp"

class MainMenu;
class UIButton : public UIElement {
	private:
		sf::Text text;
		sf::Font* font;
		GameState* parent;
		void(*callback)(MainMenu*);

	public:
		UIButton(sf::Vector2f position, sf::Texture* texture, GameState* parent, void(*callback)(MainMenu*));
		~UIButton();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(); // setting text to center of sprite
		void setSize(sf::Vector2u size);
		void setProperties(sf::Font* font, sf::Vector2f position = sf::Vector2f(0, 0), unsigned int fontSize = 32, sf::Color color = sf::Color::White);
		void setText(std::string text);
};
#endif
