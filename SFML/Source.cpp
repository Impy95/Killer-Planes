#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;

	game.run();
	/*
	sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Magenta);

	while (window.isOpen())
	{
		// get user input
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Right)
					shape.move(1, 0);
				if (event.key.code == sf::Keyboard::Key::Left)
					shape.move(-1, 0);
				if (event.key.code == sf::Keyboard::Key::Up)
					shape.move(0, -1);
				if (event.key.code == sf::Keyboard::Key::Down)
					shape.move(0, 1);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		// update the world
		auto p = shape.getPosition();
		p.x = p.x > 600 ? 0 : p.x;
		p.y = p.y > 400 ? 0 : p.y;

		p.x = p.x < 0 ? 600 : p.x;
		p.y = p.y < 0 ? 400 : p.y;

		shape.setPosition(p);

		// render the world
		window.clear();
		window.draw(shape);
		window.display();
	}
	*/
	return 0;
}