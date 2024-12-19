#include "snake.h"

static int		free_space = MAP_H * MAP_W - START_SIZE;
static e_object	map[MAP_H][MAP_W];

void	empty_map()
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_H)
	{
		j = 0;
		while (j < MAP_W)
		{
			map[i][j] = EMPTY;
			++j;
		}
		++i;
	}
}

void	render_object(SDL_Renderer *renderer, int x, int y, e_object obj)
{
	SDL_Color color;

	if (obj == HEAD || obj == TAIL)
		return ;

    if (obj == HEAD || obj == TAIL)
        return ;

    if (obj == OBSTACLE)
        color = (SDL_Color)OBSTACLE_COLOR;
    else if (obj == APPLE)
        color = (SDL_Color)APPLE_COLOR;
    else if (obj == GOLD)
        color = (SDL_Color)GOLD_COLOR;
	else
        color = (SDL_Color){0, 0, 0, 255};

	renderRect(renderer, CELL_SIZE * (SIDES + x), CELL_SIZE * (y + BANNER_H), CELL_SIZE, CELL_SIZE, color);
}

void	render_map(SDL_Renderer *renderer)
{
	int	i = 0;
	int	j;

	while (i < MAP_H)
	{
		j = 0;
		while (j < MAP_W)
		{
			if (map[i][j] != EMPTY)
				render_object(renderer, j, i, map[i][j]);
			++j;
		}
		++i;
	}

}

void	generate_nobject(int n, e_object obj)
{
	int	pos;
	int	i;
	int	j;

	while (n > 0)
	{
		srand(time(NULL));
		pos = rand() % (free_space);
		i = 0;
		j = 0;
		while (j != pos)
		{
			if (map[i / MAP_W][i % MAP_W] == EMPTY)
				++j;
			++i;
		}
		--i;
		map[i / MAP_W][i % MAP_W] = obj;
		--free_space;
		--n;
	}
}

void	affect_free_space(int delta)
{
	free_space += delta;
}

int	get_free_space()
{
	return (free_space);
}

void set_object_at(int x, int y, e_object obj)
{
	map[y][x] = obj;
}

e_object	get_object_at(int x, int y)
{
	return (map[y][x]);	
}
