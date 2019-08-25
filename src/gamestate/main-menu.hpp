#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP
#include "menu.hpp"
class MainMenu : public GameState {
	public:
		void update(sf::Time frameTime);
		void draw(sf::RenderWindow& window);
		void init();
		static void ButtonCallback(MainMenu* mm);
		void clear();
		sf::View getView();
		MainMenu(Game* game);
		~MainMenu();

	private:
		Menu menu;
		std::string titleText;
		sf::Clock sineWaveTimer;
};
#endif
