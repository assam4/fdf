/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matric_initalization_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:06 by saslanya          #+#    #+#             */
/*   Updated: 2025/02/07 00:05:42 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	deallocate_matrix(t_matrix **matrix)
{
	int	row;

	if (matrix && *matrix)
	{
		row = (*matrix)->rows;
		while (--row >= 0)
			free((*matrix)->pixels[row]);
		free((*matrix)->pixels);
		free(*matrix);
		*matrix = NULL;
	}
}

static int	set_col_z(const char *line, int current_y, t_matrix *object)
{
	char	*str;
	int		x;

	x = -1;
	while (++x < object->columns)
	{
		object->pixels[current_y][x].z = ft_atoi(line);
		str = ft_itoa(object->pixels[current_y][x].z);
		if (!str)
			return (ALLOCATION_ERROR);
		line += ft_strlen(str);
		free(str);
		while (*line == SPACE || *line == NEWLINE)
			++line;
	}
	return (SUCCESS);
}

void	set_zoom(t_matrix *matrix, int width, int height, int spacing)
{
	float	mat_width;
	float	mat_height;

	mat_width = (matrix->columns - 1) * spacing;
    	mat_height = (matrix->rows - 1) * spacing;
	matrix->zoom = fmin((float)width / mat_width, (float)height / mat_height);
	matrix->zoom *= 0.8;
}

void	set_zscale(t_matrix *matrix, int height)
{
	int		max_z;
	int		y;
	int		x;

	y = -1;
	max_z = 0;
	while (++y < matrix->rows)
	{
		x = -1;
		while (++x < matrix->columns)
			if (abs(matrix->pixels[y][x].z) > max_z)
				max_z = abs(matrix->pixels[y][x].z);
	}
	if (!max_z)
		matrix->zscale = MIN_ZSCALE;
	else
		matrix->zscale = fmin(1.0, fmax(0.2, ((float)height / 4) / max_z));
}

int	initialize_matrix(int fd, t_matrix **matrix)
{
	int		y;
	char	*line;

	(*matrix)->pixels = ft_calloc((*matrix)->rows, sizeof(t_point *));
	if (!(*matrix)->pixels)
		return (deallocate_matrix(matrix), ALLOCATION_ERROR);
	y = -1;
	while (++y < (*matrix)->rows)
	{
		(*matrix)->pixels[y] = ft_calloc((*matrix)->columns, sizeof(t_point));
		line = get_next_line(fd);
		if (!line || !(*matrix)->pixels[y])
			return (deallocate_matrix(matrix), ALLOCATION_ERROR);
		if (set_col_z(line, y, *matrix) != SUCCESS)
			return (free(line), deallocate_matrix(matrix), ALLOCATION_ERROR);
		free(line);
	}
	return (SUCCESS);
}
