#include "Player.h"
#include "Game.h"

int Player::InputMovePlayer::funct(std::string param) {

	//Get coordinates from the input
	int x = std::stoi(param.substr(0, 2));
	int y = std::stoi(param.substr(2, 2));

	//Update player's position


	return 0;
}

//Required constructor to initialize base class
Player::InputMovePlayer::InputMovePlayer(Game* context) : InputActionBase{ context } {}

void Player::registerInputs() {
	//Initialize test Input Action class
	inputs = new InputMovePlayer(m_context);

	//Create InputAction
	InputAction w_action = InputAction((InputActionBase*)inputs, "0 -1");
	InputAction a_action = InputAction((InputActionBase*)inputs, "-1 0");
	InputAction s_action = InputAction((InputActionBase*)inputs, "0 1 ");
	InputAction d_action = InputAction((InputActionBase*)inputs, "1 0 ");

	//Register input by binding the action to a key press
	m_context->inputManager->registerInput(0x57, 1, w_action);
	m_context->inputManager->registerInput(0x41, 1, a_action);
	m_context->inputManager->registerInput(0x53, 1, s_action);
	m_context->inputManager->registerInput(0x44, 1, d_action);
}


Player::Player(Game* context, wchar_t _char) : m_context{ context } {
	setchar(_char);
	registerInputs();
}

void Player::update() {

}