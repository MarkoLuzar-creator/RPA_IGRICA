﻿#define SDL_MAIN_HANDLED

#include "CORE/WINDOW/Window.h"
#include "IGRA/KlasičniGumb.h"
#include "IGRA/Igralec.h"
#include "CORE/CAMERA/Camera.h"
#include "IGRA/MiniMap.h"
#include "IGRA/Arena.h"
#include "IGRA/Nasprotnik.h"
#include <vector>
#include <ctime>
#include <SDL_image.h>
#include "CORE/LEVEL/Level.h"
#include "CORE/TEXTURE/Texture.h"
#include "CORE/TIMER/Timer.h"
#include "CORE/INPUT/Input.h"
#include "CORE/VECTOR/Vector.h"

#include "IGRA/Ozadje.h"

int main() {
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        std::cout << SDL_GetError() << std::endl;
    }

	Window::GetInstance().CreateWindow(1920, 1080, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	#pragma region Texture
	Texture::GetInstance().Load("player_idle", "../Assets/player_jump.png");
	Texture::GetInstance().Load("player_running", "../Assets/player_roll.png");
	Texture::GetInstance().Load("miniMap", "../Assets/miniMap.jpg");
	Texture::GetInstance().Load("nasprotnik", "../Assets/nasprotnik.png");
	Texture::GetInstance().Load("igralec", "../Assets/player.png");
	Texture::GetInstance().Load("igralec", "../Assets/player.png");
	Texture::GetInstance().Load("kamen", "../Assets/kamen.jpg");


	Texture::GetInstance().Load("resolutionsButtonBase", "../Assets/Gumbi0/res.png");
	Texture::GetInstance().Load("resolutionsButtonHover", "../Assets/Gumbi1/res.png");
	Texture::GetInstance().Load("homeButtonBase", "../Assets/Gumbi0/domov.png");
	Texture::GetInstance().Load("homeButtonHover", "../Assets/Gumbi1/domov.png");
	#pragma endregion

	#pragma region gumbi
	KlasičniGumb start("../Assets/Gumbi1/igraj.png", "../Assets/Gumbi1/igraj.png", 0, -214, 301, 204, 0.5f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Play);
	KlasičniGumb nastavitve("../Assets/Gumbi0/nastavitve.png", "../Assets/Gumbi1/nastavitve.png", 0, 0, 301, 204, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Options);
	KlasičniGumb exit("../Assets/Gumbi0/izhod.png", "../Assets/Gumbi1/izhod.png", 0, 214, 301, 204, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Exit);
	#pragma endregion

	#pragma region ozadja
	Ozadje meni_ozadje("../Assets/ozadje.png", "menu", 0, 0, 2000, 1333, 1, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	std::vector<std::vector<Ozadje>> mapa;
	for (int x = -MiniMap::worldSize; x < MiniMap::worldSize; x += 1000) {
		std::vector<Ozadje> r;
		for (int y = -MiniMap::worldSize; y < MiniMap::worldSize; y += 1000) {
			Ozadje tile("../Assets/pesek.jpg", "level1", x, y, 1000, 1000, 1, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
			r.push_back(tile);
		}
		mapa.push_back(r);
	}
	#pragma endregion

	#pragma region laboratorij
	for (int i = 0; i < 15; i++) {
		int x = rand() % (2 * (int)MiniMap::worldSize) - MiniMap::worldSize;
		int y = rand() % (2 * (int)MiniMap::worldSize) - MiniMap::worldSize;
		Arena* arena = new Arena("../Assets/arena.png", "level1", x, y, 1152, 1152, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	}
	#pragma endregion

    Igralec::GetInstance().SetProperties("player_idle", 0, 0, 64, 64, SDL_FLIP_NONE);
    MiniMap::GetInstance().SetProperties("miniMap", 1920 / 2 - 600 / 2, 1080 / 2 - 600 / 2, 600, 600, SDL_FLIP_NONE);

    for (int i = 0; i < 15; i++) {
        int x = rand() % (2 * (int)MiniMap::worldSize) - MiniMap::worldSize;
        int y = rand() % (2 * (int)MiniMap::worldSize) - MiniMap::worldSize;
        Nasprotnik* n = new Nasprotnik("player_idle", x, y, 64, 64, SDL_FLIP_NONE, "level1");
    }
	

	Camera::GetInstance().SetOriginPosition(0, 0);

	Level::GetInstance().LoadLevels("menu");
	Level::GetInstance().LoadLevels("level1");
	
	while (true) {
		Timer::GetInstance().Tick();

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_KEYDOWN: Input::GetInstance().UpdateKeys(); break;
			case SDL_KEYUP: Input::GetInstance().UpdateKeys(); break;
			case SDL_MOUSEMOTION: Input::GetInstance().UpdateMousePosition(); break;
			case SDL_MOUSEBUTTONDOWN: Input::GetInstance().UpdateMouseClicks(); break;
			case SDL_QUIT: break; break;
			}
		}

		Window::GetInstance().WindowClear();


		meni_ozadje.Update();

		start.Draw();
		start.Update();
		nastavitve.Draw();
		nastavitve.Update();
		exit.Draw();
		exit.Update();

		for (auto& i : mapa) {
			for (auto& t : i) {
				t.Update();
			}
		}



		for (Arena i : Arena::_arene) {
			i.Draw();
			i.Update();
		}

		for (Nasprotnik* i : Vector::GetInstance().m_SeznamNasprotnikov) {
			i->Draw();
			i->Update();
		}


		MiniMap::GetInstance().Draw();
		MiniMap::GetInstance().Update();

		Igralec::GetInstance().Draw();
		Igralec::GetInstance().Update();

		Camera::GetInstance().Update(Igralec::GetInstance().GetOrigin());

		Window::GetInstance().WindowRender();
	}
	SDL_Quit();
	IMG_Quit();
}