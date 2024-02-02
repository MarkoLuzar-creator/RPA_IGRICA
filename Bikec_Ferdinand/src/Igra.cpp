#include "Igra.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "../CORE/VECTOR/Vector.h"
#include "../CORE/CAMERA/Camera.h"
#include "../CORE/LEVEL/Level.h"
#include "../CORE/WINDOW/Window.h"
#include "../CORE/TIMER/Timer.h"
#include "../CORE/INPUT/Input.h"
#include "../CORE/TEXTURE/Texture.h"
#include "../IGRA/Button.h"
#include "../IGRA/Sprite.h"
#include "../IGRA/MiniMap.h"
#include "../IGRA/Lab.h"
#include "../IGRA/Igralec.h"
#include "../IGRA/Nasprotnik.h"
#include "../IGRA/World.h"


const int WorldSettings::worldSize;

Button* gumb_za_igro;
Button* gumb_za_nastavitve;
Button* gumb_za_izhod;
Lab* laboratoriji;
Sprite* meni_ozadje;
World* svet;

void Igra::Init(){
	_shouldClose = false;
    SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Window::GetInstance().CreateWindow(1920, 1080, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	gumb_za_igro = new Button("../Assets/Gumbi1/igraj.png", "../Assets/Gumbi1/igraj.png", "menu", 0, -214, 301, 204, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Play);
	gumb_za_nastavitve = new Button("../Assets/Gumbi0/nastavitve.png", "../Assets/Gumbi1/nastavitve.png", "menu", 0, 0, 301, 204, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Options);
	gumb_za_izhod = new Button("../Assets/Gumbi0/izhod.png", "../Assets/Gumbi1/izhod.png", "menu", 0, 214, 301, 204, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Exit);
	meni_ozadje = new Sprite("../Assets/ozadje.png", "menu", 0, 0, 2000, 1333, 1, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	laboratoriji = new Lab("level1");
	for (int i = 0; i < 15; i++) {
		int x = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		int y = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		laboratoriji->Push("../Assets/arena.png", x, y, 1152, 1152, 1.0f, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	}
	svet = new World("level1");
	for (int x = -WorldSettings::worldSize - 2000; x < WorldSettings::worldSize + 2000; x += 1000) {
		for (int y = -WorldSettings::worldSize - 2000; y < WorldSettings::worldSize + 2000; y += 1000) {
			svet->Push("../Assets/pesek.jpg", x, y, 1000, 1000, 1, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
		}
	}



	Igralec::GetInstance().SetProperties("player_idle", 0, 0, 64, 64, SDL_FLIP_NONE);

	MiniMap::GetInstance().SetProperties("miniMap", 1920 / 2 - 600 / 2, 1080 / 2 - 600 / 2, 600, 600, SDL_FLIP_NONE);

	for (int i = 0; i < 15; i++) {
		int x = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		int y = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		Nasprotnik* n = new Nasprotnik("player_idle", x, y, 64, 64, SDL_FLIP_NONE, "level1");
	}

	Texture::GetInstance().Load("player_idle", "../Assets/player_jump.png");
	Texture::GetInstance().Load("player_running", "../Assets/player_roll.png");
	Texture::GetInstance().Load("miniMap", "../Assets/miniMap.jpg");
	Texture::GetInstance().Load("nasprotnik", "../Assets/nasprotnik.png");
	Texture::GetInstance().Load("igralec", "../Assets/player.png");
	Texture::GetInstance().Load("igralec", "../Assets/player.png");
	Texture::GetInstance().Load("kamen", "../Assets/kamen.jpg");

	Camera::GetInstance().SetOriginPosition(0, 0);

	Level::GetInstance().LoadLevels("menu");
	Level::GetInstance().LoadLevels("level1");
	Level::GetInstance().LoadLevels("options");

}

void Igra::Events(){
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN: Input::GetInstance().UpdateKeys(); break;
		case SDL_KEYUP: Input::GetInstance().UpdateKeys(); break;
		case SDL_MOUSEMOTION: Input::GetInstance().UpdateMousePosition(); break;
		case SDL_MOUSEBUTTONDOWN: Input::GetInstance().UpdateMouseClicks(); break;
		case SDL_QUIT: _shouldClose = true; break;
		}
	}
	if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
		_shouldClose = true;
	}
}

void Igra::Update(){
	Window::GetInstance().WindowClear();
	Timer::GetInstance().Tick();

	meni_ozadje->Update();
	meni_ozadje->Draw();

	gumb_za_igro->Update();
	gumb_za_nastavitve->Update();
	gumb_za_izhod->Update();

	svet->Update();
	laboratoriji->Update();

	MiniMap::GetInstance().Update();
	Igralec::GetInstance().Update();

	for (Nasprotnik* i : Vector::GetInstance().m_SeznamNasprotnikov) {
		i->Update();
	}

}

void Igra::Draw(){
	svet->Draw();
	Igralec::GetInstance().Draw();

	gumb_za_igro->Draw();
	gumb_za_nastavitve->Draw();
	gumb_za_izhod->Draw();
	laboratoriji->Draw();
	MiniMap::GetInstance().Draw(*laboratoriji);

	for (Nasprotnik* i : Vector::GetInstance().m_SeznamNasprotnikov) {
		i->Draw();
	}
	Camera::GetInstance().Update(Igralec::GetInstance().GetOrigin());

	Window::GetInstance().WindowRender();
}

void Igra::Clean(){
    SDL_Quit();
    IMG_Quit();
}