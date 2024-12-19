#ifndef SNAKE_H
# define SNAKE_H

# define START_SIZE 5
# define BANNER_H 3
# define SIDES 1
# define MAP_W 22
# define MAP_H 14
# define CELL_SIZE 50
# define FONT_SIZE 75

# define OVERLAY_COLOR {139, 100, 78, 255}
# define BACKGROUND_COLOR {44, 62, 80, 255}
# define TEXT_COLOR {244, 225, 193, 255}

# define SNAKE_COLOR {139, 195, 74, 255}
# define SNAKE2_COLOR {30, 120, 40, 255}

# define APPLE_COLOR {255, 99, 71, 255}
# define OBSTACLE_COLOR {149, 165, 166, 255}
# define GOLD_COLOR {255, 215, 0, 255}

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

typedef enum
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT

}	e_direction;

typedef enum
{
	EMPTY,
	HEAD,
	TAIL,
	APPLE,
	OBSTACLE,
	TELEPORT,
	GOLD
}	e_object;

typedef struct	s_tail
{
	int				x;
	int				y;
	e_direction		direction;
	struct s_tail	*next;
}	t_tail;

// Render management
void	clean_render(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
int		init_render(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);
void	set_render_color(SDL_Renderer *renderer, int color[4]);

// Render utils
void renderRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color);
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font, SDL_Color color);
void renderLine(SDL_Renderer *renderer, int s[2], int e[2], SDL_Color color);
void setRenderDrawColor(SDL_Renderer *renderer, SDL_Color color);

// Snake
void	move_snake(int *is_game_running);
void	init_snake();
void	new_snake_direction(e_direction new_direction, int *has_moved);
void	render_snake(SDL_Renderer *renderer);
void	free_tails();
int		get_score();
int		get_snake_size();

// Map
void		empty_map();
e_object	get_object_at(int x, int y);
void		set_object_at(int x, int y, e_object event);
void		affect_free_space(int delta);
int			get_free_space();
void		generate_nobject(int n, e_object obj);
void		render_map(SDL_Renderer *renderer);

// Overlay
void	render_overlay(SDL_Renderer *renderer, int score, TTF_Font *font);

#endif
