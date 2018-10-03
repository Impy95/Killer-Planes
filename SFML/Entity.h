//
// Entity.h
//

#pragma once
#include "SceneNode.h"

namespace GEX {
	class Entity : public SceneNode
	{
	public:
		explicit		Entity(int points);

		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		sf::Vector2f	getVelocity() const;

		void			accelerate(sf::Vector2f velocity);
		void			accelerate(float vx, float vy);

		int				getHitPoints() const;
		void			damage(int points);
		void			repair(int points);
		void			destroy();
		virtual bool	isDestroyed() const;

	private:
		virtual void	updateCurrent(sf::Time dt);

	private:
		sf::Vector2f	velocity_;
		int				hitPoints_;
	};
}

