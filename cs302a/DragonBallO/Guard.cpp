#include "Guard.h"
#include "Camera.h"
#include "MyMath.h"
#include <stdlib.h>
#include <iostream>

extern float gDeltaTime;
extern Camera gCamera;
bool playerInRange = false;

using namespace std;
using namespace MyMath;

namespace {
	//Animation indices...
	int animRightIndices[ANIM_RIGHT_COUNT] = { 48,49 };
	int animLeftIndices[ANIM_LEFT_COUNT] = { 40,41 };
	int animUpIndices[ANIM_UP_COUNT] = { 33,34 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 55,56 };
}

void Guard::Update() {
	checkPlayerDistance();
	Sprite::Update();
	StateControl();

	GuardState gs = StateControl();
		switch (gs) {
		case 0:
			Patrol();
			break;
		case 1:
			Follow();
			break;
		case 2:
			Attack();
			break;
		case 3:
			Dead();
			break;
		}
}
int wayPointIteration = 1;
void Guard::Patrol() {
	if (playerInRange) {
		return;
	}
	//this sets the target to the first waypoint x and y position.
	mFollowTarget->SetToTargetPos(m_wayPoint.x, m_wayPoint.y);
	m_wayPoint = m_wayPoints[wayPointIteration];
	Float2 dir = Normalized(m_wayPoint - mPos);
	Float2 vel = dir * speed * gDeltaTime;
	
	float horizVel = Abs(vel.x);
	float vertVel = Abs(vel.y);

	//movement and sprite animations
	if (horizVel > vertVel) {
		if (vel.x > 0) {
			moveRightTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveRightTimer % ANIM_RIGHT_COUNT;
			mSpriteClipIndex = animRightIndices[index];
			lastMoveIndex = animRightIndices[0];
		}
		else {
			moveLeftTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveLeftTimer % ANIM_LEFT_COUNT;
			mSpriteClipIndex = animLeftIndices[index];
			lastMoveIndex = animLeftIndices[0];
		}
	}
	else if (vertVel > horizVel) {
		if (vel.y > 0) {
			moveDownTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveDownTimer % ANIM_DOWN_COUNT;
			mSpriteClipIndex = animDownIndices[index];
			lastMoveIndex = animDownIndices[0];
		}
		else {
			moveUpTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveUpTimer % ANIM_UP_COUNT;
			mSpriteClipIndex = animUpIndices[index];
			lastMoveIndex = animUpIndices[0];
		}
	}
	//movement(vel);
	// check if he's made it to his waypoint, then change to the next waypoint
	if (Magnitude(m_wayPoint - mPos) < .5f) {
		if (wayPointIteration < 3) {
			++wayPointIteration;
		}
		else {
			wayPointIteration = 0;
		}
	}
	movement(vel, &wayPointIteration);
}

void SetPath(vector <PathFinder::Node>) {

}

void Guard::Follow() {	
	//GetPos
	if (!playerInRange) {
		return;
	}
	mFollowTarget->SetToTargetPos(targetXPos, targetYPos);
	Float2 targetPosition{targetXPos,targetYPos};
	//aquire target position and normalize it.

	Float2 dir = Normalized(targetPosition - mPos);
	Float2 vel = dir * speed * gDeltaTime;

	float horizVel = Abs(vel.x);
	float vertVel = Abs(vel.y);
	
	//movement and sprite animations
	if (horizVel > vertVel) {
		if (vel.x > 0) {
			moveRightTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveRightTimer % ANIM_RIGHT_COUNT;
			mSpriteClipIndex = animRightIndices[index];
			lastMoveIndex = animRightIndices[0];
		}
		else {
			moveLeftTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveLeftTimer % ANIM_LEFT_COUNT;
			mSpriteClipIndex = animLeftIndices[index];
			lastMoveIndex = animLeftIndices[0];
		}
	}
	else if (vertVel > horizVel) {
		if (vel.y > 0) {
			moveDownTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveDownTimer % ANIM_DOWN_COUNT;
			mSpriteClipIndex = animDownIndices[index];
			lastMoveIndex = animDownIndices[0];
		}
		else {
			moveUpTimer += animMoveSpeed * gDeltaTime;
			int index = (int)moveUpTimer % ANIM_UP_COUNT;
			mSpriteClipIndex = animUpIndices[index];
			lastMoveIndex = animUpIndices[0];
		}
	}

	movement(vel);
}

void Guard::Attack() {
	// attack code, should take in a target.
}

void Guard::Dead() {
	// dead code, this will handle the death state sprite swap and such.
}

Guard::GuardState Guard::StateControl() {
	// series of statements that return a state value to the gs switch
	if (playerInRange) {
		return FOLLOW;
	}
	else {
		return GuardState::PATROL;
	}
}
int Guard::checkPlayerDistance() {
	mFollowTarget->SetToTargetPos(targetXPos, targetYPos);
	Float2 targetPosition{ targetXPos,targetYPos };
	if (Magnitude(targetPosition - mPos) < maxDistance) {
		playerInRange = true;
		return 1;
	}
	else if (Magnitude (targetPosition - mPos) > (maxDistance+50)){
		playerInRange = false;
		return 0;
	}

	return 0;
}
void Guard::movement(Float2 velocity, int *wayPoint) {
	Float2 vel = velocity;
	float movementLagTimer = 20.0f;
	if (GuardState::PATROL) {
		mPos += vel;
		}
	else if (GuardState::FOLLOW) {
		mPos += vel;
	}
}