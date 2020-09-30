#pragma once

#include "Input.h"
//#include "Game.h"

InputActionBase::InputActionBase(Game* context) : m_context{ context } {}

InputAction::InputAction(InputActionBase* context, std::string param, ActionType type)
	: m_context{ context }, m_actionType{ type }, m_param{ param }, m_ignore{ false } {}

void InputAction::run() {
	m_context->funct(m_param);
}

void InputAction::setIgnore(bool ignore) {
	m_ignore = ignore;
}

bool InputAction::isIgnored() const {
	return m_ignore;
}

const InputActionBase* InputAction::getActionBase() const {
	return m_context;
}