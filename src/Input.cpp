#pragma once

#include "Game.h"
#include "Input.h"

InputActionBase::InputActionBase(Game* context) : m_context{ context } {}


InputAction::InputAction(InputActionBase* context, std::string param = "", ActionType type = ActionType::none)
	: m_context{ context }, m_actionType{ type }, m_param{ param } {}

void InputAction::run() {
	//Ignore function call if nullptr
	//if (m_action != nullptr) (m_context->*m_action)(m_param);
	m_context->funct(m_param);
}

InputManager::InputManager(Game* context) : m_context{ context } {}

void InputManager::processInput() {
	for (auto it = m_keybinds.begin(); it != m_keybinds.end(); it++) {
		olcConsoleGameEngine::sKeyState& m_key = m_context->m_keys[(it->first >> 3)];
		if (m_key.bPressed && (it->first >> 0 & 0x01) ||
			m_key.bHeld && (it->first >> 1 & 0x01) ||
			m_key.bReleased && (it->first >> 2 & 0x01)) {
			it->second.run();

		}
	}
}

void InputManager::registerInput(int key, int keystate, InputAction f) {

	//Create and add, or update, a binding
	int _k = (key << 3) + keystate;
	//m_keybinds.insert_or_assign(_k, f);
	m_keybinds.insert(std::make_pair(_k, f));
}


void InputManager::renderInput(int key, int x, int y, int w = 1, ActionType type = ActionType::none, RenderFormat format = RenderFormat::pointed) {
	std::wstring _str = key_to_string(key);
	_str.resize(w);
	switch (format) {
	case RenderFormat::pointed:
		m_context->DrawString(x + 1, y, _str, action_to_color(type));
		m_context->Draw(x, y, (short)'<', FG_WHITE);
		m_context->Draw(x + w + 1, y, (short)'>', FG_WHITE);
		break;
	case RenderFormat::minimal:
		m_context->DrawString(x, y, _str, action_to_color(type));
		break;
	case RenderFormat::rounded:
		m_context->DrawString(x + 1, y, _str, action_to_color(type));
		m_context->Draw(x, y, (short)'(', FG_WHITE);
		m_context->Draw(x + w + 1, y, (short)')', FG_WHITE);

		break;
	}
}

std::wstring& InputManager::key_to_string(int key) {
	static std::map<int, std::wstring> _map = {
		{0x08, L"BACK"},	{0x09, L"TAB"},		{0x0D, L"ENTER"},	{0x12, L"ALT"},
		{0x1B, L"ESC"},		{0x20, L"SPACE"},	{0x25, L"LEFT"},	{0x26, L"UP"},
		{0x27, L"RIGHT"},	{0x28, L"DOWN"},	{0x10, L"SHIFT"},	{0x11, L"CTRL"},
		{0x30, L"0"},		{0x31, L"1"},		{0x32, L"2"},		{0x33, L"3"},
		{0x34, L"4"},		{0x35, L"5"},		{0x36, L"6"},		{0x37, L"7"},
		{0x38, L"8"},		{0x39, L"9"},		{0x41, L"A"},		{0x42, L"B"},
		{0x43, L"C"},		{0x44, L"D"},		{0x45, L"E"},		{0x46, L"F"},
		{0x47, L"G"},		{0x48, L"H"},		{0x49, L"I"},		{0x4A, L"J"},
		{0x4B, L"K"},		{0x4C, L"L"},		{0x4D, L"M"},		{0x4E, L"N"},
		{0x4F, L"O"},		{0x50, L"P"},		{0x51, L"Q"},		{0x52, L"R"},
		{0x53, L"S"},		{0x54, L"T"},		{0x55, L"U"},		{0x56, L"V"},
		{0x57, L"W"},		{0x58, L"X"},		{0x59, L"Y"},		{0x5A, L"Z"},
		{0xC0, L"~"},		{0xE8, L" "} //Undefined
	};

	auto _s = _map.find(key);
	if (_s == _map.end()) return _map[0xE8];
	return _s->second; //Else, key was found
}

COLOUR InputManager::action_to_color(ActionType format) {
	switch (format) {
	case ActionType::none:
		return FG_GREY;

	case ActionType::game:
		return FG_CYAN;

	case ActionType::interact:
		return FG_YELLOW;

	}
}