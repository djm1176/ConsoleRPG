#pragma once
#include <map>
#include "Input.h"

class Game;

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
	void renderInput(int key, int x, int y, int w = 1, ActionType type = ActionType::none, RenderFormat format = RenderFormat::pointed);

private:
	static std::wstring& key_to_string(int);
	//static COLOUR action_to_color(ActionType);
};