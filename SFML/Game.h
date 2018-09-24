//
// Game Class
//
#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "World.h"
#include "PlayerControl.h"

namespace GEX {
	class Game
	{
	public:
		Game();
		~Game();

		void				run();

	private:
		void				processEvents();
		void				update(sf::Time deltaTime);
		void				render();

		void				handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		void				updateStatistics(sf::Time deltaTime);

	private:
		sf::RenderWindow	window_;
		World				world_;

		PlayerControl		player_;

		sf::Text			statisticsText_;
		sf::Time			statisticsUpdateTime_;
		unsigned int		statisticsNumFrames_;
		sf::Font			font_;
	};
}

