#include "Button.hpp"

Button::Button(std::string name, sf::Font& font, int loc_x, int loc_y){
	SetPosition(loc_x, loc_y);
	rectangle.setOutlineThickness(2);

	SetNormalColors();

	text = sf::Text();
	text.setFont(font);

	SetText(name);
}

void Button::SetPosition(int x, int y){
	rectangle.setPosition (x, y);
	UpdateTextLocation();
}

void Button::SetText(std::string name){
	text.setString(name);
	UpdateTextLocation();
}

void Button::Draw(sf::RenderWindow &window){
	window.draw(rectangle);
	window.draw(text);
}

void Button::SetSize(int w, int h){
	rectangle.setSize (sf::Vector2f(w,h));
	UpdateTextLocation();
}

void Button::UpdateTextLocation(){
	// ------------------centered:
	/*
	// set text size to height of button
	text.setCharacterSize (rectangle.getSize().y);

	// set text origin to its center
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left,
	               textRect.top  + textRect.height/2.0f);




	// place the text into the center of the button
	const int loc_x  = rectangle.getPosition().x;
	const int loc_y  = rectangle.getPosition().y;
	const int width  = rectangle.getSize().x;
	const int height = rectangle.getSize().y;

	// 2 to account for border and 3 more for padding
	text.setPosition(loc_x+width+5,loc_y+(height/2));*/


	// ------------------aligned left:

	// set text size to height of button
	text.setCharacterSize (rectangle.getSize().y);

	// set text origin to its center
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left,
	               textRect.top  + textRect.height/2.0f);




	// place the text into the center of the button
	const int loc_x  = rectangle.getPosition().x;
	const int loc_y  = rectangle.getPosition().y;
	const int width  = rectangle.getSize().x;
	const int height = rectangle.getSize().y;

	// 2 to account for border and 3 more for padding
	text.setPosition(loc_x+5,loc_y+(height/2));
}



void Button::ProcessInput(const sf::Event &event){
	if(event.type == sf::Event::MouseButtonPressed){
		if(rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){

			if(is_toggle_button)
				state_clicked = !state_clicked;
			else
				state_clicked = true;

			if(callback != nullptr)
				callback(state_clicked,user_data);
		}
	}
	else if(event.type == sf::Event::MouseButtonReleased){
		if(!is_toggle_button)
			state_clicked = false;
	}

	if(event.type == sf::Event::MouseMoved){
		if(rectangle.getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y))
			state_hovering = true;
		else
			state_hovering = false;
	}


	// set the appropriate colors
	if(state_clicked)
		SetClickedColors();
	else if(state_hovering)
		SetHoveringColors();
	else
		SetNormalColors();

}



void Button::SetNormalColors(){
	rectangle.setFillColor(sf::Color(150, 50, 250));
	rectangle.setOutlineColor(sf::Color(250, 150, 100));
}
void Button::SetHoveringColors(){
	rectangle.setFillColor(sf::Color(200, 100, 250));
	rectangle.setOutlineColor(sf::Color(250, 150, 100));
}
void Button::SetClickedColors(){
	rectangle.setFillColor(sf::Color(255, 0, 0));
	rectangle.setOutlineColor(sf::Color(250, 150, 100));
}