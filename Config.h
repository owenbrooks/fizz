#pragma once
#include <SFML/Graphics.hpp>
constexpr float defaultObjRestitution = 0.8;
constexpr float defaultBoundaryResitution = 0.8;
struct ConfigState
{
	float objRestitution = defaultObjRestitution;
	float boundaryRestitution = defaultBoundaryResitution;
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
	void update(float deltaTime);
private:
	bool _active = false;
	sf::RenderWindow _window;
	ConfigState _state;
	std::string _commandStr;
	sf::Text _commandText;
	sf::RectangleShape _caretRect;
	bool _caretVisible = true;
	size_t _caretIndex;
	sf::Clock _clock;
	bool _inErrorState = false;
};

