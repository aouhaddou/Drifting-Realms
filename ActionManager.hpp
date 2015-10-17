#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "ActionTypes.hpp"

class Widget;

class ActionManager{
public:
	static void Initialize();

	// maps a function to an associated action and up or down of the key, or GUI button
	static void MapActionToFunctionDown(ActionTypes action, const std::function<void ()> func);
	static void MapActionToFunctionUp(ActionTypes action, const std::function<void ()> func);

	// this maps a widget to an action so that the widget can be updated if a key is pressed.
	static void MapWidgetToAction(const ActionTypes action, Widget *widget);

	// The input manager and GUI buttons call these.
	// when called they - in turn - call the functions assigned in MapActionToFunctionDown
	// and MapActionToFunctionUp, and they update any associated GUI Widgets
	static void FireDown(ActionTypes action);
	static void FireUp(ActionTypes action);

private:
	static std::function<void ()> actions_down[]; // key pressed
	static std::function<void ()> actions_up[]; // key released

	static Widget *widgets[];
};