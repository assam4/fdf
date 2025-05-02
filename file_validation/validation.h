#ifndef VALIDATION_H
# define VALIDATION_H

# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define VALIDATION_ERROR 0
# define ALLOCATION_ERROR -1
# define SUCCESS 1
# define START 0
# define IS_EQUAL 0
# define SPACE ' '
# define BASE "0123456789abcdefABCDEF"

bool	file_format_checking(int fd, int *col, int *row);

#endif
