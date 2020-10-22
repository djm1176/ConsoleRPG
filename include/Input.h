#pragma once
#include <string>
#include <functional>

//Abstract class for Input Actions.
//Create a class that derives from this class that implements the virtual function funct(), as well as the following public constructor:
//MySubclassName(olcConsoleGameEngine* game) : InputActionBase{game} { ... }
template <class Base>
class InputActionBase {
protected:
	Base* m_context;
	InputActionBase(Base* context) : m_context{ context } {};
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

template <class Base>
class InputAction {
private:
	//input_funct m_action;
	ActionType m_actionType;
	std::string m_param;
	InputActionBase<Base>* m_context;
	bool m_ignore; //If true, this InputAction is ignored and the Action is not invoked.

public:

	//Initializes an Input Action with given action (function call), optional params, and a classification of the action as an ActionType.
	InputAction(InputActionBase<Base>* context, std::string param = "", ActionType type = ActionType::none) : 
		m_context{ context }, m_param{ param }, m_actionType{ type } {}

	void run() { m_context->funct(); }

	//Sets whether this InputAction's invoke should be ignored.
	void setIgnore(bool ignore) { m_ignore = ignore; }

	//Returns true if this InputAction's invoke should be ignored.
	bool isIgnored() const { return m_ignore; }

	//Returns a pointer to this InputAction's subclassed InputActionBase.
	const InputActionBase<Base>* getActionBase() { return m_context; }

};