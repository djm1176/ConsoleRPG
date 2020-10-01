#include "ScreenManager.h"
#include "Game.h"
#include "UI.h"

ScreenManager::ScreenManager(int width, int height, Game* context)
	: m_width{ width },
	m_height{ height },
	m_context{ context },
	m_UIManager{ new UIManager{context} },
	m_Tiles{ std::vector<Tile>(width * height) },
	m_Player{ Player{context} } {

		//TODO: Somehow pass color in player's initialization? (Player > Actor > Renderer)
		m_Player.setcolor(FG_WHITE);

		//Create input binding for blocking Player input
		m_toggleUIInput = new InputToggleMenu(m_context, this);
		InputAction q_action = InputAction((InputActionBase*)m_toggleUIInput);

		m_context->inputManager->registerInput(0x51 /*Q*/, 1, q_action);
}

Tile& ScreenManager::operator[] (int index) {
	return m_Tiles[index];
}

Tile& ScreenManager::at(int index) {
	return m_Tiles.at(index);
}

Tile& ScreenManager::at(int x, int y) {
	return m_Tiles.at(x + y * m_width);
}

std::vector<Tile> ScreenManager::tiles() {
	return m_Tiles;
}

int ScreenManager::getWidth() const {
	return m_width;
}

int ScreenManager::getHeight() const {
	return m_height;
}

void ScreenManager::update() {
	//Render all tiles to the game window
	for (int i = 0; i < m_width * m_height; i++) {
		m_context->Draw(i % m_width, i / m_width, m_Tiles[i].getchar(), m_Tiles[i].getcolor());
	}

	//Render the player
	m_context->Draw(m_Player.position.x, m_Player.position.y, m_Player.getchar(), m_Player.getcolor());
}

Player* ScreenManager::getPlayer() {
	//TODO: m_Player should be a pointer?
	return &m_Player;
}

ScreenManager::~ScreenManager() {
	delete m_UIManager;
	delete m_toggleUIInput;
}

int ScreenManager::InputToggleMenu::funct(std::string) {
	//Toggle whether the Player absorbs inputs
	Player* _player = m_Manager->getPlayer();
	m_Manager->m_context->inputManager->setIgnoreInput(_player->getInputBinding(), 2);
	return 0;
}

ScreenManager::InputToggleMenu::InputToggleMenu(Game* context, ScreenManager* manager)
	: InputActionBase{ context }, m_Manager{ manager } {
	
}