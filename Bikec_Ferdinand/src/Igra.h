#pragma once

struct WorldSettings {
	static const int worldSize;
	static const float scale;
};

class Igra{
public:
	static Igra& GetInstance() {
		static Igra instance;
		return instance;
	}
	void Init();
	void Events();
	void Update();
	void Draw();
	void Clean();
	bool _shouldClose;
};

