#include<iostream>
#include <vector>
#include"SDL.h"
#include"SDL_main.h"
#include"Game.h"
#include"Configuration.h"



int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = SDL_CreateWindow("Snake",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			GAME_WINDOW_WIDTH,
			GAME_WINDOW_HEIGHT,
			0);
		if (window) {
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer) {

				Game game;
				while (game.State != Quit) {
					if (game.State == Playing) {
						game.StartTurn();
						game.HandleInput();
						game.MoveSnake();
						game.HandleCollision();
						game.HandleApple();
					}
					else {
						SDL_Event event;
						if (SDL_PollEvent(&event)) {
							if (event.type == SDL_QUIT) {
								game.State = Quit;
							}
							else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
								if (game.State == ScoreBoard)
									game.Reset();
								game.State = Playing;
							}
						}
					}
					game.Render(renderer);
				}

				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
			}
		}

	}

	return 0;

}
