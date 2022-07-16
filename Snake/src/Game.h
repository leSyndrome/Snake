#pragma once
#include <chrono>
#include <string>
#include"Snake.h"

enum GameState {
	Intro,
	Playing,
	ScoreBoard,
	Quit
};

const bool OBSTACLE = true;
const bool NO_OBSTACLE = false;

using TimePoint = std::chrono::steady_clock::time_point;
class Game
{
public:
	GameState State = Intro;

	Game();
	void StartTurn();
	void HandleInput();
	void MoveSnake();
	void HandleCollision();
	void HandleApple();
	void Render(SDL_Renderer* renderer);
	void Reset();

private:	
	int m_Score = 0;

	Snake m_Snake;
	GridCell m_Apple;
	bool m_ObstacleMap[GRID_WIDTH][GRID_HEIGHT] = { NO_OBSTACLE };
	

	int m_TurnDurationMS = DEFAULT_TURN_DURATION_MS;
	TimePoint m_TurnEnd;
	Direction m_CurrentInput = Forward;

	GridCell RandomApple();
	bool TurnHasEnded();
	void DrawSnake(SDL_Renderer* renderer);
	void DrawApple(SDL_Renderer* renderer);
	void DrawGrid(SDL_Renderer* renderer);
	void SpeedUp();

};
