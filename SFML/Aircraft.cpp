#include "Aircraft.h"
#include "Category.h"
#include "DataTables.h"
#include "TextNode.h"
#include <memory>
#include <string>

namespace GEX {

	namespace 
	{
		const std::map<AircraftType, AircraftData> TABLE = initalizeAircraftData();
	}

	GEX::Aircraft::Aircraft(AircraftType type, const TextureManager & textures)
		: Entity(TABLE.at(type).hitpoints),
		type_(type),
		sprite_(textures.get(TABLE.at(type).texture))
	{
		sf::FloatRect bounds = sprite_.getLocalBounds();
		sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

		// Creating health display and attaching to graph
		std::unique_ptr<TextNode> health(new TextNode(std::string("")));
		healthDisplay_ = health.get();
		attachChild(std::move(health));

		//Creating missile display and attaching to the graph
		std::unique_ptr<TextNode> missile(new TextNode(""));
		missileDisplay_ = missile.get();
		attachChild(std::move(missile));
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
	void Aircraft::updateTexts()
	{
		healthDisplay_->setText(std::to_string(getHitPoints()) + "HP");
		healthDisplay_->setPosition(0.f, 50.f);
		healthDisplay_->setRotation(-getRotation());
	}

	void Aircraft::updateCurrent(sf::Time dt)
	{
		updateTexts();
		Entity::updateCurrent(dt);
	}
}
