#pragma once

struct WorldSettings {
	static const int worldSize = 10000;
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

