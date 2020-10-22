#pragma once

#include "Actor.h"
#include "Input.h"

class Game;

//The main Player
class Player : public Actor {
	class InputMovePlayer : public InputActionBase<Player> {
	public:
		// Inherited via InputActionBase
		virtual int funct(std::string) override;
		InputMovePlayer(Player* context);
	};
	InputMovePlayer* inputs;

	void registerInputs();

public:
	Player(Game* context, wchar_t _char = L'@');

	const InputMovePlayer* getInputBinding() const; //Returns a pointer to the InputMovePlayer for the Player.

	void update() override;
	~Player();
};