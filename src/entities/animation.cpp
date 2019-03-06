#include "animation.hpp"
#include "math.h"

     
void Animation::init(sf::Image image, sf::Vector2u spriteSize, std::vector<int> stateLengths){
    timer.restart();
    this->stateLengths = stateLengths;
    sf::Vector2u imageSize = image.getSize();
    sf::Vector2u spriteCount = sf::Vector2u(imageSize.x / spriteSize.x, imageSize.y / spriteSize.y);
    int currentFramePosition = 0; 
    int currentState = 0;
    sf::Vector2i currentPosition;
    textures.push_back(std::vector<sf::Texture>());
    for(int i = 0; i < spriteCount.x; i++){
        for(int j = 0; j < spriteCount.y; j++){
            currentFramePosition++;
            if(currentFramePosition > stateLengths[currentState]){
                textures.push_back(std::vector<sf::Texture>());
                currentFramePosition = 0;
                currentState++;
            }

            currentPosition = sf::Vector2i(32 * (i % spriteCount.x), 32 * (floor(j / spriteCount.y)));
            sf::Texture texture;
            texture.loadFromImage(image, sf::IntRect(currentPosition.x, currentPosition.y, spriteSize.x, spriteSize.y));

            textures.at(currentState).push_back(texture);
        } 
    }
}

sf::Texture* Animation::getCurrentTexture(){
    return &textures.at(currentState).at(currentFrame);
}

void Animation::update(){
    if(timer.getElapsedTime().asMilliseconds() > delay.asMilliseconds()){
        timer.restart();
        currentFrame++;
        if(currentFrame > stateLengths[currentState] - 1){
            currentFrame = 0;
        }
    }
}

void Animation::setState(short state){
    currentState = state;
}

void Animation::setDelay(sf::Time delay){
    this->delay = delay;
}

Animation::Animation(){
    this->currentState = 0;
    this->currentFrame = 0;
}

Animation::~Animation(){

}
