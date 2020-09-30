#pragma once

#include "Actor.h"
#include "Input.h"

class Game;

//The main Player
class Player : public Actor {
	class InputMovePlayer : public InputActionBase {
	public:
		// Inherited via InputActionBase
		virtual int funct(std::string) override;

		Player* m_player;
		//Required constructor to initialize base class
		InputMovePlayer(Game*, Player*);
	};
	InputMovePlayer* inputs;

	void registerInputs();

public:
	Player(Game* context, wchar_t _char = L'@');

	void update() override;
	~Player();
};