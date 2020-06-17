#include "Config.h"
void Config::render(sf::RenderWindow& window)
{
	if (_active)
	{
		const auto windowSize = window.getSize();
		sf::Vector2f rectSize(windowSize.x * 0.2f, 100.f);
		sf::RectangleShape rectangle(sf::Vector2f(rectSize.x, rectSize.y));
		sf::Vector2f rectPos((windowSize.x - rectSize.x) / 2, (windowSize.y * 0.4f - rectSize.y) / 2);
		rectangle.setPosition(rectPos);
		rectangle.setFillColor(sf::Color(250, 150, 0, 15));
		rectangle.setOutlineThickness(5.f);
		rectangle.setOutlineColor(sf::Color(250, 150, 100));
		_commandText.setPosition(rectPos.x, rectPos.y + 10.f);

		if (_caretVisible && _commandStr.size() <= 17) {
			sf::RectangleShape caretRect(sf::Vector2f(rectSize.x / 17, rectSize.y));
			const int caretIndex = _commandStr.size();
			sf::Vector2f caretPos = rectPos + sf::Vector2f(caretIndex * rectSize.x / 17, 0.f);
			caretRect.setPosition(caretPos);
			caretRect.setFillColor(sf::Color(255, 255, 255, 30));
			window.draw(caretRect);
		}

		window.draw(rectangle);
		window.draw(_commandText);
	}
}
void Config::update(float deltaTime)
{
	unsigned int millis = _clock.getElapsedTime().asMilliseconds();
	if (millis > 500) {
		_caretVisible = !_caretVisible;
		_clock.restart();
	}
}
const ConfigState& Config::getState()
{
	return _state;
}
void Config::showCommandBox()
{
	_active = true;
}
void Config::executeCommand()
{
	std::string propertyName;
	std::string newValueStr;
	size_t pos = _commandStr.find(" ");
	if (pos != std::string::npos) {
		propertyName = _commandStr.substr(0, pos);
		newValueStr = _commandStr.substr(pos + 1);
		if (propertyName == "ob") {
			try {
				float newValue = std::stof(newValueStr);
				_state.objRestitution = newValue;
			}
			catch (std::invalid_argument& e) {
				_inErrorState = true;
			}
		}
	}
	_active = false;
	_commandStr.clear();
}
const bool Config::isActive()
{
	return _active;
}
void Config::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		constexpr size_t maxChars = 17;
		if (event.text.unicode == '\b') {
			if (_commandStr.size() > 0) { 
				_commandStr.pop_back();
			}

		}
		else if (_commandStr.size() < maxChars && event.text.unicode != ':') {
			_commandStr += static_cast<char>(event.text.unicode);
		}
		_commandText.setString(_commandStr);
	}
}
void Config::setFont(sf::Font& font)
{
	_commandText.setFont(font);
	_commandText.setCharacterSize(50);
	_commandText.setFillColor(sf::Color::White);
	_commandText.setOutlineColor(sf::Color::White);
}

