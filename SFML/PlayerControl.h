///
/// Doxy comments go here
#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Command.h"

namespace GEX {
	
	// forward declarion
	class CommandQueue;

	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown
	};
	class PlayerControl
	{
	public:
		PlayerControl();

		void		handleEvent(const sf::Event& event, CommandQueue& commands);
		void		handleRealtimeInput(CommandQueue& commands);

	private:
		void		initalizeActions();


	private:
		std::map<sf::Keyboard::Key, Action>		keyBindings_;
		std::map<Action, Command>				actionBindings_;
	};
}

