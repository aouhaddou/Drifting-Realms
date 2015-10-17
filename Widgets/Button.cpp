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

void Button::SetText(const sf::String& name){
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

void Button::SetAcionDownState(){
	if(is_toggle_button)
		state_clicked = !state_clicked;
	else
		state_clicked = true;

	UpdateColors();
}
void Button::SetAcionUpState(){
	if(!is_toggle_button)
		state_clicked = false;

	UpdateColors();
}


bool Button::ProcessInput(const sf::Event &event){
	static bool was_just_clicked = false;
	bool return_me = false;
	if(event.type == sf::Event::MouseButtonPressed){
		if(rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){

			// calls calls a correlated function to this button
			// which ends up calling SetAcionDownState().
			ActionManager::FireDown(action);

			was_just_clicked = true;
			return_me = true;
		}
	}
	else if(event.type == sf::Event::MouseButtonReleased){
		// in the event that the button was clicked,
		// we do not want to let a mouse up signal escape
		if(was_just_clicked){
			return_me = true;
			was_just_clicked = false;
			ActionManager::FireUp(action);
		}

	}

	if(event.type == sf::Event::MouseMoved){
		if(rectangle.getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y))
			state_hovering = true;
		else
			state_hovering = false;
	}

	Button::UpdateColors();

	return return_me;
}

void Button::UpdateColors(){
	if(state_clicked)
		SetClickedColors();
	else if(state_hovering)
		SetHoveringColors();
	else
		SetNormalColors();
}



void Button::SetNormalColors(){
	rectangle.setFillColor(GetNormalFill());
	rectangle.setOutlineColor(GetNormalOutline());
}
void Button::SetHoveringColors(){
	rectangle.setFillColor(GetHoveringFill());
	rectangle.setOutlineColor(GetHoveringOutline());
}
void Button::SetClickedColors(){
	rectangle.setFillColor(GetClickedFill());
	rectangle.setOutlineColor(GetClickedOutline());
}