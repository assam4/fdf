#include "graphics.h"

static void	draw_pixel(t_data *img, t_point *pixel)
{
	int	*location;

	if (img && (pixel->x >= START && pixel->x < WIN_WIDTH)
		&& (pixel->y >= START && pixel->y < WIN_HEIGHT))
	{
		location = (int *)(img->addr
				+ (pixel->y * img->row_len + pixel->x
					* (img->pixel_sizeof / SIZEOF_BYTE)));
		color_transform(&(pixel->color), location, TO_INT);
	}
}

static int	get_drawline_params(int *distance, int *direction,
			const t_point *start, const t_point *end)
{
	distance[0] = abs(end->x - start->x);
	distance[1] = abs(end->y - start->y);
	distance[2] = distance[(distance[1] > distance[0])];
	direction[0] = 1 - (2 * (start->x >= end->x));
	direction[1] = 1 - (2 * (start->y >= end->y));
	return (distance[0] - distance[1]);
}

static t_bgr	get_different(const t_bgr *start, const t_bgr *end
			, int max_steps)
{
	t_bgr	result;

	if (max_steps == START)
	{
		result.blue = end->blue - start->blue;
		result.green = end->green - start->green;
		result.red = end->red - start->red;
	}
	else
	{
		result.blue = (end->blue - start->blue) / max_steps;
		result.green = (end->green - start->green) / max_steps;
		result.red = (end->red - start->red) / max_steps;
	}
	return (result);
}

static void	calc_color(t_bgr *current, const t_bgr *diff)
{
	current->blue += diff->blue;
	current->green += diff->green;
	current->red += diff->red;
}

void	draw_line(t_data *img, t_point current, const t_point *end)
{
	int		distance[3];
	int		shifting[2];
	int		direction[2];
	t_bgr	diff;

	shifting[0] = get_drawline_params(distance, direction, &current, end);
	diff = get_different(&(current.color), &(end->color), distance[2]);
	while (current.x != end->x || current.y != end->y)
	{
		calc_color(&(current.color), &diff);
		draw_pixel(img, &current);
		shifting[1] = shifting[0] * 2;
		if (shifting[1] > -distance[1])
		{
			shifting[0] -= distance[1];
			current.x += direction[0];
		}
		if (shifting[1] <= distance[0])
		{
			shifting[0] += distance[0];
			current.y += direction[1];
		}
	}
}
