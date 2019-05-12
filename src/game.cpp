#include <iostream>
#include "game.hpp"
#include "random-numbers.hpp"
#include "level.hpp"
#include "resources.hpp"
using namespace Input;

Game::Game(sf::VideoMode videoMode)
: videoMode(videoMode)
{
    window.create(videoMode, "game-alpha-prototype-1", sf::Style::Close);
    Util::SeedRandomNumbers();
    Resources::window = &window;
}

Game::~Game()
{

}

void Game::run()
{
    // Start the game loop
    sf::Clock loopTimer;
    sf::Time secondsTime = sf::Time::Zero;
    sf::Time unprocessedTime = sf::Time::Zero;
    const sf::Time FRAME_TIME = sf::microseconds(16666);// 60 FPS
    unsigned int framesPerSecond = 0;
    unsigned int updatesPerSecond = 0;

    window.setVerticalSyncEnabled(true);

    Level* level = new Level(this, "data/levels/test-map.map", "data/graphics/tileset.png", "data/levels/test-map.dat", 32); 
    Level* level2 = new Level(this, "data/levels/test-map2.map", "data/graphics/tileset.png", "data/levels/test-map.dat", 32); 
    gameStates.push_back(level);
    gameStates.push_back(level2);
    level->init();

    while (window.isOpen()){
        unprocessedTime = loopTimer.getElapsedTime() + unprocessedTime;
        secondsTime = secondsTime + loopTimer.getElapsedTime();
        loopTimer.restart();

        while(unprocessedTime >= FRAME_TIME)
        {
            unprocessedTime = unprocessedTime - FRAME_TIME;

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
        if( secondsTime.asSeconds() >= 1)
        {
            //printf("FPS: %u, UpdatesPerSecond: %u\n", framesPerSecond, updatesPerSecond);
            secondsTime = sf::Time::Zero;
            updatesPerSecond = 0;
            framesPerSecond = 0;
        }
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if (event.type == sf::Event::EventType::Closed)
        {
            window.close();
        }
        else if(event.type ==sf::Event::EventType::MouseMoved)
        {
            Input::updateMousePosition(&window);
        }

        Input::handleEvent(&event);
    }
}

void Game::update(sf::Time frametime, sf::RenderWindow& window){
    gameStates[currentState]->update(frametime, window);
    Level* level = static_cast<Level*>(gameStates[currentState]);
    if(level != nullptr){
        if(level->checkLose()){
           updateState(-1, true);
        }
    }
}

void Game::draw(sf::RenderWindow& window) {
    gameStates[currentState]->draw(window);
}

void Game::updateState(int newState, bool carryPlayer){
    int prevState = currentState;
    gameStates[currentState]->clear();
    if(newState == -1) {
        currentState++;
        if(currentState > STATECOUNT - 1) currentState = 0;
        if(currentState < 0)              currentState = STATECOUNT - 1;
    } else {
        this->currentState = newState;
    }
    gameStates[currentState]->init();

    Level* prevLevel = static_cast<Level*>(gameStates[prevState]);
    Level* currLevel = static_cast<Level*>(gameStates[currentState]);
    if(currLevel != nullptr && carryPlayer && prevLevel != nullptr){
        PlayerShip* ps = prevLevel->getPlayer();
        if(ps != nullptr){
            ps->setHitpoints(100);
            ps->setPosition(0, 0);
            ps->revive();
            currLevel->setPlayer(ps);
            ps->setLevel(currLevel);
        }
    }
}

GameState* Game::getGameState(){
    return gameStates[currentState];
}