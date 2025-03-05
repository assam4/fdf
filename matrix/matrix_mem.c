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

static void	deallocate_pixels(t_point **pixels, size_t rows)
{
	while (pixels && rows--)
	{
		if (pixels[rows])
			free(pixels[rows]);
		pixels[rows] = NULL;
	}
	if (pixels)
		free(pixels);
}

void	deallocate_matrix(t_matrix **matrix)
{
	if (matrix && *matrix)
	{
		deallocate_pixels((*matrix)->pixels, (*matrix)->rows);
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

int	initialize_matrix(int fd, t_matrix *object)
{
	int		y;
	char	*line;

	object->pixels = ft_calloc(object->rows, sizeof(t_point *));
	if (!object->pixels)
		return (deallocate_matrix(&object), ALLOCATION_ERROR);
	y = -1;
	while (++y < object->rows)
	{
		object->pixels[y] = ft_calloc(object->columns, sizeof(t_point));
		line = get_next_line(fd);
		if (!line || !object->pixels[y])
			return (deallocate_matrix(&object), ALLOCATION_ERROR);
		if (set_col_z(line, y, object) != SUCCESS)
			return (free(line), deallocate_matrix(&object), ALLOCATION_ERROR);
		free(line);
	}
	return (SUCCESS);
}
