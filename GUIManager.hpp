#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "Widgets/Button.hpp"
#include "Widgets/CheckButton.hpp"
#include "ActionTypes.hpp"

struct WidgetList{
	Widget *widget;
	WidgetList *next = nullptr;
};


class GUIManager{
public:
	static void Initialize();
	static void Finalize();

	static bool ProcessInput(const sf::Event &event);
	static void Draw(sf::RenderWindow &window);

	static Button *MakeButton(std::string title, int x, int y, int w, int h);
	static Button *MakeToggleButton(std::string title, int x, int y, int w, int h);
	static CheckButton *MakeCheckButton(std::string title, int x, int y);

private:

	static WidgetList *widget_list;
	static WidgetList *widget_list_last;

	static sf::Font font;
	static sf::Texture check_mark_texture;
};