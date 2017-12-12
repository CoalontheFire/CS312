#include "GameManager.h"
#include <Iostream>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")
extern bool gQuitGame;

int main( int argc, char* args[] )
{
	GameManager gameManager;
	//PlaySound("sounds/zelda_13.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
	if(gameManager.Init()){
		while (!gQuitGame) {
			gameManager.Update();
			gameManager.Render();
		}
	}

	gameManager.Cleanup();

	return 0;
}