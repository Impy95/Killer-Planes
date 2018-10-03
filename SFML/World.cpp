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

	void World::update(sf::Time dt)
	{
		// scroll the world
		worldView_.move(0.f, scrollSpeeds_ * dt.asSeconds());

		playerAircraft_->setVelocity(0.f, 0.f);

		// run all the commands in the command queue
		while (!commandQueue_.isEmpty())
			sceneGraph_.onCommand(commandQueue_.pop(), dt);

		adaptPlayerVelocity();
		sceneGraph_.update(dt);
		adaptPlayerPosition();

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

		// add escort planes
		std::unique_ptr<Aircraft> leftEscort(new Aircraft(AircraftType::Avenger, textures_));
		leftEscort->setPosition(-80.f, 50.f);
		playerAircraft_->attachChild(std::move(leftEscort));

		std::unique_ptr<Aircraft> rightEscort(new Aircraft(AircraftType::Raptor, textures_));
		rightEscort->setPosition(80.f, 50.f);
		playerAircraft_->attachChild(std::move(rightEscort));

		// add enemy aircraft
		std::unique_ptr<Aircraft> enemy(new Aircraft(AircraftType::Avenger, textures_));
		enemy->setPosition(spawnPosition_.x - 100.f, spawnPosition_.y - 600.f);
		enemy->setVelocity(0.f, -scrollSpeeds_);
		enemy->setRotation(180);
		sceneLayer_[Air]->attachChild(std::move(enemy));

		enemy = std::unique_ptr<Aircraft>(new Aircraft(AircraftType::Raptor, textures_));
		enemy->setPosition(spawnPosition_.x - 100.f, spawnPosition_.y - 600.f);
		enemy->setVelocity(50.f, -scrollSpeeds_);
		enemy->setRotation(180);
		sceneLayer_[Air]->attachChild(std::move(enemy));

		enemy = std::unique_ptr<Aircraft>(new Aircraft(AircraftType::Eagle, textures_));
		enemy->setPosition(spawnPosition_.x - 100.f, spawnPosition_.y - 600.f);
		enemy->setVelocity(25.f, -scrollSpeeds_);
		enemy->setRotation(180);
		sceneLayer_[Air]->attachChild(std::move(enemy));
	}


}
