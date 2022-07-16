#include "Text.h"


void Text::DrawText(SDL_Renderer* renderer, std::string text, GridCell offset)
{
	int i = 0;
	for (char c : text) {
		GridCell charOffset = offset;
		charOffset.x += i * ( FontWidth + FontSpace );
		DrawChar(renderer, c, charOffset);
		i++;
	}
}

void Text::DrawChar(SDL_Renderer* renderer, char c, GridCell offset)
{
	SDL_SetRenderDrawColor(renderer, 150, 150, 20, 100);
	std::vector<GridCell> fillCells = CharFillPositions[c];
	for (GridCell position : fillCells) {
		GridCell fillCell = position + offset;
		SDL_FPoint cellOrigin = fillCell.GetCellOrigin();
		SDL_FRect rect({ cellOrigin.x + 2, cellOrigin.y + 2, (float)(GRID_CELL_SIZE - 4), (float)(GRID_CELL_SIZE - 4) });
		SDL_RenderFillRectF(renderer, &rect);
	}
}

std::unordered_map<char, std::vector<GridCell>> Text::CharFillPositions{
	{ 'c' , { {1, 1}, {2, 1}, {3, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 5}, {2, 5}, {3, 5}}},
	{ 'e' , { {1, 1}, {2, 1}, {0, 2}, {3, 2}, {0, 3}, {3, 3}, {0, 4}, {1, 5}, {2, 5}, {2, 3}, {1, 3}, {3, 5}}},
	{ 's' , { {3, 1}, {2, 1}, {1, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {2, 5}, {1, 5}, {0, 5}}},
	{ 'o' , { {1, 1}, {2, 1}, {0, 2}, {3, 2}, {0, 3}, {3, 3}, {3, 3}, {0, 4}, {3, 4}, {1, 5}, {2, 5}}},
	{ 't' , { {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 5}, {3, 4}, {0, 1}, {2, 1}, {3, 1}}},
	{ 'a' , { {1, 1}, {2, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {2, 5}, {1, 5}, {0, 4}, {1, 3}, {2, 3}}},
	{ 'r' , { {3, 1}, {2, 1}, {1, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}} },
	{ '1' , { {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5} }},
	{ '2' , { {0, 2}, {1, 1}, {2, 1}, {3, 2}, {2, 3}, {1, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}}},
	{ '3' , { {0, 2}, {1, 1}, {2, 1}, {3, 2}, {2, 3}, {3, 4}, {1, 5}, {2, 5}, {0, 4}}},
	{ '4' , { {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}}},
	{ '5' , { {3, 1}, {2, 1}, {1, 1}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 4}, {2, 5}, {1, 5}, {0, 5}}},
	{ '6' , { {2, 1}, {1, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 5}, {2, 5}, {3, 4}, {2, 3}, {1, 3}}},
	{ '7' , { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {3, 2}, {2, 3}, {1, 4}, {1, 5}}},
	{ '8' , { {1, 1}, {2, 1}, {0, 2}, {3, 2}, {1, 3}, {2, 3}, {0, 4}, {3, 4}, {1, 5}, {2, 5}}},
	{ '9' , { {1, 1}, {2, 1}, {0, 2}, {3, 2}, {1, 3}, {2, 3}, {3, 3}, {3, 4}, {2, 5}, {1, 5}, }},
	{ '0' , { {1, 1}, {2, 1}, {0, 2}, {3, 2}, {0, 3}, {3, 3}, {3, 3}, {0, 4}, {3, 4}, {1, 5}, {2, 5}}},
};