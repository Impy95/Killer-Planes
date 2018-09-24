#include "PlayerControl.h"
#include "Aircraft.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Category.h"

namespace GEX {
	struct AircraftMover
	{
	public:
		AircraftMover(float vx, float vy)
			: velocity(vx, vy)
		{}
		void operator() (Aircraft& aircraft, sf::Time) const
		{
			aircraft.accelerate(velocity);
		}

		sf::Vector2f velocity;
	};
	PlayerControl::PlayerControl()
	{
		// set up bindings
		keyBindings_[sf::Keyboard::A] = Action::MoveLeft;
		keyBindings_[sf::Keyboard::D] = Action::MoveRight;
		keyBindings_[sf::Keyboard::W] = Action::MoveUp;
		keyBindings_[sf::Keyboard::S] = Action::MoveDown;

		// set up action bindings
		initalizeActions();

		for (auto& pair : actionBindings_)
			pair.second.category = Category::PlayerAircraft;
	}

	void PlayerControl::handleEvent(const sf::Event & event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			auto found = keyBindings_.find(event.key.code);
			if (found != keyBindings_.end())
			{
				commands.push(actionBindings_[found->second]);
			}
		}
	}

	void PlayerControl::handleRealtimeInput(CommandQueue & commands)
	{
		// itraverse all assigned keys, look up action, generate command
		for (auto pair : keyBindings_)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
				commands.push(actionBindings_[pair.second]);
		}
	}

	void PlayerControl::initalizeActions()
	{
		const float playerSpeed = 200.f;

		actionBindings_[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		actionBindings_[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
		actionBindings_[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		actionBindings_[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
	}

	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveDown:
		case Action::MoveUp:
			return true;
			break;
		default:
			return false;
			break;
		}
	}


}
