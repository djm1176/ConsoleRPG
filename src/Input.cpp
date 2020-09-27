#pragma once

#include "Input.h"
//#include "Game.h"

InputActionBase::InputActionBase(Game* context) : m_context{ context } {}


InputAction::InputAction(InputActionBase* context, std::string param, ActionType type)
	: m_context{ context }, m_actionType{ type }, m_param{ param } {}

void InputAction::run() {
	//Ignore function call if nullptr
	//if (m_action != nullptr) (m_context->*m_action)(m_param);
	m_context->funct(m_param);
}