#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "InputManager.hpp"
#include "GUIManager.hpp"


void call_me(){
	std::cout << "call_me()\n";
}
void up(){

	std::cout << "UP!\n";
}


class Dummy{
public:
	Dummy(sf::Font &font){
		text = sf::Text("", font, 50);
	}
	void Draw(sf::RenderWindow &window){
		window.draw(text);
	}
	void print1(){
		std::cout << "d" << i++ << "\n";
		text.setString("down!");
	}
	void print2(){
		std::cout << "u" << i++ << "\n";
		text.setString("up!");
	}
protected:
	int i = 0;
	sf::Text text;
};



int main()
{





	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;


	Dummy *dummy = new Dummy(font);

	InputManager::Initialize();
	GUIManager::Initialize();
	ActionManager::Initialize();
	InputManager::SetDefaultActionMapping();


	ActionManager::MapActionToFunctionDown(ActionTypes::MoveLeft, std::bind(&Dummy::print1, dummy));
	ActionManager::MapActionToFunctionUp(ActionTypes::MoveLeft, std::bind(&Dummy::print2, dummy));

	ActionManager::MapActionToFunctionDown(ActionTypes::MoveRight, std::bind(&Dummy::print1, dummy));
	ActionManager::MapActionToFunctionUp(ActionTypes::MoveRight, std::bind(&Dummy::print2, dummy));



	InputManager::BindKeyToAction(ActionTypes::MoveLeft);
	InputManager::BindKeyToAction(ActionTypes::MoveRight);






	Button *button = GUIManager::MakeButton("left", 100,100, 100,25);
	ActionManager::MapWidgetToAction(ActionTypes::MoveLeft, button);

	// Button *toggle_button = GUIManager::MakeToggleButton("world!", 210,100,100,25);
	// toggle_button->SetCallback(std::function<void ()>(call_me));

	CheckButton *check_button = GUIManager::MakeCheckButton("I'm a toggle!", 100,135);
	ActionManager::MapWidgetToAction(ActionTypes::MoveRight, check_button);

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
			
			if(!GUIManager::ProcessInput(event))
				InputManager::ProcessInput(event);

		}
		// Clear screen
		window.clear();


		dummy->Draw(window);
		GUIManager::Draw(window);

		// Update the window
		window.display();
	}



	delete dummy;

	GUIManager::Finalize();

	return EXIT_SUCCESS;
}
