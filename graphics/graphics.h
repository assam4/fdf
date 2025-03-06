/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:57:43 by saslanya          #+#    #+#             */
/*   Updated: 2025/03/04 22:13:53 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "matrix.h"
# include "mlx.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define SPACING 10
# define ANGLE_30 0.523599
# define SIZEOF_BYTE 8

# define TO_INT 33
# define TO_BGR 22
# define BLACK 0x000000
# define WHITE 0xffffff
# define RED 0x0000ff
# define BLUE 0xff0000
# define DEFAULT_UP_COLOR BLUE 
# define DEFAULT_MID_COLOR WHITE
# define DEFAULT_DOWN_COLOR RED

typedef struct s_window
{
	void	*mlx_connect;
	void	*window;
}	t_window;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		pixel_sizeof;
	int		row_len;
	int		endian;
}	t_image;

void	set_iso_matrix(t_matrix *object);
void	color_transform(t_bgr *bgr, int *color, int swap_source);
void	draw_matrix(t_image *img, t_matrix *object);
#endif
