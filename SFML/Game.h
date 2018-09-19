//
// Game Class
//
#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "World.h"

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
	//void				loadTextures();
	//void				drawRoundingBox();

private:
	//bool				isMovingRight;
	//bool				isMovingLeft;
	//bool				isMovingUp;
	//bool				isMovingDown;
	//bool				isRotatingRight;
	//bool				isRotatingLeft;

	sf::RenderWindow	window_;
	GEX::World				world_;
	//sf::Sprite			player_;
	//GEX::TextureManager	textures_;

	sf::Text			statisticsText_;
	sf::Time			statisticsUpdateTime_;
	unsigned int		statisticsNumFrames_;
	sf::Font			font_;

	//sf::Vector2f		velocity_;
	//float				angularVelocity_;
};

