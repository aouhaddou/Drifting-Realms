#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <functional>
#include "../ActionTypes.hpp"
#include "../ActionManager.hpp"

class Widget{
public:
	virtual void Draw(sf::RenderWindow &window) = 0;

	// process input.
	// if this returns true it means something happened,
	// so that the input isn't processed any further
	virtual bool ProcessInput(const sf::Event &event) = 0;

	// called by ActionManager telling the widget
	// that a key connected to the same action
	// has been used.
	virtual void SetAcionDownState() = 0;
	virtual void SetAcionUpState() = 0;

	void SetAction(ActionTypes _action){
		action = _action;
	}
protected:
	sf::Color GetNormalFill(){
		return sf::Color(150, 50, 250);
	}
	sf::Color GetNormalOutline(){
		return sf::Color(250, 150, 100);
	}

	sf::Color GetHoveringFill(){
		return sf::Color(200, 100, 250);
	}
	sf::Color GetHoveringOutline(){
		return GetNormalOutline();
	}

	sf::Color GetClickedFill(){
		return sf::Color(255, 0, 0);
	}
	sf::Color GetClickedOutline(){
		return GetNormalOutline();
	}

	ActionTypes action;
};
