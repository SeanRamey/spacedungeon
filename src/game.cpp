#include <iostream>
#include "game.hpp"
#include "random-numbers.hpp"
#include "level.hpp"
#include "resources.hpp"
#include "main-menu.hpp"
using namespace Input;

Game::Game(sf::VideoMode videoMode)
: videoMode(videoMode)
{
    init();
}

Game::~Game() {

}

void Game::init() {

    // set up window
    window.create(videoMode, "spacedungeon", sf::Style::Close);
    Resources::window = &window;
    
    // seed random number generator
    Util::SeedRandomNumbers();

    // creation of all levels 
    // they lay in a dorment state while game is being played out until loaded (very little memory wasted)
    Level* level = new Level(this, "data/levels/test-map.map", "data/graphics/tileset.png", "data/levels/test-map.dat", 32); 
    Level* level2 = new Level(this, "data/levels/test-map2.map", "data/graphics/tileset.png", "data/levels/test-map.dat", 32); 
	MainMenu* menu = new MainMenu(this);
	gameStates.push_back(menu);
    gameStates.push_back(level);
    gameStates.push_back(level2);
    menu->init();
}


void Game::run() {
    // Start the game loop
    sf::Clock loopTimer;
    sf::Time secondsTime = sf::Time::Zero;
    sf::Time unprocessedTime = sf::Time::Zero;
    const sf::Time FRAME_TIME = sf::seconds(1.0f/60.0f); // 60 FPS
    unsigned int framesPerSecond = 0;
    unsigned int updatesPerSecond = 0;

    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        unprocessedTime += loopTimer.getElapsedTime();
        secondsTime += loopTimer.getElapsedTime();
        loopTimer.restart();

        while(unprocessedTime >= FRAME_TIME) {
            unprocessedTime -= FRAME_TIME;

            processEvents();

            // Update game objects
            update(FRAME_TIME, window);
            ++updatesPerSecond;
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw graphics to buffer
        draw(window);

        // Display buffer
        window.display();

        ++framesPerSecond;

        // Check if 1 second has passed
        if( secondsTime.asSeconds() >= 1) {
            #ifdef DEBUG
            std::cout << "FPS: " << framesPerSecond << ", Updates Per Second: " << updatesPerSecond << "\n";
	        #endif
	        secondsTime = sf::Time::Zero;
            updatesPerSecond = 0;
            framesPerSecond = 0;
        }
    }
}

void Game::processEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed) {
            window.close();
        }
        else if(event.type ==sf::Event::EventType::MouseMoved) {
            Input::updateMousePosition(&window);
        }

        Input::handleEvent(&event);
    }
}

void Game::update(sf::Time frametime, sf::RenderWindow& window) {
    gameStates[currentState]->update(frametime, window);
}

void Game::draw(sf::RenderWindow& window) {
    gameStates[currentState]->draw(window);
}

void Game::changeState(int newState, bool carryPlayer) {

    // check for valid input
    if(newState < 0 || newState >= gameStates.size()) {
        return;
    }

    prevState = currentState;

    // values are casted to check if either are levels
    Level* prevLevel = dynamic_cast<Level*>(gameStates[prevState]);
    Level* nextLevel = dynamic_cast<Level*>(gameStates[newState]);

    // carry player state over from previous level
    if(carryPlayer && prevLevel != nullptr && nextLevel != nullptr){
        nextLevel->setPlayer(prevLevel->getPlayer());
        nextLevel->getPlayer()->setLevel(nextLevel);
        nextLevel->getPlayer()->setVelocity(sf::Vector2f(0, 0));
        nextLevel->getPlayer()->revive();
        nextLevel->getPlayer()->setPosition(20, -50);
    }
    
    gameStates.at(prevState)->clear();
    gameStates.at(newState)->init();
    currentState = newState;
}


void Game::nextState(bool carryPlayer) {
    int nextState;
    // loop current state when it reaches the end
    if(gameStates.size() - 1 < currentState + 1) {
        nextState = 0; // goto first state by default
    } else {
        nextState = currentState + 1;
    }

    changeState(nextState, carryPlayer);
}

GameState* Game::getGameState() {
    return gameStates[currentState];
}
