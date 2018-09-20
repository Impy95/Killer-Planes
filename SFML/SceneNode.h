#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <memory>



namespace GEX
{
	// forward declaration
	struct Command;
	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
	public:
								SceneNode();
		virtual					~SceneNode();

								SceneNode(const SceneNode&) = delete;
		SceneNode&				operator=(SceneNode&) = delete;

		void					attachChild(Ptr child);
		Ptr						detachChild(const SceneNode& ptr);

		void					update(sf::Time dt);
		void					onCommand(const Command& command, sf::Time dt);
		virtual unsigned int	getCategory() const;

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;

	private:
		// update the tree
		virtual void			updateCurrent(sf::Time dt);
		void					updateChildren(sf::Time dt);

		// draw the tree
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		SceneNode*				parent_;
		std::vector<Ptr>		children_;
	};
}

