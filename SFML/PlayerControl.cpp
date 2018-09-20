#include "PlayerControl.h"
#include "Aircraft.h"
#include "Command.h"

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
		keyBindings_[sf::Keyboard::Left] = Action::MoveLeft;
		keyBindings_[sf::Keyboard::Right] = Action::MoveRight;
		keyBindings_[sf::Keyboard::Up] = Action::MoveUp;
		keyBindings_[sf::Keyboard::Down] = Action::MoveDown;

		// set up action bindings
		initalizeActions();
	}

	void PlayerControl::initalizeActions()
	{
		const float playerSpeed = 200.f;

		actionBindings_[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		actionBindings_[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
		actionBindings_[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
		actionBindings_[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	}


}
