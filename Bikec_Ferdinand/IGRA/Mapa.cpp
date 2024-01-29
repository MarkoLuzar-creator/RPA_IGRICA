#include "Mapa.h"
#include "MiniMap.h"
#include <SDL.h>

void Mapa::Init(){
    // Resize m_Tiles to have 40 rows and 40 columns
    m_Tiles.resize(40, std::vector<StaticSlika*>(40, nullptr));

    for (int i = 0, x = -MiniMap::worldSize * 2; i < 40; i++, x += 1000) {
        for (int j = 0, y = MiniMap::worldSize * 2; j < 40; j++, y -= 1000) {
            m_Tiles[i][j] = new StaticSlika("pesek", x, y, 1000, 1000, SDL_FLIP_NONE, "level1");
        }
    }
}

void Mapa::Draw(){
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			m_Tiles[i][j]->Draw();
		}
	}
}
