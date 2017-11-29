#include "Grid.h"



Grid::Grid(Int2 size) : mSize(size) {
	mNumCells = size.x * size.y;
	mBlockedCells = new bool[mNumCells];
	mCellsBeingSearched = new queue<int>[mNumCells];
};

Grid::~Grid()
{
	delete[] mBlockedCells;
	delete[] mCellsBeingSearched;

	mBlockedCells = nullptr;
	mCellsBeingSearched = nullptr;
}

bool Grid::IsValid(Int2 cellPos) {
	//Out of grid bounds...
	if (cellPos.x < 0 || cellPos.x > mSize.x - 1) {
		return false;
	}

	if (cellPos.y < 0 || cellPos.y > mSize.y - 1) {
		return false;
	}

	int cellIndex = (cellPos.y * mSize.x) + cellPos.x;
	if (mBlockedCells[cellIndex]) {
		return false;
	}

	return true;
}

Int2 Grid::GetCellIndexFromWorldPos(Int2 worldPos) {
	return worldPos/GRID_CELL_SIZE;
}

Int2 Grid::GetCellIndexFromWorldPos(Float2 worldPos) {
	Float2 indices(worldPos / (float)GRID_CELL_SIZE);
	return Int2((int)indices.x, (int)indices.y);
}

void Grid::SetCellToBlocked(const Entity &entity) {
	Float2 topLeftCorner = Float2(entity.mPos.x + entity.mTopLeftCollOffset.x,
		entity.mPos.y + entity.mTopLeftCollOffset.y);
	Float2 bottomRightCorner = Float2(entity.mPos.x + entity.mSize.x - entity.mBottomRightCollOffset.x,
		entity.mPos.y + entity.mSize.y - entity.mBottomRightCollOffset.y);

	Int2 topLeftIndices = GetCellIndexFromWorldPos(topLeftCorner);
	Int2 bottomRightIndices = GetCellIndexFromWorldPos(bottomRightCorner);

	for (int y = topLeftIndices.y; y < bottomRightIndices.y; ++y) {
		for (int x = topLeftIndices.x; x < bottomRightIndices.x; ++x) {
			SetCellToBlocked({x, y});
		}
	}
}

void Grid::SetCellToBlocked(Int2 cellPos) {
	int cellIndex = (cellPos.y * mSize.x) + cellPos.x;
	mBlockedCells[cellIndex] = true;
}

void Grid::UnblockCell(Int2 cellPos) {
	int cellIndex = (cellPos.y * mSize.x) + cellPos.x;
	mBlockedCells[cellIndex] = false;
}

//TODO: Use later...
void Grid::AddCellBeingSearched(Int2 cellPos) {
	int cellIndex = (cellPos.y * mSize.x) + cellPos.x;
	mCellsBeingSearched[cellIndex].push(0);	//doesn't matter what to push...
}

void Grid::RemoveCellBeingSearched(Int2 cellPos) {
	int cellIndex = (cellPos.y * mSize.x) + cellPos.x;
	mCellsBeingSearched[cellIndex].pop();
}
