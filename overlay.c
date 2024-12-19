#include "snake.h"

int	num_len(int n)
{
	int	len = 0;

	if (n == 0)
		return (1);
	while (n)
	{
		++len;
		n = n / 10;
	}
	return (len);
}

void	render_overlay(SDL_Renderer *renderer, int score, TTF_Font *font)
{
	SDL_Color	color = (SDL_Color)OVERLAY_COLOR;
	SDL_Color	text_color = (SDL_Color)TEXT_COLOR;
	char		str_num[17];
	int			n_len;

	renderRect(renderer, 0, 0, (MAP_W + 2 * SIDES)* CELL_SIZE, BANNER_H * CELL_SIZE, color);
	renderRect(renderer, 0, (MAP_H + BANNER_H) * CELL_SIZE, (MAP_W + 2 * SIDES) * CELL_SIZE, SIDES * CELL_SIZE, color);
	renderRect(renderer,
		0, BANNER_H * CELL_SIZE,
		SIDES * CELL_SIZE, MAP_H * CELL_SIZE,
		color
	);
	renderRect(renderer,
		(2 * SIDES + MAP_W - 1) * CELL_SIZE, BANNER_H * CELL_SIZE,
		SIDES * CELL_SIZE, MAP_H * CELL_SIZE,
		color
	);
	sprintf(str_num, "%d", score);
	n_len = num_len(score);
	renderText(renderer, str_num,
				((MAP_W + 2 * SIDES - n_len) * CELL_SIZE) / 2, (BANNER_H * CELL_SIZE - FONT_SIZE) / 2,
				font, text_color);
}
