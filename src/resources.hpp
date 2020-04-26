#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "sfmlpch.hpp"
#include "animation.hpp"

namespace Resources {

	extern sf::RenderWindow* window;

	enum FontID : int {
		VOID,
		PERFECTDOS,
		NUM_FONTS
	};

	enum TextureID : int {
		PLAYER_SHIP,
		ALIEN_SHIP,
		BULLET,
		SPECIALBULLET,
		SHRAPNEL,
		HEALTH_BAR,
		BUTTON,
		NUM_TEXTURES
	};

	enum SoundID : int {
		SND_PLAYER_SHOOT,
		SND_ENEMY_EXPLODE,
		SND_HIT,

		NUM_SOUNDS
	};

	void load();
	void unload();
	void playSound(SoundID id);
	sf::Font* getFont(FontID id);
	sf::Sound* getSound(SoundID id);
	sf::Texture* getTexture(TextureID id);
	sf::SoundBuffer* getSoundBuffer(SoundID id);
}

#endif
