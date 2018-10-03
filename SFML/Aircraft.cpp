#include "Aircraft.h"
#include "Category.h"
#include "DataTables.h"

namespace GEX {

	namespace 
	{
		const std::map<AircraftType, AircraftData> TABLE = initalizeAircraftData();
	}
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
		: Entity(TABLE.at(type).hitpoints),
		type_(type),
		sprite_(textures.get(TABLE.at(type).texture))
	{
		sf::FloatRect bounds = sprite_.getLocalBounds();
		sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void GEX::Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
	unsigned int Aircraft::getCategory() const
	{
		switch (type_)
		{
		case AircraftType::Eagle:
			return Category::PlayerAircraft;
			break;

		default:
			return Category::EnemyAircraft;
			break;
		}
	}
}
