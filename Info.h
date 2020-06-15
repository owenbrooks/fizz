#pragma once
#include <SFML/Graphics.hpp>

class Info
{
public:
	Info();
	void setFont(sf::Font& font);
	void render(sf::RenderWindow& window);
	void update(float frameTime);
private:
	float currTime_ = 0.f;
	sf::Font font_;
	sf::Text text_;
};

