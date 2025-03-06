/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_to_iso.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:08:20 by saslanya          #+#    #+#             */
/*   Updated: 2025/03/04 22:08:22 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	set_starting_zoom(t_matrix *object)
{
	float	width;
	float	height;

	width = (object->columns - 1) * SPACING;
	height = (object->rows - 1) * SPACING;
	object->zoom = 0.8 * fmin((float)WIN_WIDTH / width,
			(float)WIN_HEIGHT / height);
}

static int	return_max_z(const t_matrix *object)
{
	int	max_z;
	int	y;
	int	x;

	max_z = START;
	if (!object || !object->pixels)
		return (max_z);
	y = -1;
	while (++y < object->rows)
	{
		x = -1;
		while (++x < object->columns)
		{
			if (abs(object->pixels[y][x].z) > max_z)
				max_z = abs(object->pixels[y][x].z);
		}
	}
	return (max_z);
}

static void	set_iso_point(int y, int x, t_matrix *object)
{
	int		iso_x;
	int		iso_y;
	int		max_z;
	float	z_scale;

	max_z = return_max_z(object);
	if (!max_z)
		z_scale = 0.5;
	else
		z_scale = fmin(1.0, fmax(0.2, ((float)WIN_HEIGHT / 4) / max_z));
	iso_x = (x - y) * cos(ANGLE_30) * (SPACING * object->zoom / 2);
	iso_y = (x + y) * sin(ANGLE_30) * (SPACING * object->zoom / 2)
		- (object->pixels[y][x].z * z_scale);
	object->pixels[y][x].x = WIN_WIDTH / 2
		+ iso_x - ((object->columns - 1) * SPACING / 2);
	object->pixels[y][x].y = WIN_HEIGHT / 2
		+ iso_y - ((object->rows - 1) * SPACING / 2);
}

static void	set_zcolor(t_point *pixel)
{
	int	color;

	if (pixel->z > START)
		color = DEFAULT_UP_COLOR;
	else if (pixel->z < START)
		color = DEFAULT_DOWN_COLOR;
	else
		color = DEFAULT_MID_COLOR;
	color_transform(&(pixel->color), &color, TO_BGR);
}

void	set_iso_matrix(t_matrix *object)
{
	int	y;
	int	x;

	y = -1;
	set_starting_zoom(object);
	while (++y < object->rows)
	{
		x = -1;
		while (++x < object->columns)
		{
			set_iso_point(y, x, object);
			set_zcolor(&(object->pixels[y][x]));
		}
	}
}
