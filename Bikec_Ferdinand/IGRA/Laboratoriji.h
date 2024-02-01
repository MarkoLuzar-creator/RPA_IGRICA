#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "../CORE/TextureComponent.h"
#include "../IGRA/MiniMap.h"

class Laboratoriji{
public:
	static Laboratoriji& GetInstance() {
		static Laboratoriji instance;
		return instance;
	}
	void Init();
	void Draw();
	void Update();
	void Clear(const char* level);
	
	friend class MiniMap;
private:
	int _indexPrikazanegaElementa;
	struct El {
		int _indexElementa;
		const char* _level;
		TextureComponent* _texture;
	};
	std::vector<El> _list;
};

