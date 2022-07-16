#include<random>
#include"Game.h"
#include"Common.h"
#include"Text.h"



Game::Game() : m_Snake(GRID_WIDTH / 2, GRID_HEIGHT / 2),
			   m_Apple(RandomApple())
{
	for (GridCell snakeSegment : m_Snake.GetSegments()) {
		m_ObstacleMap[snakeSegment.x][snakeSegment.y] = OBSTACLE;
	}

}


void Game::StartTurn()
{
	// Move the tail out of the way before moving the snake
	GridCell snakeTail = m_Snake.Tail();
	m_ObstacleMap[snakeTail.x][snakeTail.y] = NO_OBSTACLE;
	// Set turn expiration
	m_TurnEnd = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(m_TurnDurationMS);
}


void Game::HandleInput()
{
	SDL_Event event;
	while (!TurnHasEnded()) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				State = Quit;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT)
					m_CurrentInput = Left;
				if (event.key.keysym.sym == SDLK_RIGHT)
					m_CurrentInput = Right;
				return;
			}
		}
	}
	m_CurrentInput = Forward;
}

void Game::MoveSnake()
{
	m_Snake.Move(m_CurrentInput, m_Apple);
}

void Game::HandleCollision()
{
	GridCell snakeHead = m_Snake.Head();
	if (m_ObstacleMap[snakeHead.x][snakeHead.y])
		State = ScoreBoard;
	else
		m_ObstacleMap[snakeHead.x][snakeHead.y] = true;
}

void Game::HandleApple()
{
	if (m_Snake.Head() == m_Apple) {
		m_Score++;
		m_Apple = RandomApple();
		SpeedUp();
	}
}

void Game::Render(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
	DrawGrid(renderer);
	if (State == Intro) {
		Text::DrawText(renderer, "start", { 4, 6 });
	}
	else if (State == Playing) {
		DrawApple(renderer);
		DrawSnake(renderer);
	}
	if (State == ScoreBoard) {
		Text::DrawText(renderer, "score", {4, 2});
		Text::DrawText(renderer, std::to_string(m_Score), {10, 10});
	}
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


void Game::Reset()
{
	m_Snake = Snake(GRID_WIDTH / 2, GRID_HEIGHT / 2);
	m_Apple = RandomApple();
	m_Score = 0;
	for (bool cellIsObstacle : m_ObstacleMap)
		cellIsObstacle = NO_OBSTACLE;
	for (GridCell snakeSegment : m_Snake.GetSegments())
		m_ObstacleMap[snakeSegment.x][snakeSegment.y] = OBSTACLE;
}



GridCell Game::RandomApple() {
	srand((unsigned int)time(NULL));
	GridCell randomApple(std::rand(), std::rand());
	while (m_ObstacleMap[randomApple.x][randomApple.y]) {
		randomApple.MoveTo(std::rand(), std::rand());
	}
	return randomApple;
}


bool Game::TurnHasEnded()
{
	return std::chrono::high_resolution_clock::now() > m_TurnEnd;
}


void Game::DrawGrid(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 20, 100, 100, 100);

	for (int x = GRID_CELL_SIZE; x < GAME_WINDOW_WIDTH; x += GRID_CELL_SIZE)
		SDL_RenderDrawLine(renderer, x, 0, x, GAME_WINDOW_HEIGHT);

	for (int y = GRID_CELL_SIZE; y < GAME_WINDOW_HEIGHT; y += GRID_CELL_SIZE)
		SDL_RenderDrawLine(renderer, 0, y, GAME_WINDOW_WIDTH, y);
}



void Game::DrawSnake(SDL_Renderer* renderer)
{
	m_Snake.Draw(renderer);
}

void Game::DrawApple(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 180, 60, 0, SDL_ALPHA_OPAQUE);
	SDL_FPoint cellOrigin = m_Apple.GetCellOrigin();
	SDL_FRect rect({ cellOrigin.x + 3, cellOrigin.y + 3, (float)(GRID_CELL_SIZE - 6), (float)(GRID_CELL_SIZE - 6) });
	SDL_RenderFillRectF(renderer, &rect);
}

void Game::SpeedUp()
{
	m_TurnDurationMS = m_TurnDurationMS * SPEEDUP_RATIO;
}

