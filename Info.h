#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Info
{
public:
	Info();
	void setFont(sf::Font& font);
	void render(sf::RenderWindow& window);
	void update(float frameTime);
private:
	float currTime_ = 0.f;
	std::array<float, 100> frame_time_buf_;
	size_t frame_index_;
	sf::Font font_;
	sf::Text text_;
};

