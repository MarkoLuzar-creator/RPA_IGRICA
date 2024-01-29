#pragma once
#include <SDL.h>
#include <string>
#include "../CORE/PHYSICS/Vector2D.h"
#include "../CORE/PHYSICS/RigidBody.h"
#include "../CORE/ANIMATION/Animation.h"

class MiniMap{
public:
	static MiniMap& GetInstance() {
		static MiniMap instance;
		return instance;
	}
	virtual void Draw();
	virtual void Update();
	void SetProperties(std::string mapTextureID, float x, float y, int width, int height, SDL_RendererFlip flip);
	static float worldSize;
	static float viewDistance;
private:
	MiniMap(){}
	float m_MapScale = 50;
	std::string m_BaseTextureID, m_LevelID;
	Vector2D* m_Position;
	Vector2D* m_Size;
	SDL_RendererFlip m_Flip;
};

