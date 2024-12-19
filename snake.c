#include "snake.h"

e_direction	direction = RIGHT;
t_tail		*head;
int			snake_size;
int			score;
double		is_angry;

int	get_snake_size()
{
	return (snake_size);
}
int	get_score()
{
	return (score);
}

void	free_tails()
{
	t_tail	*tmp;

	while (head)
	{
		tmp = head->next; 
		free(head);
		head = tmp;
	}
}

void	render_snake(SDL_Renderer *renderer)
{
	int			offset = 3;
	int 		x = (SIDES + head->x) * CELL_SIZE;
	int 		y = (BANNER_H + head->y) * CELL_SIZE;
	int			size = CELL_SIZE;
	t_tail		*tail;
	int			i;
	double		step_r = ((SDL_Color)SNAKE_COLOR.r - (SDL_Color)SNAKE2_COLOR.r) / (double)snake_size;
	double		step_g = ((SDL_Color)SNAKE_COLOR.g - (SDL_Color)SNAKE2_COLOR.g) / (double)snake_size;
	double		step_b = ((SDL_Color)SNAKE_COLOR.b - (SDL_Color)SNAKE2_COLOR.b) / (double)snake_size;
	SDL_Color	snake_color = (SDL_Color)SNAKE_COLOR;

	if (is_angry > 0)
		renderRect(renderer, x, y, size, size, (SDL_Color)GOLD_COLOR);
	else
		renderRect(renderer, x, y, size, size, (SDL_Color)SNAKE_COLOR);
	size -= 2 * offset;
	tail = head->next;
	i = 1;
	while (tail)
	{
		snake_color.r -= step_r;
		snake_color.g -= step_g;
		snake_color.b -= step_b;

		x = ((SIDES + tail->x) * CELL_SIZE) + offset;
		y = (tail->y + BANNER_H)* CELL_SIZE + offset;
		if (i < is_angry)
			renderRect(renderer, x, y, size, size, (SDL_Color)GOLD_COLOR);
		else
			renderRect(renderer, x, y, size, size, snake_color);
		tail = tail->next;
		++i;
	}
}

void	new_snake_direction(e_direction new_direction, int *has_moved)
{
	e_direction old_direction = direction;

	if (*has_moved)
		return ;

	if (new_direction == TOP && direction != BOTTOM)
		direction = TOP;
	if (new_direction == RIGHT && direction != LEFT)
		direction = RIGHT;
	if (new_direction == BOTTOM && direction != TOP)
		direction = BOTTOM;
	if (new_direction == LEFT && direction != RIGHT)
		direction = LEFT;

	if (old_direction != direction)
		++(*has_moved);
}

void	init_snake()
{
	t_tail	*new;
	t_tail	*tmp;
	int		i;

	score = 0;
	snake_size = START_SIZE;
	is_angry = 0;
	i = 0;
	tmp = NULL;	
	while (i < START_SIZE)
	{
		new = malloc(sizeof(t_tail));
		new->next = tmp;
		new->x = MAP_W / 2 - START_SIZE + i;
		new->y = MAP_H / 2;
		new->direction = RIGHT;
		tmp = new;
		set_object_at(new->x, new->y, TAIL);
		++i;
	}
	head = new;
	set_object_at(head->x, head->y, HEAD);
}

t_tail	*get_and_remove_last()
{
	t_tail	*tail;
	t_tail *last;

	tail = head;
	while (tail->next->next)
		tail = tail->next;
	last = tail->next;	
	tail->next = NULL;
	return (last);
}

int	is_snake_colliding(int x, int y)
{
	e_object obj = get_object_at(x, y);

	if (obj == TAIL)
		return (1);
	if (obj == OBSTACLE)
	{
		if (is_angry > 0)
		{
			affect_free_space(1);
			++score;
			return (0);
		}
		return (1);
	}
	return (0);
}

void	move_snake(int	*is_game_running)
{
	int		x = head->x;
	int		y = head->y;
	int		grow = 0;
	t_tail	*new_head;
	t_tail	*tmp;

	if (direction == TOP)
	{
		y -= 1;
		if (y < 0)
			y = MAP_H - 1;
	}
	else if (direction == RIGHT)
	{
		x += 1;
		if (x > MAP_W - 1)
			x = 0;
	}
	else if (direction == BOTTOM)
	{
		y += 1;
		if (y > MAP_H - 1)
			y = 0;
	}
	else if (direction == LEFT)
	{
		x -= 1;
		if (x < 0)
			x = MAP_W - 1;
	}
	
	if (get_object_at(x, y) == GOLD)
		is_angry = snake_size;
	if (get_object_at(x, y) == APPLE)
	{
		new_head = malloc(sizeof(t_tail));
		affect_free_space(-1);
		grow = 1;
		++score;
		++snake_size;
	}
	else
	{
		new_head = get_and_remove_last();
		tmp = head;
		if (get_object_at(new_head->x, new_head->y) == TAIL)
			set_object_at(new_head->x, new_head->y, EMPTY);
		head = tmp;
	}

	new_head->x = x;
	new_head->y = y;
	new_head->direction = direction;
	new_head->next = head;
	if (is_snake_colliding(x, y))
	{
		*is_game_running = 0;
		return ;
	}
	set_object_at(head->x, head->y, TAIL);
	set_object_at(new_head->x, new_head->y, HEAD);
	if (grow)
	{
		generate_nobject(1, APPLE);
		if (snake_size % 5 == 0)
		{
			generate_nobject(10, OBSTACLE);
			is_angry = snake_size;
		}
	}
	if (is_angry > 0)
		is_angry -= (double)snake_size / 40;
	head = new_head;
}

