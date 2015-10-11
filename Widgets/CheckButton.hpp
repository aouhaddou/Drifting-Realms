#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Button.hpp"


#include <iostream>

class CheckButton : public Button{
public:
	CheckButton(std::string name, sf::Font& font, int loc_x, int loc_y, sf::Texture &check);
	virtual void ProcessInput(const sf::Event &event);
	virtual void Draw(sf::RenderWindow &window);
	virtual void SetPosition(int x, int y);
	virtual void UpdateTextLocation();
protected:
	sf::Sprite checkmark;
};
