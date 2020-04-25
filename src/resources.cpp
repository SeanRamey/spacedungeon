#include "stdpch.hpp"

#include "log.hpp"
#include "animation.hpp"
#include "resources.hpp"

#define VOID_FILE "data/graphics/Void_2058.ttf"

#define PLAYER_SHIP_FILE "data/graphics/new-playership-idle.png"
#define ALIEN_SHIP_FILE "data/graphics/alien-ship.png"
#define BULLET_FILE "data/graphics/new-bullet.png"
#define BIG_BULLET_FILE "data/graphics/big-bullet_test.png"
#define SHRAPNEL_FILE "data/graphics/shrapnel.png"
#define HEALTH_BAR_FILE "data/graphics/healthBar.png"
#define BUTTON_FILE "data/graphics/button.png"

#define SND_PLAYER_SHOOT_FILE "data/sounds/shoot.wav"
#define SND_ENEMY_EXPLOSION_FILE "data/sounds/ded.wav"
#define SND_HIT "data/sounds/hit.wav"
#define MUSIC_1

namespace Resources {

	std::map<FontID, sf::Font*> fontMap;
	std::map<TextureID, sf::Texture*> textureMap;
	std::map<SoundID, sf::SoundBuffer*> soundBufferMap;
	std::map<SoundID, sf::Sound*> soundMap;
	sf::RenderWindow* window;

	std::string fontFiles[] = {
		VOID_FILE
	};

	std::string textureFiles[] = {
		PLAYER_SHIP_FILE,
		ALIEN_SHIP_FILE,
		BULLET_FILE,
		BIG_BULLET_FILE,
		SHRAPNEL_FILE,
		HEALTH_BAR_FILE,
		BUTTON_FILE,
	};

	std::string soundFiles[] = {
		SND_PLAYER_SHOOT_FILE,
		SND_ENEMY_EXPLOSION_FILE,
		SND_HIT
	};

	///////////////////////////
	void load() {

		for(int i = 0; i < NUM_FONTS; i++) {
			sf::Font *font = new sf::Font();
			fontMap[(FontID)i] = nullptr; // make sure each texture pointer is initialized to null
			if(!font->loadFromFile(fontFiles[i])) {
				Log::error("Unable to load font: " + fontFiles[i]);
				std::exit(-1);
			} else {
				fontMap[(FontID)i] = font;
			}
		}

		for(int i = 0; i < NUM_TEXTURES; i++) {
			sf::Texture *texture = new sf::Texture();
			textureMap[(TextureID)i] = nullptr; // make sure each texture pointer is initialized to null
			if(!texture->loadFromFile(textureFiles[i])) {
				Log::error("Unable to load texture: " + textureFiles[i]);
				std::exit(-1);
			} else {
				textureMap[(TextureID)i] = texture;
			}
		}

		for(int i = 0; i < NUM_SOUNDS; i++) {
			sf::SoundBuffer *buffer = new sf::SoundBuffer();
			sf::Sound *sound = new sf::Sound();
			soundBufferMap[(SoundID)i] = nullptr; // make sure each sound pointer is initialized to null
			if(!buffer->loadFromFile(soundFiles[i])) {
				Log::error("Unable to load sound: " + soundFiles[i]);
				std::exit(-1);
			} else {
				soundBufferMap[(SoundID)i] = buffer;
				sound->setBuffer(*buffer);
				soundMap[(SoundID)i] = sound;
			}
		}
	}

	///////////////////////////
	void unload() {

		for(int i = 0; i < NUM_FONTS; ++i) {
			sf::Font* font = fontMap.at((FontID)i);
			if(font != nullptr) {
				delete font;
			}
		}

		for(int i = 0; i < NUM_TEXTURES; ++i) {
			sf::Texture* texture = textureMap.at((TextureID)i);
			if(texture != nullptr) {
				delete texture;
			}
		}

		for(int i = 0; i < NUM_SOUNDS; ++i) {
			sf::SoundBuffer *buffer = soundBufferMap.at((SoundID)i);
			sf::Sound *sound = soundMap.at((SoundID)i);

			if(sound != nullptr) {
				delete sound;
			}

			if(buffer != nullptr) {
				delete buffer;
			}
		}
	}

	///////////////////////////
	void playSound(SoundID id) {
		if(soundMap[id] != nullptr) {
			soundMap[id]->play();
		}
	}

	///////////////////////////
	sf::Font* getFont(FontID id) {
		if(fontMap.at(id) == nullptr) {
			return nullptr;
		}
		return fontMap.at(id);
	}

	///////////////////////////
	sf::Sound* getSound(SoundID id) {
		if(soundMap[id] == nullptr) {
			return nullptr;
		}
		return soundMap[id];
	}

	///////////////////////////
	sf::Texture* getTexture(TextureID id) {
		if(textureMap[id] == nullptr) {
			return nullptr;
		}
		return textureMap[id];
	}

	///////////////////////////
	sf::SoundBuffer* getSoundBuffer(SoundID id) {
		if(soundBufferMap[id] == nullptr) {
			return nullptr;
		}
		return soundBufferMap[id];
	}

}
