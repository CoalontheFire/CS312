#pragma once
#include <string>
#include <SDL_image.h>
#include "MyMath.h"
#include <vector>

class Entity {

	friend class SDLInit;
	friend class Camera;
	friend class Grid;

public:
	using UInt = unsigned int;
	using Int2 = MyMath::Int2;
	using Float2 = MyMath::Float2;
	using UByte = MyMath::UByte;

public:
	//Needs to be virtual so that derived destructor gets called...
	virtual ~Entity() {};

public:
	virtual void Update();
	Float2 mPos;
	void SetPosition(Float2 pos);
	std::vector<Float2> m_wayPoints;
	void SetSize(int width, int height);
	void SetMoveSpeed(float moveSpeed);

	void ConfigureCollision(bool canPushBack, bool canBePushedBack,
		Int2 topLeftCollOffset = { 0, 0 }, Int2 bottomRightCollOffset = { 0, 0 });

	void AddCollidableEntity(Entity &entity);

	void SetToTargetPos(float &xPos, float &yPos) {
		xPos = mPos.x;
		yPos = mPos.y;
	}

	void SetFollowTarget(Entity *followTarget) {
		mFollowTarget = followTarget;
	}
	void SetWaypointTargets(std::vector<Float2> wayPoints) {
		m_wayPoints = wayPoints;
	}

private:
	void CheckCollision();

protected:
	virtual void OnCollision(Entity *other);

protected:
	
	Int2 mSize;
	Int2 mTopLeftCollOffset;
	Int2 mBottomRightCollOffset;

	UByte mPushbackSides{ 0 };

	//If this entity can move, it needs a move speed...
	float mMoveSpeed{ 140.f };
	float mMoveSpeedAI{ 110.f };

	//For collision...
	std::vector<Entity*> mCollidableEntities;
	bool mCanPushBack{ false };
	bool mCanBePushedBack{ false };
	int mHasCollided{ false };

	Entity* mFollowTarget = nullptr;
};
