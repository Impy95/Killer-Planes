#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "PlayerControl.h"
#include "TextureManager.h"
#include "StateStack.h"

class Application
{
public:
	Application();

	void						run();

private:
	void						processEvents();
	void						update(sf::Time dt);
	void						render();
		
	void						updateStatistics(sf::Time dt);
	void						registerStates();

private:
	static const sf::Time		TimePerFrame;

	sf::RenderWindow			window_;
	GEX::PlayerControl			player_;
	sf::Font					font_;
	GEX::TextureManager			textures_;
	GEX::StateStack				stateStack_;

	sf::Text					statisticsText_;
	sf::Time					statisticsUpdateTime_;
	unsigned int				statisticsNumFrames_;
	sf::Font					font_;
};

