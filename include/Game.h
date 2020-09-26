#pragma once

#include "olcConsoleGameEngine.h"
#include "Input.h"
#include "ScreenManager.h"

class Game : public olcConsoleGameEngine {
	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float) override;
	virtual bool OnUserDestroy() override;

public:
	ScreenManager* sceneManager;
	InputManager* inputManager;
};