#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "InputState.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/CheckButton.hpp"


void call_me(bool t, void *user_data){
	std::string *text = (std::string *)user_data;
	if(t){
		std::cout << *text << ": T is true\n";
	}else{
		std::cout << *text << ": T is false\n";
	}
}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;
	sf::Text text("", font, 50);


	InputState::SetDefaultActionMapping();


	InputState::GetKeyForAction(ActionTypes::MoveLeft);
	InputState::GetKeyForAction(ActionTypes::MoveRight);
	InputState::GetKeyForAction(ActionTypes::MoveUp);
	InputState::GetKeyForAction(ActionTypes::MoveDown);
	InputState::GetKeyForAction(ActionTypes::Attack, true);

	sf::Texture texture;
	texture.loadFromFile("check.png");


	std::string text1 = "hello";
	Button button(text1, font, 100,100);
	button.SetSize(100,25);
	button.SetToggle(false);
	button.SetCallback(call_me, &text1);

	std::string text2 = "world";
	Button toggle_button("world!", font, 210,100);
	toggle_button.SetSize(100,25);
	toggle_button.SetToggle(true);
	toggle_button.SetCallback(call_me, &text2);

	std::string text3 = "I'm a toggle!";
	CheckButton check_button(text3, font, 100,135, texture);
	check_button.SetCallback(call_me, &text3);

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
			
			InputState::ProcessInput(event);


			button.ProcessInput(event);
			toggle_button.ProcessInput(event);
			check_button.ProcessInput(event);
		}
		// Clear screen
		window.clear();


		std::string str = "";

		if(InputState::GetAction(ActionTypes::MoveLeft))
			str="moving left!\n";
		else if(InputState::GetAction(ActionTypes::MoveRight))
			str="moving right!\n";
		else if(InputState::GetAction(ActionTypes::MoveUp))
			str="moving up!\n";
		else if(InputState::GetAction(ActionTypes::MoveDown))
			str="moving down!\n";
		
		if(InputState::GetAction(ActionTypes::Attack))
			std::cout << "attacked\n";

		text.setString(str);

		window.draw(text);

		button.Draw(window);
		toggle_button.Draw(window);
		check_button.Draw(window);

		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
