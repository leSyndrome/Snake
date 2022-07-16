#pragma once
#include"SDL.h"
#include"GridCell.h"
#include <unordered_map>
#include <vector>

static class Text
{
public:
	static const int FontHeight = 6;
	static const int FontWidth = 4;
	static const int FontSpace = 1;
	static void DrawText(SDL_Renderer* renderer, std::string text, GridCell offset);


private:
	static void DrawChar(SDL_Renderer* renderer, char c, GridCell offset);
	static std::unordered_map<char, std::vector<GridCell>> CharFillPositions;

};
