#ifndef FDF_H
# define FDF_H

# include "graphics.h"

t_matrix	*get_matrix(const char *fname);
void		run_fdf(t_data *data);
void		reset_img(t_data *data);
void		shift_or_zoom(int key, t_matrix *matrix);
void		rotate(int key, t_matrix *matrix);

#endif
