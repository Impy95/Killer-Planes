//
// Aircraft class
//
#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include <SFML/Graphics/Sprite.hpp>

namespace GEX {
	enum class AircraftType { Eagle, Raptor, Avenger };

	class Aircraft : public Entity
	{
	public:
						Aircraft(AircraftType type, const TextureManager& textures);

		virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int	getCategory() const override;

	private:
		sf::Sprite		sprite_;
		AircraftType	type_;
	};
}

