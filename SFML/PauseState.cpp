#include "PauseState.h"
#include "Utility.h"

PauseState::PauseState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, backgroundSprite_()
	, pauseText_()
	, instructionText_()
{
	sf::Font& font = *context.font;

	pauseText_.setFont(font);
	pauseText_.setString("Game Paused");
	pauseText_.setCharacterSize(80);
	centerOrigin(pauseText_);

	instructionText_.setFont(font);
	instructionText_.setString("Press Backspace to return to the main menu");
	centerOrigin(instructionText_);

	sf::Vector2f viewSize = context.window->getView().getSize();
	pauseText_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
	instructionText_.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color (0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pauseText_);
	window.draw(instructionText_);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Escape)
		requestStackPop();

	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}

	return false;
}
