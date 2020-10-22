#pragma once
#include <map>
#include "Input.h"

class Game;

//Describes a user input and the resulting action
class InputManager {
private:
	Game* m_context;
	template<class T>
	std::map<int, InputAction<T>> m_keybinds;

public:
	InputManager(Game*);

	void processInput();

	// Binds a key input to an action.
	//keystate 1 = pressed
	//keystate 2 = held
	//keystate 4 = released
	void registerInput(int, int, InputAction);

	//Renders a graphic displaying the given input Key and Format.
	void renderInput(int key, int x, int y, int w = 1, ActionType type = ActionType::none, RenderFormat format = RenderFormat::pointed);

	//Set whether inputs for the given custom subclass of InputActionBase is ignored when input is processed.
	//operation 0:	Don't Ignore
	//operation 1:	Ignore
	//operation 2:	Toggle
	void setIgnoreInput(const InputActionBase* m_actionBase, int operation);
private:
	static std::wstring& key_to_string(int);
	//static COLOUR action_to_color(ActionType);
};