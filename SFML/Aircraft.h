//
// Aircraft class
//
#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include <SFML/Graphics/Sprite.hpp>

namespace GEX {
	class TextNode;

	// Aircraft types
	enum class AircraftType { Eagle, Raptor, Avenger };

	class Aircraft : public Entity
	{
	public:
						Aircraft(AircraftType type, const TextureManager& textures);

		virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int	getCategory() const override;
		void			updateTexts(); // update the mini health and missle display

	protected:
		void			updateCurrent(sf::Time dt) override;

	private:
		sf::Sprite		sprite_;
		AircraftType	type_;
		TextNode*		healthDisplay_;
		TextNode*		missileDisplay_;
	};
}

