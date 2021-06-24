// Displays current fps and configuration parameters (e.g. strength of gravity) in text on screen
#include "Info.h"
#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iomanip>

Info::Info() : font_(), text_(), 
frame_time_buf_({ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f })
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
	if (!hidden_) {
		window.draw(text_);
	}
}
void Info::toggleHidden()
{
	hidden_ = !hidden_;
}
void Info::update(float frameTime, const ConfigState& state, unsigned int obj_count)
{
	// calculate rolling average of the frameTime
	frame_time_buf_[frame_index_] = frameTime;
	if (frame_index_ < frame_time_buf_.size() - 1) {
		frame_index_++;
	}
	else {
		frame_index_ = 0;
	}

	// Early return so that strings are not recreated every update
	constexpr float update_threshold = 1.f;
	time_since_last_update += frameTime;
	if (time_since_last_update < update_threshold) {
		return;
	}
	time_since_last_update = 0;

	float avg_frame_time = std::accumulate(frame_time_buf_.begin(), frame_time_buf_.end(), 0.f)/frame_time_buf_.size();

	float fps = 1.f / avg_frame_time;
	std::stringstream fps_string;
	fps_string << "fps: " << std::fixed << std::setprecision(1) << fps;

	std::string obj_count_str = "obj count: " + std::to_string(obj_count);

	std::stringstream obj_obj_restitution_str;
	obj_obj_restitution_str << "obj->obj: " << std::fixed << std::setprecision(2) << state.objRestitution;
	
	std::stringstream obj_bound_restitution_str;
	obj_bound_restitution_str << "obj->bndry: " << std::fixed << std::setprecision(2) << state.boundaryRestitution;

	std::stringstream gravity_str;
	gravity_str << "gravity: " << std::fixed << std::setprecision(8) << state.gravity;

	std::stringstream obj_radius;
	obj_radius << "radius: " << std::fixed << std::setprecision(2) << state.ballRadius;

	text_.setString(obj_count_str + '\n' + 
		fps_string.str() + '\n' + 
		obj_obj_restitution_str.str() + '\n' + 
		obj_bound_restitution_str.str() + '\n' +
		gravity_str.str() + '\n' +
		obj_radius.str()
	);
}
