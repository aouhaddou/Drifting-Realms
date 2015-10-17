#include "ActionManager.hpp"
#include "Widgets/Include/Widget.hpp"


std::function<void ()> ActionManager::actions_down[(unsigned int)ActionTypes::Length]; // key pressed
std::function<void ()> ActionManager::actions_up[(unsigned int)ActionTypes::Length]; // key released

Widget *ActionManager::widgets[(unsigned int)ActionTypes::Length];


void ActionManager::Initialize(){
	for(unsigned int i = 0;i < (unsigned int)ActionTypes::Length; i++)
		widgets[i] = nullptr;
}

void ActionManager::MapActionToFunctionDown(ActionTypes action, const std::function<void ()> func){
	actions_down[(unsigned int)action] = func;
}

void ActionManager::MapActionToFunctionUp(ActionTypes action, const std::function<void ()> func){
	actions_up[(unsigned int)action] = func;
}

void ActionManager::MapWidgetToAction(const ActionTypes action, Widget *widget){
	widgets[(unsigned int)action] = widget;
	widget->SetAction(action);
}


void ActionManager::FireDown(ActionTypes action){
	if(actions_down[(unsigned int)action])
		actions_down[(unsigned int)action]();

	if(widgets[(unsigned int)action] != nullptr){
		widgets[(unsigned int)action]->SetAcionDownState();
	}
}
void ActionManager::FireUp(ActionTypes action){
	if(actions_up[(unsigned int)action])
		actions_up[(unsigned int)action]();

	if(widgets[(unsigned int)action] != nullptr){
		widgets[(unsigned int)action]->SetAcionUpState();
	}
}
