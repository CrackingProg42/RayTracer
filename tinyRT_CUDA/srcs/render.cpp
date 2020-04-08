
#include "tinyRT.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

static SDL_Event event;
static SDL_Renderer *renderer;
static SDL_Window *window;

void initSDL() {
	SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(W*2, H*2, 0, &window, &renderer);
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

void loopSDL() {
    while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
	}
}

void render(Vector3 **pix, int s) {
	for (int col = 0; col < W*2; col = col + 2) {
		for (int row = 0; row < H*2; row = row + 2) {
			SDL_SetRenderDrawColor(renderer, std::min((int)(pix[(int)(col / 2)][(int)(row / 2)].x / (s + 1)), 255), std::min((int)(pix[(int)(col / 2)][(int)(row / 2)].y / (s + 1)), 255), std::min((int)(pix[(int)(col / 2)][(int)(row / 2)].z / (s + 1)), 255), 255);
			SDL_RenderDrawPoint(renderer, col, row);
			SDL_RenderDrawPoint(renderer, col, row + 1);
			SDL_RenderDrawPoint(renderer, col + 1, row);
			SDL_RenderDrawPoint(renderer, col + 1, row + 1);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_SetWindowTitle(window, std::to_string(s).c_str());
}