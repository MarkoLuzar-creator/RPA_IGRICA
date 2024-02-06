#pragma once
#include <SDL.h>
#include <string>
#include <engine.h>
#include <Lab.h>
#include <Enemy.h>
#include <World.h>

class MiniMap{
public:
	static MiniMap& GetInstance() {
		static MiniMap instance;
		return instance;
	}
	void LoadLab(Lab& l);
	void LoadEnemy(Enemy& e);
	void LoadWorld(World& w);
	void Draw();
	void Update();

private:
	float m_MapScale = 50;
	TextureComponent* _texture;
	Lab* _lab;
	Enemy* _enemy;
	World* _world;
};

