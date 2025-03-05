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

	width = (object->columns - 1) * SPACING + (SPACING * SPACING);
	height = (object->rows - 1) * SPACING + (SPACING * SPACING);
	object->zoom = fmin((float)WIN_WIDTH / width, (float)WIN_HEIGHT / height);
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
		z_scale = fmin(1.0,
				fmax(0.1, ((float)WIN_HEIGHT / 4) / max_z * object->zoom));
	iso_x = (x - y) * cos(ANGLE_30) * SPACING;
	iso_y = (x + y) * sin(ANGLE_30)
		* SPACING + object->pixels[y][x].z * z_scale;
	object->pixels[y][x].x = WIN_WIDTH / 2
		+ iso_x - (object->columns * SPACING) / 2;
	object->pixels[y][x].y = WIN_HEIGHT / 2
		+ iso_y - (object->rows * SPACING) / 2;
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
			set_iso_point(y, x, object);
	}
}
