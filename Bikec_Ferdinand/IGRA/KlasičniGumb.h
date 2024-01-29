#pragma once
#include <string>
#include <SDL.h>
#include "../CORE/VECTOR/Vector.h"

enum class ButtonTypes {
	Play,
	Exit,
	Options,
	Resolution,
	Home,
};

class KlasičniGumb{
public:
	KlasičniGumb(std::string baseTextureID, std::string hoverTextureID, float x, float y, int width, int height, SDL_RendererFlip flip, std::string levelName, ButtonTypes buttonType);
	virtual void Draw();
	virtual void Update();
private:
	ButtonTypes tipGumba;
	std::string trenutnaTextura;
	std::string m_HoverTextureID;
	std::string m_BaseTextureID, m_LevelID;
	Vector2D* m_Position;
	Vector2D* m_Size;
	SDL_RendererFlip m_Flip;
};

