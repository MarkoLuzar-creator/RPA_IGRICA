#include "Level.h"

void Level::LoadLevels(std::string levelName){
	m_Levels.push_back(levelName);
}

void Level::NextLevel(){
	if (index < m_Levels.size()) {
		index++;
	}
}

void Level::PrevLevel(){
	if (index > 0) {
		index--;
	}
}

void Level::SetLevel(std::string levelName){
	for (int i = 0; i < m_Levels.size(); i++) {
		if (m_Levels[i] == levelName) {
			index = i;
			break;
		}
	}
}

std::string& Level::GetCurrentLevelName(){
	return m_Levels[index];
}
