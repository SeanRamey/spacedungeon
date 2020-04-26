#include <iostream>
#include "game.hpp"
#include "random-numbers.hpp"
#include "level.hpp"
#include "resources.hpp"
#include "main-menu.hpp"
#include "input.hpp"
#include "ui-text-element.hpp"

///////////////////////////
Game::Game(sf::VideoMode videoMode)
: videoMode(videoMode)
{
	init();
}

///////////////////////////
Game::~Game() {
	Resources::unload();
}

///////////////////////////
void Game::init() {

	// set up window
	window.create(videoMode, "spacedungeon", sf::Style::Close);
	Resources::window = &window;
	Resources::load();

	// seed random number generator
	Util::SeedRandomNumbers();

	// initial game state
	std::shared_ptr<MainMenu> menu = std::make_shared<MainMenu>(this);
	pushState(menu);
}

///////////////////////////
void Game::run() {
	// Start the game loop
	sf::Clock loopTimer;
	sf::Time secondsTime = sf::Time::Zero;
	sf::Time unprocessedTime = sf::Time::Zero;
	const sf::Time FRAME_TIME = sf::seconds(1.0f/60.0f); // 60 FPS
	unsigned int framesPerSecond = 0;
	unsigned int updatesPerSecond = 0;
	sf::Font* font = Resources::getFont(Resources::FontID::PERFECTDOS);
	UITextElement fpsText(sf::Vector2f(0,0), font, std::to_string(framesPerSecond), 12);
	UITextElement updatesText(sf::Vector2f(0,30), font, std::to_string(updatesPerSecond), 12);

	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		unprocessedTime += loopTimer.getElapsedTime();
		secondsTime += loopTimer.getElapsedTime();
		loopTimer.restart();

		while(unprocessedTime >= FRAME_TIME) {
			unprocessedTime -= FRAME_TIME;

			processEvents();

			// Update game objects
			update(FRAME_TIME);
			++updatesPerSecond;
		}

		// Clear screen
		window.clear(sf::Color::Black);

		// Draw graphics to buffer
		draw(window);
		window.draw(fpsText);
		window.draw(updatesText);

		// Display buffer
		window.display();

		++framesPerSecond;

		// Check if 1 second has passed
		if( secondsTime.asSeconds() >= 1) {
			#ifdef DEBUG
			std::cout << "FPS: " << framesPerSecond << ", Updates Per Second: " << updatesPerSecond << "\n";
			#endif
			fpsText.setText("FPS:" + std::to_string(framesPerSecond));
			updatesText.setText("Updates:" + std::to_string(updatesPerSecond));
			secondsTime = sf::Time::Zero;
			updatesPerSecond = 0;
			framesPerSecond = 0;

		}
	}
}

///////////////////////////
void Game::processEvents() {
	sf::Event event;
	while (this->window.pollEvent(event)) {
		if (event.type == sf::Event::EventType::Closed) {
			window.close();
		}
		else if(event.type == sf::Event::EventType::MouseMoved) {
			Input::updateMousePosition(&window);
		}

		Input::handleEvent(&event);
	}
}

///////////////////////////
void Game::update(sf::Time frametime) {
	gameStates.top()->update(frametime);
}

///////////////////////////
void Game::draw(sf::RenderWindow& window) {
	gameStates.top()->draw(window);
}

///////////////////////////
void Game::changeState(std::shared_ptr<GameState> state) {
	popState();
	pushState(state);
}

///////////////////////////
void Game::pushState(std::shared_ptr<GameState> state) {
	state->init();
	gameStates.push(state);
}

///////////////////////////
void Game::popState() {
	if ( !gameStates.empty() ) {
		// check if gamestate is a level and if so, store the player
		std::shared_ptr<Level> levelState = std::dynamic_pointer_cast<Level>(gameStates.top());
		if(levelState.get() != nullptr) {
			player = levelState->getPlayer();
		}
		gameStates.top()->clear();
		gameStates.pop();
	}
}

///////////////////////////
std::shared_ptr<GameState> Game::getGameState() {
	return gameStates.top();
}

///////////////////////////
PlayerShip* Game::getPlayer() {
	return player;
}
