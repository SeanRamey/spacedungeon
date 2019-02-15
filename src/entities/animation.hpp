#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Animation {
    private:
        short currentFrame;
        short currentState;
        sf::Time delay;
        sf::Clock timer;

        std::vector<std::vector<sf::Texture>> textures;

    public:
        void init(sf::Image image, sf::Vector2u spriteSize, int* stateLengths, int totalFrames);
        void update();
        void setState(short state);
        void setDelay(sf::Time delay);
        sf::Texture* getCurrentTexture();
        Animation();
        ~Animation();
    
    std::vector<int> stateLengths;
};
#endif