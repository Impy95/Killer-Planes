#include "TextNode.h"
#include "Utility.h"

GEX::TextNode::TextNode(std::string & text)
{
	// text_.setFont();
	text_.setCharacterSize(20);
	setText(text);
}

void GEX::TextNode::setText(const std::string & text)
{
	text_.setString(text);
	centerOrigin(text_);
}

void GEX::TextNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
}
