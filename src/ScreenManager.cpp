#include "ScreenManager.h"
#include "Game.h"

ScreenManager::ScreenManager(int width, int height, Game* context)
	: m_width{ width },
	m_height{ height },
	m_context{ context },
	m_Tiles{ std::vector<Tile>(width * height) },
	m_Player{ Player{context} } {}

Tile& ScreenManager::operator[] (int index) {
	return m_Tiles[index];
}

Tile& ScreenManager::at(int index) {
	return m_Tiles.at(index);
}

void ScreenManager::update() {
	//Render all tiles to the game window
	for (int i = 0; i < m_width * m_height; i++) {
		m_context->Draw(i % m_width, i / m_width, m_Tiles[i].getchar());
	}

	//Render the player
	m_context->Draw(m_Player.position.x, m_Player.position.y, m_Player.getchar(), m_Player.getcolor());
}