#include "InputState.hpp"

bool InputState::action_types[(unsigned int)ActionTypes::Length];
bool InputState::action_types_single_fire[(unsigned int)ActionTypes::Length];
bool InputState::action_types_has_single_fired[(unsigned int)ActionTypes::Length];

std::map<ActionTypes, sf::Event> InputState::event_to_action_map;
std::vector<ActionTypes> InputState::parsing_actions;

// ugh, SFML must have a problem(or my keyboard...)
// it triggers a key release periodically when the key
// is still being held down, resulting in single_fire
// to not behave exactly correctly
const bool InputState::GetAction(ActionTypes option){
	if(IsGettingKeyMap() == true)
		return false;

	const bool return_me = action_types[(unsigned int)option];


	if(action_types_has_single_fired[(unsigned int)option] == true)
		return false;

	// if we do single fire, and we just hit the key,
	// set it so that 
	if(return_me && action_types_single_fire[(unsigned int)option] == true){
		action_types_has_single_fired[(unsigned int)option] = true;
	}





	return return_me;
}
void InputState::SetAction(ActionTypes option, bool state){
	action_types[(unsigned int)option] = state;
}




void InputState::SetDefaultActionMapping(){
	sf::Event event;
	sf::Event::KeyEvent key_event;
	event.type = sf::Event::KeyPressed;

	
	key_event.code = sf::Keyboard::Key::A;
	event.key = key_event;
	SetActionMapping(ActionTypes::MoveLeft, event);
	
	key_event.code = sf::Keyboard::Key::D;
	event.key = key_event;
	SetActionMapping(ActionTypes::MoveRight, event);
	
	key_event.code = sf::Keyboard::Key::W;
	event.key = key_event;
	SetActionMapping(ActionTypes::MoveUp, event);

	key_event.code = sf::Keyboard::Key::S;
	event.key = key_event;
	SetActionMapping(ActionTypes::MoveDown, event);

	key_event.code = sf::Keyboard::Key::Up;
	event.key = key_event;
	SetActionMapping(ActionTypes::Attack, event);
}

void InputState::SetActionMapping(ActionTypes action, const sf::Event &event, bool single_fire){
	event_to_action_map[action] = event;
}
sf::Event InputState::GetActionMapping(ActionTypes option){
	return event_to_action_map[option];
}
const bool InputState::IsGettingKeyMap(){
	return !parsing_actions.empty();
}

void InputState::GetKeyForAction(ActionTypes action, bool single_fire){
	parsing_actions.push_back(action);

	action_types_single_fire[(unsigned int)action] = single_fire;
}

void InputState::ProcessInput(const sf::Event &event){
	const int margin = 50;
	// are we assigning a key?
	if(IsGettingKeyMap() == true){
		if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
		{
			// assign the key to an action
			SetActionMapping(parsing_actions[0], event);
			// event_to_action_map[parsing_actions[0]] = event;
			// if we have a assign all keys at once thing
			// this can handle the chain
			parsing_actions.erase(parsing_actions.begin());
			return;
		}
	}
	// or are we looking for a key?
	else{
		// this is why auto is useful. would be
		// for(std::map<ActionTypes, sf::Event>::iterator = event_to_action_map.begin(); iterator != event_to_action_map.end(); iterator++) {
		for(auto iterator = event_to_action_map.begin(); iterator != event_to_action_map.end(); iterator++) {

			// ActionTypes map_action = iterator->first;
			// sf::Event map_event = iterator->second;
			CheckForEvent(event, iterator->first, iterator->second);

		}
	}
}


void InputState::CheckForEvent(const sf::Event &event, ActionTypes map_action, sf::Event map_event){
	if(map_event.type == sf::Event::KeyPressed){

		if(event.type == sf::Event::KeyPressed && map_event.key.code == event.key.code){
			SetAction(map_action, true);
			return;
		}
		else if(event.type == sf::Event::KeyReleased && map_event.key.code == event.key.code){
			SetAction(map_action, false);

			action_types_has_single_fired[(unsigned int)map_action] = false;
			return;
		}
	}

	else if(map_event.type == sf::Event::MouseButtonPressed){
		if(event.type == sf::Event::MouseButtonPressed && map_event.mouseButton.button == event.mouseButton.button){
			SetAction(map_action, true);
			return;
		}
		else if(event.type == sf::Event::MouseButtonReleased && map_event.mouseButton.button == event.mouseButton.button){
			SetAction(map_action, false);

			action_types_has_single_fired[(unsigned int)map_action] = false;
			return;
		}
	}
}