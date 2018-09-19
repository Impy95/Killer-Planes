#include "Aircraft.h"

namespace GEX {
	TextureID toTextureID(AircraftType type)
	{
		switch (type)
		{
		case AircraftType::Eagle:
			return TextureID::Eagle;
			break;

		case AircraftType::Raptor:
			return TextureID::Raptor;
			break;

		default:
			return TextureID::Raptor;
			break;
		}
	}
	GEX::Aircraft::Aircraft(AircraftType type, const TextureManager & textures)
		: type_(type),
		sprite_(textures.get(toTextureID(type)))
	{
		sf::FloatRect bounds = sprite_.getLocalBounds();
		sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void GEX::Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
}
