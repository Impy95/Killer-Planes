/**
* @file
* Aircraft.cpp
* @author
* Vaughn Rowse 2018
* @version 1.0
*
* @section DESCRIPTION
*
* @section LICENSE
*
* Copyright 2018
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/
#include "Aircraft.h"
#include "Category.h"
#include "DataTables.h"
#include "TextNode.h"
#include <memory>
#include <string>
#include "Utility.h"

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
		updateMovementPattern(dt);
		updateTexts();
		Entity::updateCurrent(dt);
	}

	void Aircraft::updateMovementPattern(sf::Time dt)
	{
		// Movement pattern
		const std::vector<Direction>& directions = TABLE.at(type_).directions;
		if (!directions.empty())
		{
			if (travelDistance_ > directions.at(directionIndex_).distance)
			{
				directionIndex_ = (++directionIndex_) % directions.size();
				travelDistance_ = 0;
			}
			float radians = toRadian(directions.at(directionIndex_).angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);
			setVelocity(vx, vy);
			travelDistance_ += getMaxSpeed() * dt.asSeconds();
		}
	}
	float Aircraft::getMaxSpeed() const
	{
		return TABLE.at(type_).speed;
	}
}
