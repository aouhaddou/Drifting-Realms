#include "InputManager.hpp"

bool InputManager::action_types[(unsigned int)ActionTypes::Length];
bool InputManager::key_has_gone_up[(unsigned int)ActionTypes::Length];

std::map<ActionTypes, sf::Event> InputManager::event_to_action_map;
std::vector<ActionTypes> InputManager::parsing_actions;


void InputManager::Initialize(){
	for(int i = 0;i < (unsigned int)ActionTypes::Length;i++){
		key_has_gone_up[i] = true;
	}
}


void InputManager::SetDefaultActionMapping(){
	sf::Event event;
	sf::Event::KeyEvent key_event;
	event.type = sf::Event::KeyPressed;

	
	key_event.code = sf::Keyboard::Key::A;
	event.key = key_event;
	event_to_action_map[ActionTypes::MoveLeft] = event;
	
	key_event.code = sf::Keyboard::Key::D;
	event.key = key_event;
	event_to_action_map[ActionTypes::MoveRight] = event;
	
	key_event.code = sf::Keyboard::Key::W;
	event.key = key_event;
	event_to_action_map[ActionTypes::MoveUp] = event;

	key_event.code = sf::Keyboard::Key::S;
	event.key = key_event;
	event_to_action_map[ActionTypes::MoveDown] = event;

	key_event.code = sf::Keyboard::Key::Up;
	event.key = key_event;
	event_to_action_map[ActionTypes::Attack] = event;
}

const bool InputManager::IsGettingKeyMap(){
	return !parsing_actions.empty();
}

void InputManager::BindKeyToAction(ActionTypes action){
	parsing_actions.push_back(action);
}

void InputManager::ProcessInput(const sf::Event &event){

	// are we assigning a key?
	if(IsGettingKeyMap() == true){
		if(event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
		{
			// assign the key to an action
			event_to_action_map[parsing_actions[0]] = event;

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


void InputManager::CheckForEvent(const sf::Event &event, ActionTypes map_action, sf::Event map_event){
	// we call return when we find a favorable outcome because this only gets
	// called once per event so not returning would make absolutely no sense

	if(map_event.type == sf::Event::KeyReleased){

		if(event.type == sf::Event::KeyPressed && map_event.key.code == event.key.code){
			if(key_has_gone_up[(unsigned int)map_action]){
				ActionManager::FireDown(map_action);
				key_has_gone_up[(unsigned int)map_action] = false;
			}
			return;
		}
		else if(event.type == sf::Event::KeyReleased && map_event.key.code == event.key.code){
			ActionManager::FireUp(map_action);
			key_has_gone_up[(unsigned int)map_action] = true;
			return;
		}
	}

	else if(map_event.type == sf::Event::MouseButtonReleased){
		if(event.type == sf::Event::MouseButtonPressed && map_event.mouseButton.button == event.mouseButton.button){
			if(key_has_gone_up[(unsigned int)map_action]){
				ActionManager::FireDown(map_action);
				key_has_gone_up[(unsigned int)map_action] = false;
			}
			return;
		}
		else if(event.type == sf::Event::MouseButtonReleased && map_event.mouseButton.button == event.mouseButton.button){
			ActionManager::FireUp(map_action);
			key_has_gone_up[(unsigned int)map_action] = true;
			return;
		}
	}
}