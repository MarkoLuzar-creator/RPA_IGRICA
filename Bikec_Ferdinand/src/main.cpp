#define SDL_MAIN_HANDLED
#include <ctime>
#include <stdlib.h>
#include "Igra.h"


int main() {
    srand(time(0));

	Igra::GetInstance().Init();
	while (!Igra::GetInstance()._shouldClose) {
		Igra::GetInstance().Events();
		Igra::GetInstance().Draw();
		Igra::GetInstance().Update();
	}
	Igra::GetInstance().Clean();

	return 0;
}