#include "SceneNode.h"
#include "Category.h"
#include "Command.h"
#include <algorithm>
#include <cassert>

namespace GEX {
	SceneNode::SceneNode()
		: children_(),
		parent_(nullptr)
	{
	}


	SceneNode::~SceneNode()
	{
	}

	void SceneNode::attachChild(Ptr child)
	{
		child->parent_ = this;
		children_.push_back(std::move(child));
	}

	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
	{
		auto found = std::find_if(children_.begin(), children_.end(), [&](Ptr& p) {return &node == p.get(); });
		assert(found != children_.end());

		Ptr result = std::move(*found);
		children_.erase(found);

		return result;
	}

	void SceneNode::update(sf::Time dt)
	{
		updateCurrent(dt);
		updateChildren(dt);
	}

	void SceneNode::onCommand(const Command& command, sf::Time dt)
	{
		// Command current node
		if (command.category & getCategory())
			command.action(*this, dt);

		// Command children
		for (Ptr& child : children_)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const
	{
		return Category::Type::None;
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;

		for (const SceneNode* node = this; node != nullptr; node = node->parent_)
			transform = node->getTransform() * transform;

		return transform;
	}

	void SceneNode::updateCurrent(sf::Time dt)
	{
		// default do nothing
	}

	void SceneNode::updateChildren(sf::Time dt)
	{
		for (Ptr& child : children_)
			child->update(dt);
	}

	void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// default to do nothing
	}

	void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Ptr& child : children_)
		{
			child->draw(target, states);
		}
	}


	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		drawCurrent(target, states);
		drawChildren(target, states);
	}

}
