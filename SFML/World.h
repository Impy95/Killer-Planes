//
// The game World
//
#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureManager.h"
#include "Aircraft.h"

namespace sf
{
	class RenderWindow;
}
namespace GEX {
	class World
	{
	public:
		explicit					World(sf::RenderWindow& window);

		void						update(sf::Time dt);
		void						draw();

	private:
		void						loadTextures();
		void						buildScene();

	private:
		enum Layer 
		{
			Background = 0,
			Air,
			LayerCount
		};
	private:
		sf::RenderWindow&			window_;
		sf::View					worldView_;
		TextureManager				textures_;

		SceneNode					sceneGraph_;
		std::vector<SceneNode*>		sceneLayer_;

		sf::FloatRect				worldBounds_;
		sf::Vector2f				spawnPosition_;
		float						scrollSpeeds_;

		int							count_;
		Aircraft*					playerAircraft_;

	};
}


