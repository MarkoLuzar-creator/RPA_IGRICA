#pragma once
#include <SDL.h>
#include <string>
#include "../IGRA/Lab.h"
#include "../IGRA/Enemy.h"
#include "../CORE/TextureComponent.h"

class MiniMap{
public:
	static MiniMap& GetInstance() {
		static MiniMap instance;
		return instance;
	}
	void Init();
	void Draw(Lab& l, Enemy& e);
	void Update();

private:
	float m_MapScale = 50;
	TextureComponent* _texture;
};

