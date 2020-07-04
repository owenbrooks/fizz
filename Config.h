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
	bool gravityEnabled = true;
	bool topWallEnabled = false;
};
class Config
{
public:
	void render(sf::RenderWindow& window);
	void showCommandBox();
	void executeCommand();
	const bool isActive();
	const ConfigState& getState();
	void handleEvent(sf::Event& event);
	void setFont(sf::Font& font);
	void update();
	inline void toggleGravity() { state_.gravityEnabled = !state_.gravityEnabled; };
	inline void toggleTopWall() { state_.topWallEnabled = !state_.topWallEnabled; };
private:
	bool active_ = false;
	sf::RenderWindow window_;
	ConfigState state_;
	std::string commandStr_;
	sf::Text commandText_;
	sf::RectangleShape caretRect_;
	bool caretVisible_ = true;
	size_t caretIndex_ = 0;
	sf::Clock clock_;
	bool inErrorState_ = false;
};

