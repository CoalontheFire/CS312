#pragma once
#include "Sprite.h"
#include "Destructible.h"


#define ANIM_RIGHT_COUNT 2
#define ANIM_LEFT_COUNT 2
#define ANIM_UP_COUNT 2
#define ANIM_DOWN_COUNT 2
#define SQRHYPE 1.4142f	

class Guard : public Sprite, public Destructible {
public:
	Guard() { mCanBePushedBack = false; }
	virtual ~Guard() override {}

	enum GuardState { PATROL, FOLLOW, ATTACK, DEAD };

	void Update() override;
	void SetPath(vector <PathFinder::Node>);

	int lastMoveIndex = 55;
	vector<PathFinder::Node> mPath;

private:
	GuardState mLastGuardState;
	void Patrol();
	void Follow();
	void Attack();
	void Dead();
	GuardState StateControl();
	bool canSeePlayer = false;
	bool inAttackRange = false;
	int VertMovement;
	int HorizMovement;

private:
	float targetXPos{ 0.0f };
	float targetYPos{ 0.0f };
	Float2 m_wayPoint{ 0.0f,0.0f };
	int speed = 50;

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;
	float pauseTimer = 0.f;
	float maxDistance = 50.0f;

	int checkPlayerDistance();

	void movement(Float2 velocity, int *wayPoint = nullptr);

	//Animation speeds...
	float animMoveSpeed = 10;
};
