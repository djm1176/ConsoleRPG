#pragma once
#include <string>
#include <map>
#include <functional>

#include "olcConsoleGameEngine.h"

class Game;

//Abstract class for Input Actions.
//Create a class that derives from this class that implements the virtual function funct(), as well as the following public constructor:
//MySubclassName(olcConsoleGameEngine* game) : InputActionBase{game} { ... }
class InputActionBase {
protected:
	Game* m_context;
	InputActionBase(Game*);
public:
	virtual int funct(std::string) = 0;
};

//A function pointer that accepts optional string parameter, and returns int.
//typedef int(InputActionBase::*input_funct)(std::string);

//none:		The input represents either no action, or an undefined action.
//interact: The input represents an interaction within the game.
//game:		The input represents a game window action.
enum ActionType { none, interact, game };


//Minimal: 1 character is used to display the input key.
//Pointed: 3 characters are used, with < >, to display the input key.
//Rounded: 3 characters are used, with ( ), to display the input key.
enum RenderFormat { minimal, pointed, rounded };

class InputAction {
private:
	//input_funct m_action;
	ActionType m_actionType;
	std::string m_param;
	InputActionBase* m_context;

public:

	//Initializes an Input Action with given action (function call), optional params, and a classification of the action as an ActionType.
	//InputAction(InputActionBase* context, input_funct action = nullptr, std::string param = "", ActionType type = ActionType::none)
	//	: m_context{ context }, m_action { action }, m_actionType{ type }, m_param{ param } {}
	InputAction(InputActionBase*, std::string, ActionType);

	void run();

};

//Describes a user input and the resulting action
class InputManager {
private:
	Game* m_context;
	std::map<int, InputAction> m_keybinds;

public:
	InputManager(Game*);

	void processInput();

	// Binds a key input to an action.
	//keystate 1 = pressed
	//keystate 2 = held
	//keystate 4 = released
	void registerInput(int, int, InputAction);

	//Renders a graphic displaying the given input Key and Format.
	void renderInput(int, int, int, int, ActionType, RenderFormat);

private:
	static std::wstring& key_to_string(int);
	static COLOUR action_to_color(ActionType);
};