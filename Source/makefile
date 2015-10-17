CC=g++
CCFLAGS=-std=c++14 -g3
INC=-I./Include -I./Widgets/Include
LIBS=-lpthread -lsfml-graphics -lsfml-window -lsfml-system

OBJS=main.o InputManager.o ActionManager.o GUIManager.o Button.o CheckButton.o Widget.o

link: $(OBJS)
	$(CC) $(CCFLAGS) -o ../Bin/game $(OBJS) $(LIBS)
	
main.o: main.cpp
	$(CC) $(CCFLAGS) -c $< $(INC)

InputManager.o: InputManager.cpp ./Include/InputManager.hpp
	$(CC) $(CCFLAGS) -c $< $(INC)

ActionManager.o: ActionManager.cpp ./Include/ActionManager.hpp
	$(CC) $(CCFLAGS) -c $< $(INC)

## Define Rules for the GUIManager and its widgets
GUIManager.o: GUIManager.cpp ./Include/GUIManager.hpp
	$(CC) $(CCFLAGS) -c $< $(INC)

Button.o: ./Widgets/Button.cpp
	$(CC) $(CCFLAGS) -c $< $(INC)
	
CheckButton.o: ./Widgets/CheckButton.cpp
	$(CC) $(CCFLAGS) -c $< $(INC)
	
Widget.o: ./Widgets/Widget.cpp
	$(CC) $(CCFLAGS) -c $< $(INC)
