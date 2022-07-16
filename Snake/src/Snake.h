#pragma once
#include<list>
#include"SDL.h"
#include"SDL_main.h"
#include"Common.h"
#include"GridCell.h"



class Snake
{
public:
	Snake();
	Snake(int headX, int headY);

	GridCell Head();
	GridCell Tail();
	std::list<GridCell> GetSegments();

	void Move(Direction dir, const GridCell& apple);
	void Draw(SDL_Renderer* renderer);
	void DrawSegment(SDL_Renderer* renderer, GridCell segment);

private:
	Orientation m_Orientation;
	std::list<GridCell> m_Segments;
};

