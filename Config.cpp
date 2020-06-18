#include "Config.h"
#include <iostream>
void Config::render(sf::RenderWindow& window)
{
	if (active_)
	{
		const auto windowSize = window.getSize();
		sf::Vector2f rectSize(windowSize.x * 0.2f, 100.f);
		sf::RectangleShape rectangle(sf::Vector2f(rectSize.x, rectSize.y));
		sf::Vector2f rectPos((windowSize.x - rectSize.x) / 2, (windowSize.y * 0.4f - rectSize.y) / 2);
		rectangle.setPosition(rectPos);
		rectangle.setFillColor(sf::Color(250, 150, 0, 15));
		rectangle.setOutlineThickness(5.f);
		rectangle.setOutlineColor(sf::Color(250, 150, 100));
		commandText_.setPosition(rectPos.x, rectPos.y + 10.f);

		if (caretVisible_ && commandStr_.size() < maxChars) { // don't show caret if command box is full
			sf::RectangleShape caretRect(sf::Vector2f(rectSize.x / maxChars, rectSize.y));
			const int caretIndex = commandStr_.size();
			sf::Vector2f caretPos = rectPos + sf::Vector2f(caretIndex * rectSize.x / maxChars, 0.f);
			caretRect.setPosition(caretPos);
			caretRect.setFillColor(sf::Color(255, 255, 255, 30));
			window.draw(caretRect);
		}

		window.draw(rectangle);
		window.draw(commandText_);
	}
}
void Config::update()
{
	unsigned int millis = clock_.getElapsedTime().asMilliseconds();
	if (millis > 500) {
		caretVisible_ = !caretVisible_;
		clock_.restart();
	}
}
const ConfigState& Config::getState()
{
	return state_;
}
void Config::showCommandBox()
{
	active_ = true;
}
void Config::executeCommand()
{
	std::string propertyName;
	std::string newValueStr;
	size_t pos = commandStr_.find(" ");
	if (pos != std::string::npos) {
		propertyName = commandStr_.substr(0, pos);
		newValueStr = commandStr_.substr(pos + 1);
		if (propertyName == "ob") {
			try {
				float newValue = std::stof(newValueStr);
				state_.objRestitution = newValue;
			}
			catch (std::invalid_argument& e) {
				inErrorState_ = true;
				std::cout << e.what();
			}
		}
	}
	active_ = false;
	commandStr_.clear();
}
const bool Config::isActive()
{
	return active_;
}
void Config::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b') {
			if (commandStr_.size() > 0) { 
				commandStr_.pop_back();
			}
		}
		else if (commandStr_.size() < maxChars && event.text.unicode != ':') {
			commandStr_ += static_cast<char>(event.text.unicode);
		}
		commandText_.setString(commandStr_);
	}
}
void Config::setFont(sf::Font& font)
{
	commandText_.setFont(font);
	commandText_.setCharacterSize(50);
	commandText_.setFillColor(sf::Color::White);
	commandText_.setOutlineColor(sf::Color::White);
}

