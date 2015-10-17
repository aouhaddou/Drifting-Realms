#include "GUIManager.hpp"


WidgetList *GUIManager::widget_list;
WidgetList *GUIManager::widget_list_last;
sf::Texture GUIManager::check_mark_texture;
sf::Font GUIManager::font;

void GUIManager::Initialize(){
	check_mark_texture.loadFromFile("check.png");
	widget_list = new WidgetList;
	widget_list_last = widget_list;
	font.loadFromFile("arial.ttf");
}

// NOTE: this function will crash
// if no GUI elements have been created
// because "delete iterator->next;"
void GUIManager::Finalize(){
	WidgetList *iterator = widget_list;


	while(iterator->next != nullptr){
		WidgetList *delete_me = iterator;
		iterator = iterator->next;
		delete delete_me->widget;
		delete delete_me;
	}
	// we always have an empty link
	// so we delete it.
	delete iterator->next;
}

bool GUIManager::ProcessInput(const sf::Event &event){
	WidgetList *iterator = widget_list;
	while(iterator->next != nullptr){
		if(iterator->widget->ProcessInput(event))
			return true;
		iterator = iterator->next;
	}
}

void GUIManager::Draw(sf::RenderWindow &window){
	WidgetList *iterator = widget_list;
	while(iterator->next != nullptr){
		iterator->widget->Draw(window);
		iterator = iterator->next;
	}
}

Button *GUIManager::MakeButton(std::string title, int x, int y, int w, int h){
	Button *button = new Button(title, font, x, y);
	button->SetSize(w,h);

	widget_list_last->widget = button;
	widget_list_last->next = new WidgetList;
	widget_list_last = widget_list_last->next;
	
	return button;
}
Button *GUIManager::MakeToggleButton(std::string title, int x, int y, int w, int h){
	Button *button = MakeButton(title, x, y, w, h);
	button->SetToggle(true);
	return button;
}
CheckButton *GUIManager::MakeCheckButton(std::string title, int x, int y){
	CheckButton *button = new CheckButton(title, font, x, y, check_mark_texture);

	widget_list_last->widget = button;
	widget_list_last->next = new WidgetList;
	widget_list_last = widget_list_last->next;

	return button;
}
