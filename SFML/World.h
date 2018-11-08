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
#include "CommandQueue.h"

#include <vector>
#include "BloomEffect.h"
#include "SoundPlayer.h"

// forward declaration
namespace sf
{
	class RenderTarget;
}
namespace GEX {
	class World
	{
	public:
		explicit					World(sf::RenderTarget& outputTarget, SoundPlayer& sounds);

		void						update(sf::Time dt, CommandQueue& commands);
		void						updateSounds();
		void						draw();

		CommandQueue&				getCommandQueue();
		bool						hasAlivePlayer() const;
		bool						hasPlayerReachedEnd() const;
	private:
		void						loadTextures();
		void						buildScene();
		void						adaptPlayerPosition();
		void						adaptPlayerVelocity();

		void						addEnemies();
		void						addEnemy(AircraftType type, float relX, float relY);
		void						spawnEnemies();

		sf::FloatRect				getViewBounds() const;
		sf::FloatRect				getBattlefieldBounds() const;

		void						guideMissile();
		void						handleCollisions();
		bool						matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

		void						destroyEntitiesOutOfView();

	private:
		enum Layer 
		{
			Background = 0,
			LowerAir,
			UpperAir,
			LayerCount
		};

		struct SpawnPoint
		{
			SpawnPoint(AircraftType type, float x, float y) 
				: type(type)
				, x(x)
				, y(y) 
			{}
			AircraftType	type;
			float			x;
			float			y;
		};
	private:
		sf::RenderTarget&			target_;
		sf::RenderTexture			sceneTexture_;
		sf::View					worldView_;
		TextureManager				textures_;
		SoundPlayer&				sounds_;

		SceneNode					sceneGraph_;
		std::vector<SceneNode*>		sceneLayer_;

		CommandQueue				commandQueue_;

		sf::FloatRect				worldBounds_;
		sf::Vector2f				spawnPosition_;
		float						scrollSpeeds_;

		int							count_;
		Aircraft*					playerAircraft_;

		std::vector<SpawnPoint>		enemySpawnPoints_;
		std::vector<Aircraft*>		activeEnemies_;

		BloomEffect					bloomEffect_;
	};
}


