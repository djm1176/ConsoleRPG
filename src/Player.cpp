#include "Player.h"
#include "Game.h"

int Player::InputMovePlayer::funct(std::string param) {

	//Get coordinates from the input
	int x = std::stoi(param.substr(0, 2));
	int y = std::stoi(param.substr(2, 2));

	//Update player's position
	m_context->Move(x, y);

	return 0;
}

Player::InputMovePlayer::InputMovePlayer(Player* context) : InputActionBase{context} {}

void Player::registerInputs() {
	//Initialize test Input Action class
	inputs = new InputMovePlayer(this);

	//Create InputAction
	InputAction<Player> w_action = InputAction((InputActionBase<Player>*)inputs, "0 -1");
	InputAction<Player> a_action = InputAction((InputActionBase<Player>*)inputs, "-1 0");
	InputAction<Player> s_action = InputAction((InputActionBase<Player>*)inputs, "0 1 ");
	InputAction<Player> d_action = InputAction((InputActionBase<Player>*)inputs, "1 0 ");

	//Register input by binding the action to a key press
	m_context->inputManager->registerInput(0x57, 1, w_action);
	m_context->inputManager->registerInput(0x41, 1, a_action);
	m_context->inputManager->registerInput(0x53, 1, s_action);
	m_context->inputManager->registerInput(0x44, 1, d_action);
}


Player::Player(Game* context, wchar_t _char) : Actor{context } {
	setchar(_char);
	registerInputs();
}

Player::~Player() {
	delete inputs;
}

void Player::update() {

}

const Player::InputMovePlayer* Player::getInputBinding() const {
	return inputs;
}