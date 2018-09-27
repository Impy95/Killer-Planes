//
//
#pragma once

#include "TextureManager.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateIdentifier.h"

namespace GEX {
	// forward declarations
	class StateStack;
	class PlayerControl;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;
		struct Context
		{
			Context(
				sf::RenderWindow&	window,
				TextureManager&		textures,
				sf::Font&			font,
				PlayerControl&		player);

			sf::RenderWindow*	window;
			TextureManager*		textures;
			sf::Font*			font;
			PlayerControl*		player;
		};

	public:
						State(StateStack& stack, Context context);
		virtual			~State();

		virtual void	draw() = 0;
		virtual bool	update(sf::Time) = 0;
		virtual bool	handleEvent(const sf::Event& event) = 0;

	protected:
		void			requestStackPush(StateID stateID);
		void			requestStackPop();
		void			requestStackClear();

		Context			getContext() const;

	private:
		StateStack*		stack_;
		Context 		context_;
	};
}

