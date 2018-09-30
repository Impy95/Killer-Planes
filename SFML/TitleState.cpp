#include "TitleState.h"
#include "TextureManager.h"
#include "Utility.h"

TitleState::TitleState(GEX::StateStack & stack, Context context)
	: State(stack, context)
	, backgroundSprite_()
	, text_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{
	backgroundSprite_.setTexture(context.textures->get(GEX::TextureID::TitleScreen));

	text_.setFont(*context.font);
	text_.setString("Press any key to start");

	centerOrigin(text_);
	text_.setPosition(context.window->getView().getSize() / 2.f);


}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(backgroundSprite_);

	if (showText_)
		window.draw(text_);
}

bool TitleState::update(sf::Time dt)
{
	textEffectTime_ += dt;

	if (textEffectTime_ >= sf::seconds(0.5f))
	{
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(GEX::StateID::Game);
	}

	return true;
}
