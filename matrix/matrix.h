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

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct s_bgr
{
	t_uchar		blue;
	t_uchar		green;
	t_uchar		red;
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
	float		zoom;
}	t_matrix;

// creating matrix
int		initialize_matrix(int fd, t_matrix *object);
// dealloacting matrix
void	deallocate_matrix(t_matrix **matrix);

#endif
