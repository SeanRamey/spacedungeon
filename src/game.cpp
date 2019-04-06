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
    Level level = Level("data/levels/test-map.map", "data/graphics/tileset.png", "data/levels/test-map.dat");

    while (window.isOpen())
    {
        unprocessedTime = loopTimer.getElapsedTime() + unprocessedTime;
        secondsTime = secondsTime + loopTimer.getElapsedTime();
        loopTimer.restart();

        while(unprocessedTime >= FRAME_TIME)
        {
            unprocessedTime = unprocessedTime - FRAME_TIME;

            processEvents();

            // Update game objects
            level.update(FRAME_TIME, window);
            ++updatesPerSecond;
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw graphics to buffer
        level.draw(window);

        // Display buffer
        window.display();

        ++framesPerSecond;

        // Check if 1 second has passed
        if( secondsTime.asSeconds() >= 1)
        {
            printf("FPS: %u, UpdatesPerSecond: %u\n", framesPerSecond, updatesPerSecond);
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
