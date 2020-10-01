#include "external/PerlinNoise.h"
#include "Tile.h"
#include <memory>
#include <map>

namespace MapBuilder {
	siv::PerlinNoise perlin(std::random_device{});

	const std::map<int, Tile> TILES{
		{0, Tile{"air", Tile::moveable, L' ', FG_WHITE} },
		{1, Tile{"grass", Tile::moveable, L'.', FG_DARK_GREEN} },
		{2, Tile{"grass", Tile::moveable, L'\'', FG_DARK_GREEN} },
		{3, Tile{"grass", Tile::moveable, L',', FG_DARK_GREEN} },
		{4, Tile{"grass", Tile::moveable, L'\"', FG_DARK_GREEN} }
	};

	void generatePerlinTiles(int x, int y, int w, int h, std::vector<Tile>& tiles) {
		for (int i = 0; i < w * h; i++) {
			//Generate perlin noise value
			int p = (int)(perlin.accumulatedOctaveNoise2D_0_1(x, y, 1) * 4);
			switch(p) {
			case 0:
				tiles[i] = Tile{ TILES.at(1) };
				break;
			case 1:
				tiles[i] = Tile{ TILES.at(2) };
				break;
			case 2:
				tiles[i] = Tile{ TILES.at(3) };
				break;
			case 3:
				tiles[i] = Tile{ TILES.at(4) };
				break;
			}
			
		}
	}
}