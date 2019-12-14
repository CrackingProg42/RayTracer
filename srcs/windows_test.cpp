/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:16:21 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/12/14 15:19:25 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "global.hpp"
#include "Camera/Camera.hpp"
#include <stdlib.h>
#include "OBJ/Obj.hpp"

std::map<int, Vector>				g_normal;				// must start at index 1 !!
std::map<int, Vector>				g_uvs;					// must start at index 1 !!
std::map<int, Vector>				g_vertex;				// must start at index 1 !!
std::map<std::string, Material>		materials;			// list of all material

// example with a circle
void render(SDL_Renderer *renderer, Obj obj, Camera cam)
{
	Ray r;
	Hit h = Hit(INFINITY, Vector(42));


	for (int y = 0; y < IMAGE_H; y++)
	{
		for (int x = 0; x < IMAGE_W; x++)
		{
			/*if (x%8 == 0 && y%8 == 0)
			{
				r = cam.cast_ray(x, y);
				h = obj.intersect(r);
			}*/
			if (h.get_t() != INFINITY)
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			else
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			for (int i = 0; i < 8; i++)
				SDL_RenderDrawPoint(renderer, x, y + i);
		}
	}
	SDL_RenderPresent(renderer);
}


int main(int ac, char **av) 
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
	Obj 	obj(av[1], 100);
	Camera	cam(Vector(0, 0, 500), Vector(0, 1, 0), 90, Vector(0, 1, 0));
    int i;
	
	std::cout << obj;
	
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(IMAGE_W, IMAGE_W, 0, &window, &renderer);
    render(renderer, obj, cam);
	while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
    return EXIT_SUCCESS;
}