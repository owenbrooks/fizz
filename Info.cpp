#include "Info.h"
#include <iostream>
Info::Info() : font_(), text_()
{
}
void Info::setFont(sf::Font& font)
{
	text_.setFont(font);
	text_.setCharacterSize(50);
	text_.setFillColor(sf::Color::White);
	text_.setOutlineColor(sf::Color::White);
	text_.setPosition(50.f, 50.f);
	text_.setString("frameTime: ");
}
void Info::render(sf::RenderWindow& window)
{
	window.draw(text_);
}
void Info::update(float frameTime)
{
	text_.setString(std::string("fps: ") + std::to_string(1.f/frameTime));
}
