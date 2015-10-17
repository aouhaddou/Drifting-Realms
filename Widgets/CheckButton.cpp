#include "CheckButton.hpp"


CheckButton::CheckButton(std::string name, sf::Font& font, int loc_x, int loc_y, sf::Texture &check) : Button(name, font, loc_x, loc_y){
	rectangle.setOutlineThickness(2);
	SetSize(20,20);
	SetToggle(true);

	checkmark.setTexture(check);
	SetPosition(loc_x,loc_y);
}

void CheckButton::SetPosition(int x, int y){
	Button::SetPosition(x,y);
	checkmark.setPosition(x,y-16);
}

bool CheckButton::ProcessInput(const sf::Event &event){
	return Button::ProcessInput(event);
}


void CheckButton::UpdateTextLocation(){
	
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

	// 2 to account for border and 4 more for padding
	text.setPosition(loc_x+width+6,loc_y+(height/2));
}

void CheckButton::Draw(sf::RenderWindow &window){
	Button::Draw(window);
	if(state_clicked)
		window.draw(checkmark);
}