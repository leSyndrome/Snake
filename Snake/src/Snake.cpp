#include"Snake.h"

Snake::Snake()
{
	m_Segments.push_back(GridCell(0, 2)); //head
	m_Segments.push_back(GridCell(0, 1));
	m_Segments.push_back(GridCell(0, 0)); //tail
	m_Orientation = South;
}

Snake::Snake(int headX, int headY)
{
	m_Segments.push_back(GridCell(headX, headY)); //head
	m_Segments.push_back(GridCell(headX, headY + 1));
	m_Segments.push_back(GridCell(headX, headY + 2)); //tail
	m_Orientation = North;
}

void Snake::Move(Direction dir, const GridCell& apple)
{
	m_Orientation = (Orientation)((m_Orientation + dir + OrientationsCount) % OrientationsCount);
	GridCell newHead = m_Segments.front().GetNeighbour(m_Orientation);
	if (newHead != apple)
		m_Segments.pop_back();

	m_Segments.push_front(newHead);
}


void Snake::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 150, 150, 20, 100);
	for (GridCell segment : m_Segments)
	{
		DrawSegment(renderer, segment);
	}
}

void Snake::DrawSegment(SDL_Renderer* renderer, GridCell segment)
{
	SDL_FPoint cellOrigin = segment.GetCellOrigin();
	SDL_FRect rect({ cellOrigin.x + 2, cellOrigin.y + 2, (float)(GRID_CELL_SIZE - 4), (float)(GRID_CELL_SIZE - 4) });
	SDL_RenderFillRectF(renderer, &rect);
}

std::list<GridCell> Snake::GetSegments()
{
	return m_Segments;
}

GridCell Snake::Head()
{
	return m_Segments.front();
}

GridCell Snake::Tail()
{
	return m_Segments.back();
}



