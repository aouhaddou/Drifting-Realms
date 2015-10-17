#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <functional>
#include "Widget.hpp"

class Button : public Widget{
public:
	Button(std::string name, sf::Font& font, int loc_x, int loc_y);
	virtual void Draw(sf::RenderWindow &window);
	virtual void SetPosition(int x, int y);
	void SetText(const sf::String& name);

	// sets the width and height
	void SetSize(int w, int h);

	virtual bool ProcessInput(const sf::Event &event);

	virtual void SetAcionDownState();
	virtual void SetAcionUpState();

	void UpdateColors();

	bool GetIsClicked(){
		return state_clicked;
	}
	void SetToggle(bool toggle){
		is_toggle_button = toggle;
	}
protected:
	void SetNormalColors();
	void SetHoveringColors();
	void SetClickedColors();

	sf::RectangleShape rectangle;
	sf::Text text;
	virtual void UpdateTextLocation();

	bool state_hovering = false;
	bool state_clicked = false;
	bool is_toggle_button = false;

};
