#include "State.h"
#include "StateStack.h"
//
//

namespace GEX
{
	State::State(StateStack & stack, Context context)
		: stack_(&stack)
		, context_(context)
	{}

	State::~State()
	{}


	void State::requestStackPush(StateID stateID)
	{
		stack_->pushState(stateID);
	}

	void State::requestStackPop()
	{
		stack_->popState();
	}

	void State::requestStackClear()
	{
		stack_->clearStates();
	}

	State::Context State::getContext() const
	{
		return context_;
	}
	State::Context::Context(
		sf::RenderWindow & window, 
		TextureManager & textures, 
		sf::Font & font, 
		PlayerControl & player)
		
		: window(&window)
		, textures(&textures)
		, font(&font)
		, player(&player)
	{}
}