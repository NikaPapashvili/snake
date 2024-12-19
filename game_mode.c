#include "snake.h"

void	manage_events(int *is_game_running)
{
	SDL_Event 	event;
	int			has_moved = 0;

	while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			*is_game_running = 0;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			*is_game_running = 0;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
				new_snake_direction(TOP, &has_moved);
			else if (event.key.keysym.sym == SDLK_RIGHT)
				new_snake_direction(RIGHT, &has_moved);
			else if (event.key.keysym.sym == SDLK_DOWN)
				new_snake_direction(BOTTOM, &has_moved);
			else if (event.key.keysym.sym == SDLK_LEFT)
				new_snake_direction(LEFT, &has_moved);
		}
	}
}

void	start_game(SDL_Renderer *renderer, TTF_Font *font)
{
	int			is_game_running;

	empty_map();
	init_snake();
	generate_nobject(5, OBSTACLE);
	generate_nobject(1, APPLE);
	generate_nobject(1, GOLD);
	is_game_running = 1;
	while (is_game_running)
	{
		manage_events(&is_game_running);
		move_snake(&is_game_running);
		if (!is_game_running)
			break ;
		setRenderDrawColor(renderer, (SDL_Color)BACKGROUND_COLOR);
		SDL_RenderClear(renderer);
		render_overlay(renderer, get_score(), font);
		render_map(renderer);
		render_snake(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(105);
	}
	is_game_running = 1;
	while (is_game_running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				is_game_running = 0;
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				is_game_running = 0;
		}
	}
	free_tails();
}

int main(int	ac, char **av)
{
    SDL_Window 		*window;
	SDL_Renderer	*renderer;
	TTF_Font 		*font;

	(void)ac;
	(void)av;
	if (!init_render(&window, &renderer, &font))
	{
		clean_render(window, renderer, font);
		return (1);
	}
	start_game(renderer, font);
	clean_render(window, renderer, font);
    return 0;
}

