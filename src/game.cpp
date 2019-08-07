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
    Level* level = static_cast<Level*>(gameStates[currentState]);
    gameStates[currentState]->update(frametime, window);
	//std::cout << level->getPlayer()->isDestroyed() << "   ";
	//std::cout << level->getPlayer()->getHitpoints() << std::endl;
    if(level != nullptr) {
        if(level->checkLose()) {
            // TODO handle player losing sequence
            changeState(0, true);
        }
    }
}

void Game::draw(sf::RenderWindow& window) {
    gameStates[currentState]->draw(window);
}

void Game::changeState(int newState, bool carryPlayer) {
    int prevState = currentState;
    gameStates[currentState]->clear();
    if(newState == -1) {
        // looping value to end if we hit the end
        currentState++;
        if(currentState > STATECOUNT - 1) {
            currentState = 0;
        }
        if(currentState < 0) {
            currentState = STATECOUNT - 1;
        }
    } else {
        this->currentState = newState;
    }

    // values are casted to check if either are levels
    Level* prevLevel = dynamic_cast<Level*>(gameStates[prevState]);
    Level* currLevel = dynamic_cast<Level*>(gameStates[currentState]);
    if(prevLevel != nullptr){
        // storing previous level to access previous player
        previousLevel = prevLevel;
    }
    if(currLevel != nullptr){
        // used as a reset sequence, moves player
		if(carryPlayer && previousLevel != nullptr){
        	currLevel->setPlayer(previousLevel->getPlayer());
        	currLevel->getPlayer()->setLevel(currLevel);
			currLevel->getPlayer()->setVelocity(sf::Vector2f(0, 0));
		}
		currLevel->getPlayer()->revive();
		currLevel->getPlayer()->setPosition(20, -50);
    } 
    gameStates[currentState]->init();
}

GameState* Game::getGameState() {
    return gameStates[currentState];
}
