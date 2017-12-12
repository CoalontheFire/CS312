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
	Sprite dungeonOverpass;
	MoveTrigger moveTriggerDungeonEntrance01;
	MoveTrigger moveTriggerDungeonEntrance02;
	MoveTrigger moveTriggerDungeonEntrance03;
	MoveTrigger moveTriggerDungeonExit01;
	MoveTrigger moveTriggerDungeonExit02;
	MoveTrigger moveTriggerDungeonExit03;
	Entity colliderPrefab; ///Prefabs will be grouped by numbers, currently they are all diagonal cliffs
	Entity colliderPrefab01;
	Entity colliderPrefab02;
	Entity colliderPrefab03;
	Entity colliderPrefab04;
	Entity colliderPrefab05;
	Entity colliderCliff01;
	Entity colliderHedge01;
	Entity colliderHedge02;
	Entity colliderHedge03;
	Entity colliderHouse01;
	Entity colliderWoods01;
	Entity colliderWoods02;
	Entity colliderWoods03;
	Entity colliderDungeonWallRight01; /// 1 Is dungeon path
	Entity colliderDungeonWallLeft01;
	Entity colliderDungeonWallTop01;
	Entity colliderDungeonWallBot01;
	Entity colliderDungeonWallBot02; ///the left and right sides of the treasure cave
	Entity colliderDungeonWallBot03;
	Entity colliderDungeonWallLeft02;
	Entity colliderDungeonWallTop02; /// 2 Is Treasure Cave

}



void InitEntities() {
	//Setting path names...
	kakariko.SetTexturePath("textures/mapVillage_kakariko.png");
	player.SetTexturePath("textures/link_sheet.png");
	//tree.SetTexturePath("textures/tree_green.gif");
	boulder.SetTexturePath("textures/boulder.png");
	leftForest.SetTexturePath("textures/map_leftForest.png");
	dungeonOverpass.SetTexturePath("textures/map_dungeonOverpass.png");

	//Loading textures...
	sdlInit.LoadTexture(kakariko);
	sdlInit.LoadTexture(player);
	//sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(boulder);
	sdlInit.LoadTexture(leftForest);
	sdlInit.LoadTexture(dungeonOverpass);

	//Setting position information...
	kakariko.SetPosition({ 0, 0 });
	leftForest.SetPosition({ 0, 0});
	player.SetPosition({260, 25});
	//tree.SetPosition({200, 300});
	boulder.SetPosition({360, 480});
	dungeonOverpass.SetPosition({ 4301, 1329 });
	moveTriggerDungeonEntrance01.SetPosition({ 176, 460 });
	moveTriggerDungeonEntrance02.SetPosition({ 2641, 1585 });
	moveTriggerDungeonEntrance03.SetPosition({ 2573, 1515 });
	moveTriggerDungeonExit01.SetPosition({ 4535, 2386 });
	moveTriggerDungeonExit02.SetPosition({ 4350, 865 });
	moveTriggerDungeonExit03.SetPosition({4400, 400});

	//Setting size information...
	kakariko.SetSize(5080, 5080);
	leftForest.SetSize(160, 1926);
	player.SetSize(70, 70);
	//tree.SetSize(64, 78);
	boulder.SetSize(45, 45);
	moveTriggerDungeonEntrance01.SetSize(30, 30);
	moveTriggerDungeonEntrance02.SetSize(30, 30);
	moveTriggerDungeonEntrance03.SetSize(40, 30);
	moveTriggerDungeonExit01.SetSize(30, 30);
	moveTriggerDungeonExit02.SetSize(30, 30);
	moveTriggerDungeonExit03.SetSize(30,30);
	dungeonOverpass.SetSize(509, 130);

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

	player.SetSpriteClip(0, 245, 35, 35, 30);		//first left attack...
	player.SetSpriteClip(105, 245, 35, 35, 33);		//middle left attack...
	player.SetSpriteClip(175, 245, 35, 35, 36);		//last left attack...

	player.SetSpriteClip(0, 210, 35, 35, 39);		//last right attack...
	player.SetSpriteClip(105, 210, 35, 35, 42);		//second right attack...
	player.SetSpriteClip(175, 210, 35, 35, 45);		//first right attack...

	player.SetSpriteClip(0, 175, 35, 35, 48);		//first up attack...
	player.SetSpriteClip(105, 175, 35, 35, 51);		//middle up attack...
	player.SetSpriteClip(175, 175, 35, 35, 54);		//last up attack...

	player.SetSpriteClip(0, 140, 35, 35, 57);		//last down attack...
	player.SetSpriteClip(105, 140, 35, 35, 60);		//second down attack...
	player.SetSpriteClip(175, 140, 35, 35, 63);		//first down attack...

	////Set sprite sheet anchor positions...
	player.SetAnchorOffset({0, -3}, 30);			//first left attack...
	player.SetAnchorOffset({-35 , -3}, 33);			//second left attack...
	player.SetAnchorOffset({-30, -3}, 36);			//last left attack...

	player.SetAnchorOffset({0, -3}, 39);			//last right attack...
	player.SetAnchorOffset({-6, -8}, 42);			//second right attack...
	player.SetAnchorOffset({0, -3}, 45);			//first right attack...=>2

	player.SetAnchorOffset({ 0, -26 }, 48);			//first up attack...
	player.SetAnchorOffset({ 0 , -18 }, 51);		//second up attack...
	player.SetAnchorOffset({ -20, -26 }, 54);		//last up attack...

	player.SetAnchorOffset({ -14, 0 }, 57);			//last down attack...
	player.SetAnchorOffset({ -6, -6 }, 60);			//second down attack...
	player.SetAnchorOffset({ 0, -6 }, 63);			//first down attack...=>2

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Setup collision...
	kakariko.ConfigureCollision(false, false);
	leftForest.ConfigureCollision(true, false);
	player.ConfigureCollision(true, true, { 0, 14 }, { 35, 16 });
	//tree.ConfigureCollision(true, false);
	boulder.ConfigureCollision(true, true);
	moveTriggerDungeonEntrance01.ConfigureCollision(false, false);
	dungeonOverpass.ConfigureCollision(false, false);

	//player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
	player.AddCollidableEntity(leftForest);
	player.AddCollidableEntity(moveTriggerDungeonEntrance01);
	player.AddCollidableEntity(moveTriggerDungeonEntrance02);
	player.AddCollidableEntity(moveTriggerDungeonEntrance03);
	player.AddCollidableEntity(moveTriggerDungeonExit01);
	player.AddCollidableEntity(moveTriggerDungeonExit02);
	player.AddCollidableEntity(moveTriggerDungeonExit03);

	moveTriggerDungeonEntrance01.SetMovePos({ 4380, 865 });
	moveTriggerDungeonEntrance02.SetMovePos({ 4535, 2305 });
	moveTriggerDungeonEntrance03.SetMovePos({ 4400, 340 });
	moveTriggerDungeonExit01.SetMovePos({ 2640, 1625 });
	moveTriggerDungeonExit02.SetMovePos({ 176, 490 });
	moveTriggerDungeonExit03.SetMovePos({ 2573, 1559 });

	//---------------------------------------COLLIDERS------------------------------------------------//

	colliderCliff01.SetPosition({160, 346});
	colliderHedge01.SetPosition({640, 240});
	colliderHedge02.SetPosition({960, 240});
	colliderHedge03.SetPosition({1504, 280});
	colliderHouse01.SetPosition({960, 320});
	colliderWoods01.SetPosition({320, 1});
	colliderWoods02.SetPosition({704, 1});
	colliderWoods03.SetPosition({1696, 1});
	colliderDungeonWallRight01.SetPosition({ 4575, 0 });
	colliderDungeonWallLeft01.SetPosition({ 4500, 900 });   
	colliderDungeonWallLeft02.SetPosition({ 4192,  0 });
	colliderDungeonWallBot01.SetPosition({ 4339, 900 });
	colliderDungeonWallBot02.SetPosition({ 4256, 352 });
	colliderDungeonWallBot03.SetPosition({ 4436, 352 });
	colliderDungeonWallTop01.SetPosition({ 4339, 820 });
	colliderDungeonWallTop02.SetPosition({ 4192, 0 });
	colliderPrefab.SetPosition({ 260, 370 });
	colliderPrefab01.SetPosition({ 300, 400 });
	colliderPrefab02.SetPosition({ 360, 410 });
	colliderPrefab03.SetPosition({ 405, 410 });
	colliderPrefab04.SetPosition({ 463, 400 });
	colliderPrefab05.SetPosition({ 493, 364 });
	
	colliderCliff01.SetSize(96, 100);
	colliderHedge01.SetSize(220, 40);
	colliderHedge02.SetSize(574, 40);
	colliderHedge03.SetSize(30, 160);
	colliderHouse01.SetSize(190, 124);
	colliderWoods01.SetSize(320, 160);
	colliderWoods02.SetSize(800, 160);
	colliderWoods03.SetSize(301, 160);
	colliderDungeonWallRight01.SetSize(100, 2430);
	colliderDungeonWallLeft01.SetSize(35, 1530);
	colliderDungeonWallLeft02.SetSize(62, 414);
	colliderDungeonWallBot01.SetSize(161, 35);
	colliderDungeonWallBot02.SetSize(138, 63);
	colliderDungeonWallBot03.SetSize(142, 63);
	colliderDungeonWallTop01.SetSize(236, 35);
	colliderDungeonWallTop02.SetSize(383, 63);
	colliderPrefab.SetSize(30, 110);
	colliderPrefab01.SetSize(60, 105);
	colliderPrefab02.SetSize(45, 53);
	colliderPrefab03.SetSize(60, 100);
	colliderPrefab04.SetSize(30, 89);
	colliderPrefab05.SetSize(25, 86);
	
	colliderCliff01.ConfigureCollision(true, false);
	colliderHedge01.ConfigureCollision(true, false);
	colliderHedge02.ConfigureCollision(true, false);
	colliderHedge03.ConfigureCollision(true, false);
	colliderHouse01.ConfigureCollision(true, false);
	colliderWoods01.ConfigureCollision(true, false);
	colliderWoods02.ConfigureCollision(true, false);
	colliderWoods03.ConfigureCollision(true, false);
	colliderDungeonWallRight01.ConfigureCollision(true, false);
	colliderDungeonWallLeft01.ConfigureCollision(true, false);
	colliderDungeonWallLeft02.ConfigureCollision(true, false);
	colliderDungeonWallBot01.ConfigureCollision(true, false);
	colliderDungeonWallBot02.ConfigureCollision(true, false);
	colliderDungeonWallBot03.ConfigureCollision(true, false);
	colliderDungeonWallTop01.ConfigureCollision(true, false);
	colliderDungeonWallTop02.ConfigureCollision(true, false);
	colliderPrefab.ConfigureCollision(true, false);
	colliderPrefab01.ConfigureCollision(true, false);
	colliderPrefab02.ConfigureCollision(true, false);
	colliderPrefab03.ConfigureCollision(true, false);
	colliderPrefab04.ConfigureCollision(true, false);
	colliderPrefab05.ConfigureCollision(true, false);
	
	
	player.AddCollidableEntity(colliderCliff01);
	player.AddCollidableEntity(colliderHedge01);
	player.AddCollidableEntity(colliderHedge02);
	player.AddCollidableEntity(colliderHedge03);
	player.AddCollidableEntity(colliderHouse01);
	player.AddCollidableEntity(colliderWoods01);
	player.AddCollidableEntity(colliderWoods02);
	player.AddCollidableEntity(colliderWoods03);
	player.AddCollidableEntity(colliderDungeonWallRight01);
	player.AddCollidableEntity(colliderDungeonWallLeft01);
	player.AddCollidableEntity(colliderDungeonWallLeft02);
	player.AddCollidableEntity(colliderDungeonWallBot01);
	player.AddCollidableEntity(colliderDungeonWallBot02);
	player.AddCollidableEntity(colliderDungeonWallBot03);
	player.AddCollidableEntity(colliderDungeonWallTop01);
	player.AddCollidableEntity(colliderDungeonWallTop02);
	player.AddCollidableEntity(colliderPrefab);
	player.AddCollidableEntity(colliderPrefab01);
	player.AddCollidableEntity(colliderPrefab02);
	player.AddCollidableEntity(colliderPrefab03);
	player.AddCollidableEntity(colliderPrefab04);
	player.AddCollidableEntity(colliderPrefab05);
	boulder.AddCollidableEntity(colliderPrefab01);
	boulder.AddCollidableEntity(colliderPrefab02);
	boulder.AddCollidableEntity(colliderPrefab03);
	boulder.AddCollidableEntity(colliderPrefab04);
	boulder.AddCollidableEntity(colliderPrefab05);
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
	sdlInit.CleanupSprite(dungeonOverpass);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	kakariko.Update();
	leftForest.Update();
	tree.Update();
	boulder.Update();
	player.Update();
	dungeonOverpass.Update();

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
	sdlInit.DrawSprite(dungeonOverpass);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(moveTriggerDungeonEntrance01);
		sdlInit.DrawEntityCollider(moveTriggerDungeonEntrance02);
		sdlInit.DrawEntityCollider(moveTriggerDungeonEntrance03);
		sdlInit.DrawEntityCollider(moveTriggerDungeonExit01);
		sdlInit.DrawEntityCollider(moveTriggerDungeonExit02);
		sdlInit.DrawEntityCollider(moveTriggerDungeonExit03);
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
		sdlInit.DrawEntityCollider(colliderDungeonWallRight01);
		sdlInit.DrawEntityCollider(colliderDungeonWallLeft01);
		sdlInit.DrawEntityCollider(colliderDungeonWallLeft02);
		sdlInit.DrawEntityCollider(colliderDungeonWallBot01);
		sdlInit.DrawEntityCollider(colliderDungeonWallBot02);
		sdlInit.DrawEntityCollider(colliderDungeonWallBot03);
		sdlInit.DrawEntityCollider(colliderDungeonWallTop01);
		sdlInit.DrawEntityCollider(colliderDungeonWallTop02);
		sdlInit.DrawEntityCollider(colliderPrefab);
		sdlInit.DrawEntityCollider(colliderPrefab01);
		sdlInit.DrawEntityCollider(colliderPrefab02);
		sdlInit.DrawEntityCollider(colliderPrefab03);
		sdlInit.DrawEntityCollider(colliderPrefab04);
		sdlInit.DrawEntityCollider(colliderPrefab05);
	}
}