#include "Game.h"
#include <string>

namespace {
	const sf::IntRect NO_ROLL(0, 0, 48, 64);
	const sf::IntRect ROLL_LEFT(48, 0, 48, 64);
	const sf::IntRect ROLL_RIGHT(96, 0, 48, 64);
}

Game::Game()
	: window_(sf::VideoMode(1200, 800), "Killer Circles"),
	world_(window_),
	statisticsText_(),
	statisticsUpdateTime_(sf::Time::Zero),
	statisticsNumFrames_(0)
{
	//loadTextures();
	//player_.setTexture(textures_.get(GEX::TextureID::Airplane));
	//player_.setTextureRect(sf::IntRect(0, 0, 48, 64));
	//player_.setPosition(100.f, 100.f);

	//sf::FloatRect bounds = player_.getLocalBounds();
	//player_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	if (!font_.loadFromFile("Media/Sansation.ttf"))
	{
		// error handling
	}

	statisticsText_.setFont(font_);
	statisticsText_.setPosition(5.0f, 5.0f);
	statisticsText_.setCharacterSize(15.0f);
	statisticsText_.setString("Frames / Second = \n Time / Update =");
}


Game::~Game()
{
}


void Game::run()
{
	const sf::Time SPF = sf::seconds(1.0f / 60.f); // seconds per frame for 60 fps

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > SPF)
		{
			updateStatistics(SPF);
			update(SPF);
			timeSinceLastUpdate -= SPF;
		}

		//updateStatistics(timeSinceLastUpdate);
		//update(timeSinceLastUpdate);

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			window_.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	//if (key == sf::Keyboard::Up)
	//	isMovingUp = isPressed;
	//if (key == sf::Keyboard::Down)
	//	isMovingDown = isPressed;
	//if (key == sf::Keyboard::Left)
	//	isMovingLeft = isPressed;
	//if (key == sf::Keyboard::Right)
	//	isMovingRight = isPressed;
	//if (key == sf::Keyboard::J)
	//	isRotatingRight = isPressed;
	//if (key == sf::Keyboard::K)
	//	isRotatingLeft = isPressed;

}

void Game::updateStatistics(sf::Time deltaTime)
{
	statisticsUpdateTime_ += deltaTime;
	statisticsNumFrames_ += 1;

	if (statisticsUpdateTime_ > sf::seconds(1))
	{
		statisticsText_.setString(
			"Frames / Second = " + std::to_string(statisticsNumFrames_) + "\n" +
			"Time / Update = " + std::to_string(statisticsUpdateTime_.asMicroseconds() / statisticsNumFrames_)
		);
		statisticsUpdateTime_ -= sf::seconds(1);
		statisticsNumFrames_ = 0;
	}
}

//void Game::drawRoundingBox()
//{
//	auto rect = player_.getGlobalBounds();
//
//	sf::RectangleShape boundingBox;
//	boundingBox.setPosition(sf::Vector2f(rect.left, rect.top));
//	boundingBox.setSize(sf::Vector2f(rect.width, rect.height));
//	boundingBox.setFillColor(sf::Color::Transparent);
//	boundingBox.setOutlineColor(sf::Color::Green);
//	boundingBox.setOutlineThickness(3.f);
//
//	window_.draw(boundingBox);
//}

void Game::update(sf::Time deltaTime)
{
	//
	// update
	//
	world_.update(deltaTime);

	//const float PLAYER_SPEED = 1.0f;

	//if (isMovingDown)
	//	velocity_.y += PLAYER_SPEED;
	//if (isMovingUp)
	//	velocity_.y -= PLAYER_SPEED;
	//if (isMovingRight)
	//{
	//	velocity_.x += PLAYER_SPEED;
	//	player_.setTextureRect(sf::IntRect(-5, 0, 48, 64));
	//}
	//if (isMovingLeft)
	//{
	//	velocity_.x -= PLAYER_SPEED;
	//	player_.setTextureRect(sf::IntRect(5, 0, 48, 64));
	//}
	//if (isRotatingRight)
	//	angularVelocity_ += PLAYER_SPEED;
	//if (isRotatingLeft)
	//	angularVelocity_ -= PLAYER_SPEED;
	//if (!isMovingRight && !isMovingLeft)
	//{
	//	player_.setTextureRect(sf::IntRect(0, 0, 48, 64));
	//	if (velocity_.x > 0)
	//		velocity_.x -= 1;
	//	else if (velocity_.x < 0)
	//		velocity_.x += 1;
		
	//}
	//if (!isMovingDown && !isMovingUp)
	//{

	//	if (velocity_.y > 0)
	//		velocity_.y -= 1;
	//	else if (velocity_.y < 0)
	//		velocity_.y += 1;
	//}


	//player_.move(velocity_ * deltaTime.asSeconds());
	//player_.rotate(angularVelocity_ * deltaTime.asSeconds());

	//// update the world
	//auto p = player_.getPosition();
	//p.x = p.x > 1200 ? 0 : p.x;
	//p.y = p.y > 800 ? 0 : p.y;

	//p.x = p.x < 0 ? 1200 : p.x;
	//p.y = p.y < 0 ? 800 : p.y;
	//player_.setPosition(p);
}

void Game::render()
{
	// render the world
	window_.clear();
	world_.draw();

	window_.setView(window_.getDefaultView());
	window_.draw(statisticsText_);
	window_.display();
}
