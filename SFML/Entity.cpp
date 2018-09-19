#include "Entity.h"



namespace GEX {

	void GEX::Entity::setVelocity(sf::Vector2f velocity)
	{
		velocity_ = velocity;
	}

	void GEX::Entity::setVelocity(float vx, float vy)
	{
		velocity_.x = vx;
		velocity_.y = vy;
	}

	sf::Vector2f GEX::Entity::getVelocity() const
	{
		return velocity_;
	}

	void GEX::Entity::updateCurrent(sf::Time dt)
	{
		move(velocity_ * dt.asSeconds());
	}

}
