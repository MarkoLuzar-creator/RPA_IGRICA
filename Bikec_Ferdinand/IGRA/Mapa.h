#pragma once
#include "StaticSlika.h"
#include <vector>

class Mapa {
public:
	void Init();
	void Draw();
private:
	std::vector <std::vector<StaticSlika*>> m_Tiles;
};

