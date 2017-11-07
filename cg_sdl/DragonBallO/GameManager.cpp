#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"

#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS true

//Also camera dimension...
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Camera gCamera(CAMERA_MODE);
World gWorld;

static SDLInit sdlInit;

namespace {
	Player player;
	Sprite tree;
	Sprite boulder;
	Sprite kakariko;
	MoveTrigger moveTrigger;
}

void InitEntities() {
	//Setting path names...
	kakariko.SetTexturePath("textures/mapVillage_kakariko.png");
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");
	boulder.SetTexturePath("textures/boulder.png");

	//Loading textures...
	sdlInit.LoadTexture(kakariko);
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(boulder);

	//Setting position information...
	kakariko.SetPosition({ 0, 0});
	player.SetPosition({0, 0});
	tree.SetPosition({200, 300});
	boulder.SetPosition({200, 150});
	moveTrigger.SetPosition({300, 150});

	//Setting size information...
	kakariko.SetSize(1540, 1540); //TODO: Correct size, is fine at 1024, but bugs at actual size
	player.SetSize(35, 35);
	tree.SetSize(64, 78);
	boulder.SetSize(45, 45);
	moveTrigger.SetSize(45, 45);

	//Set sprite sheet texture coordinates...
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(105, 35, 30, 30, 3);			//up...
	player.SetSpriteClip(1, 35, 30, 30, 17);		//up move 1...
	//player.SetSpriteClip(35, 35, 30, 30, 17);		//up move 2...
	//player.SetSpriteClip(70, 35, 30, 30, 17);		//up move 3...
	//player.SetSpriteClip(105, 35, 30, 30, 17);		//up move 4...
	//player.SetSpriteClip(140, 35, 30, 30, 17);		//up move 5...

	player.SetSpriteClip(105, 1, 30, 30, 1);			//down...
	player.SetSpriteClip(1, 1, 30, 30, 15);			//down move 1...
	//player.SetSpriteClip(35, 1, 30, 30, 15);		//down move 2...
	//player.SetSpriteClip(70, 1, 30, 30, 15);		//down move 3...
	//player.SetSpriteClip(105, 1, 30, 30, 15);		//down move 4...
	//player.SetSpriteClip(140, 1, 30, 30, 15);		//down move 5...

	player.SetSpriteClip(105, 70, 30, 30, 4);		//right...
	player.SetSpriteClip(1, 70, 30, 30, 15);			//right move 1...
	//player.SetSpriteClip(35, 70, 30, 30, 15);		//right move 2...
	//player.SetSpriteClip(70, 70, 30, 30, 15);		//right move 3...
	//player.SetSpriteClip(105, 70, 30, 30, 15);		//right move 4...
	//player.SetSpriteClip(140, 70, 30, 30, 15);		//right move 5...

	player.SetSpriteClip(105, 105, 30, 30, 2);			//left...
	player.SetSpriteClip(1, 105, 30, 30, 15);			//left move 1...
	//player.SetSpriteClip(35, 105, 30, 30, 15);		//left move 2...
	//player.SetSpriteClip(70, 105, 30, 30, 15);		//left move 3...
	//player.SetSpriteClip(105, 105, 30, 30, 15);		//left move 4...
	//player.SetSpriteClip(140, 105, 30, 30, 15);		//left move 5...

	player.SetSpriteClip(170, 141, 30, 31, 61);		//first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);		//second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);		//last left attack...

	player.SetSpriteClip(203, 142, 30, 30, 62);		//last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);		//second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);		//first right attack...

	//Set sprite sheet anchor positions...
	player.SetAnchorOffset({-16, -13}, 61);			//first left attack...
	player.SetAnchorOffset({-23, -10}, 48);			//second left attack...
	player.SetAnchorOffset({-26, -5}, 34);			//last left attack...

	player.SetAnchorOffset({4, 0}, 62);				//last right attack...
	player.SetAnchorOffset({2, -10}, 49);			//second right attack...
	player.SetAnchorOffset({-11, -13}, 35);			//first right attack...=>2

	//Setup collision...
	kakariko.ConfigureCollision(false, false);
	player.ConfigureCollision(true, true, { 0, 14 }, { 35, 16 });
	tree.ConfigureCollision(true, false);
	boulder.ConfigureCollision(false, true);
	moveTrigger.ConfigureCollision(false, false);

	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
	player.AddCollidableEntity(moveTrigger);

	moveTrigger.SetMovePos({960, 200});

	//TODO: Don't hard-code this...
	gWorld.InitWorldGrid({ 0, 70 - 35, 14, 70 - 16});
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupSprite(kakariko);
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(boulder);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	kakariko.Update();
	tree.Update();
	boulder.Update();
	player.Update();

	//Needs to come last...
	gCamera.LookAt(player);

	//gCamera.RestrictTargetToWorld(player);

	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

	sdlInit.DrawSprite(kakariko);
	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(player);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(moveTrigger);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(player);
	}
}