/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:16:21 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/12/11 12:05:18 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "global.hpp"
#include <stdlib.h>
#include "OBJ/Obj.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

std::map<int, Vector>				g_normal;				// must start at index 1 !!
std::map<int, Vector>				g_uvs;					// must start at index 1 !!
std::map<int, Vector>				g_vertex;				// must start at index 1 !!
std::map<std::string, Material>		materials;			// list of all material

// example with a circle
/*void render(SDL_Renderer *renderer, Vector circle_pos)
{
	SDL_RenderClear(renderer);
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			if (circle_pos.dist(Vector(x, y, 0)) < 200)
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			else
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}
*/

int main(int ac, char **av) 
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
	Obj 	obj(av[1]);
    int i;
	
	// std::cout << obj;

	exit(0);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    while (1) {
		// render(renderer, Vector(500, 500, 0));
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
    return EXIT_SUCCESS;
}