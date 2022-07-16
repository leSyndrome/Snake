#pragma once
#include"Configuration.h"
#include"SDL.h"
#include"Common.h"

class GridCell
{
public:
	int x, y;

	GridCell();
	GridCell(int x, int y);
	SDL_FPoint GetCellOrigin();
	void MoveTo(int x, int y);

	const GridCell operator+(const GridCell& const other);
	const bool operator==(const GridCell& const other);
	const bool operator!=(const GridCell& const other);

	GridCell GetNeighbour(Orientation toThe);
};

