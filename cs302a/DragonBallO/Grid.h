#pragma once
#include "MyMath.h"
#include <queue>
#include "Entity.h"
#include "PathFinder.h"

using namespace MyMath;
using namespace std;

extern const int GRID_CELL_SIZE;

class Grid
{
public:
	Grid(Int2 size);
	~Grid();

public:
	void SetCellToBlocked(const Entity &entity);
	void SetCellToBlocked(Int2 cellPos);
	void UnblockCell(Int2 cellPos);
	void AddCellBeingSearched(Int2 cellPos);
	void RemoveCellBeingSearched(Int2 cellPos);
	bool IsValid(Int2 cellPos);

	

	Int2 GetCellIndexFromWorldPos(Int2 worldPos);
	Int2 GetCellIndexFromWorldPos(Float2 worldPos);

private:
	Int2 mSize;
	int mNumCells;
	bool *mBlockedCells = nullptr;
	queue<int> *mCellsBeingSearched = nullptr;
};

