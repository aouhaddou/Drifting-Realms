#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class Button{
public:
	Button(std::string name, sf::Font& font, int loc_x, int loc_y);
	virtual void Draw(sf::RenderWindow &window);
	virtual void SetPosition(int x, int y);
	void SetText(std::string name);

	// sets the width and height
	void SetSize(int w, int h);

	virtual void ProcessInput(const sf::Event &event);


	bool GetIsClicked(){
		return state_clicked;
	}
	void SetCallback(void (*_callback)(bool, void *), void *_user_data = nullptr){
		callback = _callback;
		user_data = _user_data;
	}
	void SetToggle(bool toggle){
		is_toggle_button = toggle;
	}
protected:
	sf::RectangleShape rectangle;
	sf::Text text;
	virtual void UpdateTextLocation();

	void SetNormalColors();
	void SetHoveringColors();
	void SetClickedColors();

	bool state_hovering = false;
	bool state_clicked = false;
	bool is_toggle_button = false;

	void (*callback)(bool, void *) = nullptr;
	void *user_data = nullptr;

};
