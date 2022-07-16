#include "GridCell.h"


GridCell::GridCell() : x(0), y(0) {};
GridCell::GridCell(int x, int y) : x((x + GRID_WIDTH) % GRID_WIDTH), y((y + GRID_HEIGHT) % GRID_HEIGHT) {};

SDL_FPoint GridCell::GetCellOrigin()
{
	return SDL_FPoint({ (float)(GRID_CELL_SIZE * x), (float)(GRID_CELL_SIZE * y) });
}

void GridCell::MoveTo(int x, int y)
{
	this->x = (x + GRID_WIDTH) % GRID_WIDTH;
	this->y = (y + GRID_HEIGHT) % GRID_HEIGHT;
}

GridCell GridCell::GetNeighbour(Orientation toThe)
{
	if (toThe == North)
		return GridCell(x, y - 1);
	if (toThe == East)
		return GridCell(x + 1, y);
	if (toThe == South)
		return GridCell(x, y + 1);
	if (toThe == West)
		return GridCell(x - 1, y);
}


const GridCell GridCell::operator+(const GridCell& const other) {
	return GridCell(x + other.x, y + other.y);
}

const bool GridCell::operator==(const GridCell& const other) {
	return x == other.x && y == other.y;
}

const bool GridCell::operator!=(const GridCell& const other) {
	return x != other.x || y != other.y;
}