#include <iostream>
#include <Windows.h>

#pragma comment(lib, "Winmm.lib")

#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"

#define CAMERA_MODE Camera::Mode::FOLLOW
#define SHOW_COLLIDERS false


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
	Sprite leftForest;
	MoveTrigger moveTrigger;
	Entity colliderPrefab;
	Entity colliderCliff01;
	Entity colliderHedge01;
	Entity colliderHedge02;
	Entity colliderHedge03;
	Entity colliderHouse01;
	Entity colliderWoods01;
	Entity colliderWoods02;
	Entity colliderWoods03;
}



void InitEntities() {
	//Setting path names...
	kakariko.SetTexturePath("textures/mapVillage_kakariko.png");
	player.SetTexturePath("textures/link_sheet.png");
	//tree.SetTexturePath("textures/tree_green.gif");
	boulder.SetTexturePath("textures/boulder.png");
	leftForest.SetTexturePath("textures/map_leftForest.png");

	//Loading textures...
	sdlInit.LoadTexture(kakariko);
	sdlInit.LoadTexture(player);
	//sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(boulder);
	sdlInit.LoadTexture(leftForest);

	//Setting position information...
	kakariko.SetPosition({ 0, 0 });
	leftForest.SetPosition({ 0, 0});
	player.SetPosition({260, 25});
	//tree.SetPosition({200, 300});
	boulder.SetPosition({360, 480});
	moveTrigger.SetPosition({176, 460});

	//Setting size information...
	kakariko.SetSize(3080, 3080);
	leftForest.SetSize(160, 1926);
	player.SetSize(70, 70);
	//tree.SetSize(64, 78);
	boulder.SetSize(45, 45);
	moveTrigger.SetSize(30,30);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Set sprite sheet texture coordinates...
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(105, 35, 30, 30, 1);			//up...
	player.SetSpriteClip(1, 35, 30, 30, 2);		//up move 1...
	player.SetSpriteClip(35, 35, 30, 30, 3);		//up move 2...
	player.SetSpriteClip(70, 35, 30, 30, 4);		//up move 3...
	player.SetSpriteClip(140, 35, 30, 30, 5);		//up move 4...
	player.SetSpriteClip(175, 35, 30, 30, 6);		//up move 5...
	player.SetSpriteClip(210, 35, 30, 30, 7);		//up move 5...

	player.SetSpriteClip(105, 70, 30, 30, 8);		//right...
	player.SetSpriteClip(1, 70, 30, 30, 9);			//right move 1...
	player.SetSpriteClip(35, 70, 30, 30, 10);		//right move 2...
	player.SetSpriteClip(70, 70, 30, 30, 11);		//right move 3...
	player.SetSpriteClip(140, 70, 30, 30, 12);		//right move 4...
	player.SetSpriteClip(175, 70, 30, 30, 13);		//up move 5...
	player.SetSpriteClip(210, 70, 30, 30, 14);		//right move 5...

	player.SetSpriteClip(105, 1, 30, 30, 15);			//down...
	player.SetSpriteClip(1, 1, 30, 30, 16);			//down move 1...
	player.SetSpriteClip(35, 1, 30, 30, 17);		//down move 2...
	player.SetSpriteClip(70, 1, 30, 30, 18);		//down move 3...
	player.SetSpriteClip(140, 1, 30, 30, 19);		//down move 4...
	player.SetSpriteClip(175, 1, 30, 30, 20);		//up move 5...
	player.SetSpriteClip(210, 1, 30, 30, 21);		//down move 5...

	player.SetSpriteClip(105, 105, 30, 30, 22);			//left...
	player.SetSpriteClip(1, 105, 30, 30, 23);			//left move 1...
	player.SetSpriteClip(35, 105, 30, 30, 24);		//left move 2...
	player.SetSpriteClip(70, 105, 30, 30, 25);		//left move 3...
	player.SetSpriteClip(140, 105, 30, 30, 26);		//left move 4...
	player.SetSpriteClip(175, 105, 30, 30, 27);		//down move 5...
	player.SetSpriteClip(210, 105, 30, 30, 28);		//left move 5...

	//TODO: Animations for Attack

	//player.SetSpriteClip(170, 141, 30, 31, 61);		//first left attack...
	//player.SetSpriteClip(173, 109, 30, 30, 48);		//second left attack...
	//player.SetSpriteClip(173, 71, 30, 30, 34);		//last left attack...

	//player.SetSpriteClip(203, 142, 30, 30, 62);		//last right attack...
	//player.SetSpriteClip(203, 109, 30, 30, 49);		//second right attack...
	//player.SetSpriteClip(203, 77, 30, 31, 35);		//first right attack...

	////Set sprite sheet anchor positions...
	//player.SetAnchorOffset({-16, -13}, 61);			//first left attack...
	//player.SetAnchorOffset({-23, -10}, 48);			//second left attack...
	//player.SetAnchorOffset({-26, -5}, 34);			//last left attack...

	//player.SetAnchorOffset({4, 0}, 62);				//last right attack...
	//player.SetAnchorOffset({2, -10}, 49);			//second right attack...
	//player.SetAnchorOffset({-11, -13}, 35);			//first right attack...=>2

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Setup collision...
	kakariko.ConfigureCollision(false, false);
	leftForest.ConfigureCollision(true, false);
	player.ConfigureCollision(true, true, { 0, 14 }, { 35, 16 });
	//tree.ConfigureCollision(true, false);
	boulder.ConfigureCollision(false, true);
	moveTrigger.ConfigureCollision(false, false);

	//player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
	player.AddCollidableEntity(leftForest);
	player.AddCollidableEntity(moveTrigger);

	moveTrigger.SetMovePos({960, 200});

	//---------------------------------------COLLIDERS------------------------------------------------//

	colliderCliff01.SetPosition({160, 346});
	colliderHedge01.SetPosition({640, 240});
	colliderHedge02.SetPosition({960, 240});
	colliderHedge03.SetPosition({1504, 280});
	colliderHouse01.SetPosition({960, 320});
	colliderWoods01.SetPosition({320, 1});
	colliderWoods02.SetPosition({704, 1});
	colliderWoods03.SetPosition({1696, 1});
	
	colliderCliff01.SetSize(96, 100);
	colliderHedge01.SetSize(220, 40);
	colliderHedge02.SetSize(574, 40);
	colliderHedge03.SetSize(30, 160);
	colliderHouse01.SetSize(190, 124);
	colliderWoods01.SetSize(320, 160);
	colliderWoods02.SetSize(800, 160);
	colliderWoods03.SetSize(301, 160);
	
	colliderCliff01.ConfigureCollision(true, false);
	colliderHedge01.ConfigureCollision(true, false);
	colliderHedge02.ConfigureCollision(true, false);
	colliderHedge03.ConfigureCollision(true, false);
	colliderHouse01.ConfigureCollision(true, false);
	colliderWoods01.ConfigureCollision(true, false);
	colliderWoods02.ConfigureCollision(true, false);
	colliderWoods03.ConfigureCollision(true, false);
	
	
	player.AddCollidableEntity(colliderCliff01);
	player.AddCollidableEntity(colliderHedge01);
	player.AddCollidableEntity(colliderHedge02);
	player.AddCollidableEntity(colliderHedge03);
	player.AddCollidableEntity(colliderHouse01);
	player.AddCollidableEntity(colliderWoods01);
	player.AddCollidableEntity(colliderWoods02);
	player.AddCollidableEntity(colliderWoods03);

	//------------------------------------------------------------------------------------------------//

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
	sdlInit.CleanupSprite(leftForest);
	sdlInit.CleanupSprite(kakariko);
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(boulder);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	kakariko.Update();
	leftForest.Update();
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
	sdlInit.DrawSprite(leftForest);
	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(player);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(moveTrigger);
		sdlInit.DrawEntityCollider(colliderHedge01);
		sdlInit.DrawEntityCollider(colliderHedge02);
		sdlInit.DrawEntityCollider(colliderHedge03);
		sdlInit.DrawEntityCollider(colliderWoods01);
		sdlInit.DrawEntityCollider(colliderWoods02);
		sdlInit.DrawEntityCollider(colliderWoods03);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(player);
		sdlInit.DrawEntityCollider(leftForest);
	}
}