#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Config.h"

class Info
{
public:
	Info();
	void setFont(sf::Font& font);
	void render(sf::RenderWindow& window);
	void update(float frameTime, const ConfigState& state, unsigned int objCount);
	void toggleHidden();
private:
	sf::Font font_;
	sf::Text text_;
	float currTime_ = 0.f;
	std::array<float, 100> frame_time_buf_;
	size_t frame_index_ = 0;
	float time_since_last_update = 0;
	bool hidden_ = true;
};

