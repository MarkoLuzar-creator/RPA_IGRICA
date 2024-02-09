#include "Igra.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <engine.h>

#include <Button.h>
#include <Sprite.h>
#include <MiniMap.h>
#include <Lab.h>
#include <Player.h>
#include <Enemy.h>
#include <World.h>


const int WorldSettings::worldSize = 10000;
const int WorldSettings::viewDistance = 5000;
const float WorldSettings::scale = 1.0f;

Button* gumb_za_igro;
Button* gumb_za_nastavitve;
Button* gumb_za_izhod;
Lab* laboratoriji, *laboratoriji2;
Sprite* meni_ozadje;
World* svet, *svet2;
Enemy* nasprotniki, *nasprotniki2;

void Igra::Init(){
	_shouldClose = false;
    SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Window::GetInstance().CreateWindow(1920, 1080, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	Player::GetInstance().Init(0, 0, 64, 64, WorldSettings::scale, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	Camera::GetInstance().SetTarget(Player::GetInstance().GetOrigin());
	gumb_za_igro = new Button("../assets/Gumbi1/igraj.png", "../assets/Gumbi1/igraj.png", "menu", 0, -214, 301, 204, WorldSettings::scale, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Play);
	gumb_za_nastavitve = new Button("../assets/Gumbi0/nastavitve.png", "../assets/Gumbi1/nastavitve.png", "menu", 0, 0, 301, 204, WorldSettings::scale, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Options);
	gumb_za_izhod = new Button("../assets/Gumbi0/izhod.png", "../assets/Gumbi1/izhod.png", "menu", 0, 214, 301, 204, WorldSettings::scale, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE, ButtonTypes::Exit);
	meni_ozadje = new Sprite("../assets/ozadje.png", "menu", 0, 0, 2000, 1333, WorldSettings::scale , &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	laboratoriji = new Lab("level1");
	svet = new World("level1");
	nasprotniki = new Enemy("level1");
	laboratoriji2 = new Lab("level2");
	svet2 = new World("level2");
	nasprotniki2 = new Enemy("level2");
	for (int i = 0; i < 3; i++) {
		int x = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		int y = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		laboratoriji->Push("../assets/arena.png", x, y, 1152, 1152, WorldSettings::scale, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	}
	for (int x = -WorldSettings::worldSize - 2000; x < WorldSettings::worldSize + 2000; x += 1000) {
		for (int y = -WorldSettings::worldSize - 2000; y < WorldSettings::worldSize + 2000; y += 1000) {
			bool z = rand() % (2);
			if (z)
			svet->Push("../assets/pesek.jpg", x, y, 1000, 1000, 1.0f, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
			else
			svet->Push("../assets/kamen.jpg", x, y, 1000, 1000, 1.0f, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
		}
	}
	for (int i = 0; i < 10; i++) {
		int x = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		int y = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		nasprotniki->Push("../assets/player_jump.png", x, y, 64, 64, 0, 8, 50, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	}
	for (int i = 0; i < 10; i++) {
		int x = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		int y = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		laboratoriji2->Push("../assets/arena.png", x, y, 1152, 1152, WorldSettings::scale, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	}
	for (int x = -WorldSettings::worldSize - 2000; x < WorldSettings::worldSize + 2000; x += 1000) {
		for (int y = -WorldSettings::worldSize - 2000; y < WorldSettings::worldSize + 2000; y += 1000) {
			bool z = rand() % (2);
			if (z)
				svet2->Push("../assets/pesek.jpg", x, y, 1000, 1000, 1.0f, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
			else
				svet2->Push("../assets/kamen.jpg", x, y, 1000, 1000, 1.0f, Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
		}
	}
	for (int i = 0; i < 20; i++) {
		int x = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		int y = rand() % (2 * WorldSettings::worldSize) - WorldSettings::worldSize;
		nasprotniki2->Push("../assets/player_jump.png", x, y, 64, 64, 0, 8, 50, 1.0f, &Window::GetInstance().GetRenderer(), SDL_FLIP_NONE);
	}

	Level::GetInstance().LoadLevels("menu");
	Level::GetInstance().LoadLevels("level1");
	Level::GetInstance().LoadLevels("level2");
	Level::GetInstance().LoadLevels("options ");

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
	Timer::GetInstance().Tick();
	{	
		std::cout << Level::GetInstance().GetCurrentLevelName();
		MiniMap::GetInstance().Update();
		Player::GetInstance().Update();
		gumb_za_igro->Update();
		gumb_za_nastavitve->Update();
		gumb_za_izhod->Update();
		meni_ozadje->Update();
		svet->Update();
		svet2->Update();
		laboratoriji->Update();
		laboratoriji2->Update();
		nasprotniki->Update();
		nasprotniki2->Update();
	}

}

void Igra::Draw(){
	Window::GetInstance().WindowClear();
	{
		meni_ozadje->Draw();
		svet->Draw();
		svet2->Draw();
		laboratoriji->Draw();
		laboratoriji2->Draw();
		gumb_za_igro->DrawBase();
		gumb_za_nastavitve->DrawBase();
		gumb_za_izhod->DrawBase();
		gumb_za_igro->DrawHover();
		gumb_za_nastavitve->DrawHover();
		gumb_za_izhod->DrawHover();
		nasprotniki->Draw();
		nasprotniki2->Draw();
		MiniMap::GetInstance().Draw();
		Player::GetInstance().Draw();
		Camera::GetInstance().Update();
		Camera::GetInstance().UpdateAnimation();
	}
	Window::GetInstance().WindowRender();
}

void Igra::Clean(){
    SDL_Quit();
    IMG_Quit();
}
