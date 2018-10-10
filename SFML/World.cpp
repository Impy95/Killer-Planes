/**
* @file
* World.cpp
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
#include "World.h"
#include "Aircraft.h"

namespace GEX {
	World::World(sf::RenderWindow& window) : window_(window),
		worldView_(window.getDefaultView()),
		textures_(),
		sceneGraph_(),
		sceneLayer_(),
		worldBounds_(0.f, 0.f, worldView_.getSize().x, 5000.f),
		spawnPosition_(worldView_.getSize().x / 2.f, worldBounds_.height - worldView_.getSize().y / 2.f),
		scrollSpeeds_(-50.f),
		count_(0),
		playerAircraft_(nullptr)
	{
		loadTextures();
		buildScene();

		// prepare the view
		worldView_.setCenter(spawnPosition_);
	}

	void World::update(sf::Time dt, CommandQueue& commands)
	{
		// scroll the world
		worldView_.move(0.f, scrollSpeeds_ * dt.asSeconds());

		playerAircraft_->setVelocity(0.f, 0.f);

		// run all the commands in the command queue
		while (!commandQueue_.isEmpty())
			sceneGraph_.onCommand(commandQueue_.pop(), dt);

		adaptPlayerVelocity();
		sceneGraph_.update(dt, commands);
		adaptPlayerPosition();

		spawnEnemies();

		// zoom a little
		// worldView_.zoom(1.001);	
		// rotate a little
		// worldView_.rotate(.1);

		// move player
		//sf::Vector2f pos = playerAircraft_->getPosition();
		//float bounds = worldView_.getSize().x;

		//if (pos.x < 120.f || pos.x > bounds - 120.f)
		//{
		//	playerAircraft_->setVelocity(
		//		sf::Vector2f(	playerAircraft_->getVelocity().x * -1, 
		//						playerAircraft_->getVelocity().y));
		//}
	}

	void World::adaptPlayerPosition()
	{
		const float BORDER_DISTANCE = 40.f;
		sf::FloatRect viewBounds(worldView_.getCenter() - worldView_.getSize() / 2.f, worldView_.getSize());

		sf::Vector2f position = playerAircraft_->getPosition();
		position.x = std::max(position.x, viewBounds.left + BORDER_DISTANCE);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - BORDER_DISTANCE);

		position.y = std::max(position.y, viewBounds.top + BORDER_DISTANCE);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - BORDER_DISTANCE);

		playerAircraft_->setPosition(position);
	}

	void World::adaptPlayerVelocity()
	{
		sf::Vector2f velocity = playerAircraft_->getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f)
			playerAircraft_->setVelocity(velocity / std::sqrt(2.f));
	}

	void World::addEnemies()
	{
		addEnemy(AircraftType::Raptor, -250.f, 200.f);
		addEnemy(AircraftType::Raptor, 0.f, 200.f);
		addEnemy(AircraftType::Raptor, 250.f, 200.f);

		addEnemy(AircraftType::Raptor, -250.f, 600.f);
		addEnemy(AircraftType::Raptor, 0.f, 600.f);
		addEnemy(AircraftType::Raptor, 250.f, 600.f);

		addEnemy(AircraftType::Avenger, -70.f, 400.f);
		addEnemy(AircraftType::Avenger, 70.f, 400.f);

		addEnemy(AircraftType::Avenger, -70.f, 800.f);
		addEnemy(AircraftType::Avenger, 70.f, 800.f);

		addEnemy(AircraftType::Avenger, -70.f, 850.f);
		addEnemy(AircraftType::Avenger, 70.f, 850.f);

		std::sort(enemySpawnPoints_.begin(), enemySpawnPoints_.end(), 
			[](SpawnPoint lhs, SpawnPoint rhs)
			{
				return lhs.y < rhs.y;
			});
	}

	void World::addEnemy(AircraftType type, float relX, float relY)
	{
		SpawnPoint spawnPoint(type, spawnPosition_.x - relX, spawnPosition_.y - relY);
		enemySpawnPoints_.push_back(spawnPoint);
	}

	void World::spawnEnemies()
	{
		while (!enemySpawnPoints_.empty() &&
			enemySpawnPoints_.back().y > getBattlefieldBounds().top)
		{
			auto spawnPoint = enemySpawnPoints_.back();
			std::unique_ptr<Aircraft> enemy(new Aircraft(spawnPoint.type, textures_));
			enemy->setPosition(spawnPoint.x, spawnPoint.y);
			enemy->setRotation(180);
			sceneLayer_[Air]->attachChild(std::move(enemy));
			enemySpawnPoints_.pop_back();
		}
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(worldView_.getCenter() - worldView_.getSize() / 2.f, worldView_.getSize());
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100.f;
		bounds.height += 100.f;
		return bounds;
	}

	void World::draw()
	{
		window_.setView(worldView_);
		window_.draw(sceneGraph_);
	}

	CommandQueue & World::getCommandQueue()
	{
		return commandQueue_;
	}

	void World::loadTextures()
	{
		textures_.load(GEX::TextureID::Airplane, "Media/Textures/Eagles.png");
		textures_.load(GEX::TextureID::Landscape, "Media/Textures/Desert.png");
		textures_.load(GEX::TextureID::Eagle, "Media/Textures/Eagle.png");
		textures_.load(GEX::TextureID::Raptor, "Media/Textures/Raptor.png");
		textures_.load(GEX::TextureID::Avenger, "Media/Textures/Avenger.png");
	}

	void World::buildScene()
	{
		// Initalize layers
		for (int i = 0; i < LayerCount; i++)
		{
			SceneNode::Ptr layer(new SceneNode());
			sceneLayer_.push_back(layer.get());
			sceneGraph_.attachChild(std::move(layer));
		}

		// background
		sf::Texture& texture = textures_.get(TextureID::Landscape);
		sf::IntRect textureRect(worldBounds_);
		texture.setRepeated(true);

		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
		sceneLayer_[Background]->attachChild(std::move(backgroundSprite));

		// add player aircraft & game objects
		std::unique_ptr<Aircraft> leader(new Aircraft(AircraftType::Eagle, textures_));
		leader->setPosition(spawnPosition_);
		leader->setVelocity(200.f, scrollSpeeds_);
		playerAircraft_ = leader.get();
		sceneLayer_[Air]->attachChild(std::move(leader));

		// add enemy aircraft
		addEnemies();
	}


}
