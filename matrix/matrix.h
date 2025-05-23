/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:54:23 by saslanya          #+#    #+#             */
/*   Updated: 2025/02/07 00:05:18 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "validation.h"

# define MIN_ZOOM 0.1
# define ZOOM_STEP 0.1
# define MAX_ZOOM 20.0
# define ZOOM_COEFF 0.6
# define MIN_ZSCALE 1.5

# define LOOP_START -1

# define TO_INT 33
# define TO_BGR 22
# define SIZEOF_BYTE 8

typedef struct s_bgr
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
}	t_bgr;

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	t_bgr		color;
}	t_point;

typedef struct s_matrix
{
	t_point		**pixels;
	int			columns;
	int			rows;
	int			color_set;
	int			shift_x;
	int			shift_y;
	float		rotate_x;
	float		rotate_y;
	float		rotate_z;
	float		zoom;
	float		zscale;
}	t_matrix;

bool	initialize_matrix(int fd, t_matrix **matrix);
void	color_transform(t_bgr *bgr, unsigned int *color, int swap_source);
void	fd_colors(const char **line, int y, int x, t_matrix *object);
void	deallocate_matrix(t_matrix **matrix);
void	set_zoom(t_matrix *matrix, int width, int height, int spacing);
void	set_zscale(t_matrix *matrix, int height);

#endif
