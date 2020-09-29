#pragma once

#include "Input.h"
#include "ScreenManager.h"
#include "InputManager.h"
#include "UI.h"

class olcConsoleGameEngine;

class Game : public olcConsoleGameEngine {
	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float) override;
	virtual bool OnUserDestroy() override;

public:
	ScreenManager* sceneManager;
	InputManager* inputManager;
	UIManager* uiManager;
};