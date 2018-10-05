#include "GameState.h"

GameState::GameState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, world_(*context.window)
	, player_(*context.player)
{}

void GameState::draw()
{
	world_.draw();
}

bool GameState::update(sf::Time dt)
{
	world_.update(dt);

	GEX::CommandQueue& commands = world_.getCommandQueue();
	player_.handleRealtimeInput(commands);
	return true;
}

bool GameState::handleEvent(const sf::Event & event)
{
	GEX::CommandQueue& commands = world_.getCommandQueue();
	player_.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Escape)
		requestStackPush(GEX::StateID::Pause);

	// Pushing G will enter GEX State
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::G)
		requestStackPush(GEX::StateID::GEX);

	return true;
}
