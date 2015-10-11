#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


enum class ActionTypes : unsigned int{
	MoveLeft = 0,
	MoveRight,
	MoveUp,
	MoveDown,
	Attack,
	Length
};



// InputState is a static object which allows easy keymapping.
// InputState intentionally uses buffered inputs which means that
// if the game freezes and the user holds the left arrow key,
// he will unfreeze far to the left(hopefully out of harms way).
// I don't think unbufferd input garuntees this.

// todo: add a should pause callback which is called whenever a used
// input device is unplugged
class InputState{
public:
	// is an action currently supposed to be happening?
	// returns true if the key correlated to that action if
	// being held down, and will continue to return true until
	// it is released. It only returns true initially if it
	// had single_fire on initiation
	static const bool GetAction(ActionTypes option);

	// sets a default key mapping. when the config file cannot
	// be found, or is corrupt, these actions can be saved to it.
	static void SetDefaultActionMapping();

	// manually set an event to an action(see SetDefaultActionMapping for example)
	// this will be used to load from a config file.
	// single_fire acts just like in GetKeyForAction
	static void SetActionMapping(ActionTypes action, const sf::Event &event, bool single_fire = false);

	// get a event correlated to an action
	// this will be used to save a config file
	static sf::Event GetActionMapping(ActionTypes option);

	// are any GetKeyForActions waiting for a key? if so, return true.
	static const bool IsGettingKeyMap();

	// this will wait for a key to be called, then assign action to it.
	// single_fire affects the way GetAction works.
	// if this is called many times, it will wait for the approprate
	// amount of keys and assign them in proper order.
	static void GetKeyForAction(ActionTypes action, bool single_fire = false);

	// process input currently cannot handle analog sticks
	static void ProcessInput(const sf::Event &event);

private:
	static bool action_types[];
	static bool action_types_single_fire[];
	static bool action_types_has_single_fired[];

	static std::map<ActionTypes, sf::Event> event_to_action_map;


	static std::vector<ActionTypes> parsing_actions;

	// a helper function for ProcessInput.
	static void CheckForEvent(const sf::Event &event, ActionTypes map_action, sf::Event map_event);

	// sets whether an action is happening or not
	static void SetAction(ActionTypes option, bool state);
};