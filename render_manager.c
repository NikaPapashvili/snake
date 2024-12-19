#include "snake.h"

void	clean_render(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font)
{
   	TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit(); 
}

void set_render_color(SDL_Renderer *renderer, int color[4])
{
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
}

int	init_render(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        return 0;
    }

    // Create window
    *window = SDL_CreateWindow(
		"SDL2 Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		CELL_SIZE * (MAP_W + 2 * SIDES), CELL_SIZE * (BANNER_H + MAP_H + SIDES),
		SDL_WINDOW_SHOWN
	);
    if (!(*window)) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create renderer
   *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!(*renderer)) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Load font
    *font = TTF_OpenFont("font.ttf", FONT_SIZE);
    if (!(*font)) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return 0;
    }

	return (1);
}

