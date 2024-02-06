#pragma once
#include <string>
#include <vector>

class Level{
public:
	static Level& GetInstance() {
		static Level instance;
		return instance;
	}
	void LoadLevels(std::string levelName);
	void NextLevel();
	void PrevLevel();
	void SetLevel(std::string levelName);
	std::string& GetCurrentLevelName();
private:
	Level(){}
	int index = 0;
	std::vector<std::string> m_Levels;
};

