#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP
#include "ui-element.hpp"
#include "ui-text-element.hpp"
#include "game-state.hpp"

class MainMenu;
class UIButton : public UIElement {
    private:
        UITextElement text;
        sf::Font font;
		GameState* parent;
		void(*callback)(MainMenu*);

    public:
        UIButton(sf::Vector2f position, sf::Texture* texture, GameState* parent, void(*callback)(MainMenu*));
        ~UIButton();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update();
 		void setSize(sf::Vector2u size);
		void setString(std::string text);
		UITextElement& getText();
};
#endif
