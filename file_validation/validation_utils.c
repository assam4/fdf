/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 00:16:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/02/06 23:58:42 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

static int	number_validation(char **line)
{
	char		*str_num;
	size_t		str_len;
	int			is_equal;

	str_num = ft_itoa(ft_atoi(*line));
	if (!str_num)
		return (ALLOCATION_ERROR);
	str_len = ft_strlen(str_num);
	if (ft_strncmp(*line, str_num, str_len) != IS_EQUAL)
		is_equal = VALIDATION_ERROR;
	else
	{
		*line += str_len;
		is_equal = SUCCESS;
	}
	free(str_num);
	return (is_equal);
}

static int	get_col_count(char *line)
{
	int			status;
	int			ongoing_cols;

	ongoing_cols = START;
	while (line && *line)
	{
		if (*line == SPACE)
			++line;
		else if (*line == NEWLINE)
			break ;
		else
		{
			status = number_validation(&line);
			if (status == SUCCESS)
				++ongoing_cols;
			else
				return (status);
		}
	}
	return (ongoing_cols);
}

static int	set_cols_status(int status, int *col, int row)
{
	if (status > VALIDATION_ERROR)
	{
		if (*col == START && row == START)
		{
			*col = status;
			return (SUCCESS);
		}
		if (*col == status)
			return (SUCCESS);
	}
	return (VALIDATION_ERROR);
}

int	file_format_checking(int fd, int *col, int *row)
{
	char	*ongoing_line;
	int		status;
	int		ongoing_col;

	while (SUCCESS)
	{
		ongoing_line = get_next_line(fd);
		if (!ongoing_line)
			break ;
		ongoing_col = get_col_count(ongoing_line);
		status = set_cols_status(ongoing_col, col, *row);
		free(ongoing_line);
		if (status != SUCCESS)
			return (status);
		++(*row);
	}
	if (!*col && !*row)
		return (VALIDATION_ERROR);
	return (SUCCESS);
}
