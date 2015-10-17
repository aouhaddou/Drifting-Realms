#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "ActionTypes.hpp"
#include "ActionManager.hpp"


// InputManager is a static object which allows easy keymapping.
// InputManager intentionally uses buffered inputs which means that
// if the game freezes and the user holds the left arrow key,
// he will unfreeze far to the left(hopefully out of harms way).
// I don't think unbufferd input garuntees this.

// todo: add a should pause callback which is called whenever a used
// input device is unplugged
class InputManager{
public:
	// sets a default key mapping. when the config file cannot
	// be found, or is corrupt, these actions can be saved to it.
	static void SetDefaultActionMapping();

	static void Initialize();

	// are any GetKeyForActions waiting for a key? if so, return true.
	static const bool IsGettingKeyMap();

	// this will wait for a key to be called, then assign action to it.
	// if this is called many times, it will wait for the approprate
	// amount of keys and assign them in proper order.
	static void BindKeyToAction(ActionTypes action);

	static void ProcessInput(const sf::Event &event);

private:
	static bool action_types[];

	static std::map<ActionTypes, sf::Event> event_to_action_map;
	static bool key_has_gone_up[];


	static std::vector<ActionTypes> parsing_actions;

	// a helper function for ProcessInput.
	static void CheckForEvent(const sf::Event &event, ActionTypes map_action, sf::Event map_event);
};