#pragma once
#include <SFML/Graphics.hpp>
constexpr float defaultObjRestitution = 0.8f;
constexpr float defaultBoundaryResitution = 0.8f;
constexpr float defaultGravity = 0.003f;
constexpr float defaultBallRadius = 25.f;
constexpr size_t maxChars = 17;
struct ConfigState
{
	float objRestitution = defaultObjRestitution;
	float boundaryRestitution = defaultBoundaryResitution;
	float gravity = defaultGravity;
	float ballRadius = defaultBallRadius;
	bool gravityEnabled = false;
	bool topWallEnabled = true;
};
class Config
{
public:
	void render(sf::RenderWindow& window);
	void update();
	const ConfigState& getState();
	void handleEvent(sf::Event& event);
	void setFont(sf::Font& font);
	const bool isActive();
	void showCommandBox();
	void executeCommand();
	inline void toggleGravity() { state_.gravityEnabled = !state_.gravityEnabled; };
	inline void toggleTopWall() { state_.topWallEnabled = !state_.topWallEnabled; };
private:
	sf::RenderWindow window_;
	ConfigState state_;
	sf::Clock clock_;
	bool active_ = false;
	std::string commandStr_;
	sf::Text commandText_;
	sf::RectangleShape caretRect_;
	bool caretVisible_ = true;
	size_t caretIndex_ = 0;
};

