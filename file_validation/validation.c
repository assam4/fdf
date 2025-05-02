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

static bool	number_validation(char **line)
{
	int		count;
	bool	is_signed;

	count = START;
	is_signed = false;
	while (**line && **line == SPACE)
		++(*line);
	if (**line == '-')
	{
		++(*line);
		is_signed = true;
	}
	while (ft_isdigit((*line)[count]))
		++count;
	(*line) += count;
	if (count > 11
		|| (count == 10 && !is_signed && *(*line - 1) > '7')
		|| (count == 10 && is_signed && *(*line - 1) > '8'))
		return (false);
	return (true);
}

static bool	color_jump(char **line)
{
	int	count;

	count = START;
	while (**line == SPACE)
		++(*line);
	if (**line == ',')
		++(*line);
	else
		return (true);
	while (**line == SPACE)
		++(*line);
	if (**line == '0' && *(*line + 1) == 'x')
		(*line) += 2;
	while (ft_strchr(BASE, (*line)[count]))
		++count;
	if (count >= 1 && count <= 6)
	{
		(*line) += count;
		return (true);
	}
	else
		return (false);
}

static int	get_col_count(char *line)
{
	bool		status;
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
			if (status)
				++ongoing_cols;
			else
				return (0);
			status = color_jump(&line);
			if (!status)
				return (0);
		}
	}
	return (ongoing_cols);
}

static bool	set_cols_status(int col_count, int *col, int row)
{
	if (col_count)
	{
		if (*col == START && row == START)
		{
			*col = col_count;
			return (true);
		}
		if (*col == col_count)
			return (true);
	}
	printf("invalid col status\n");
	return (false);
}

bool	file_format_checking(int fd, int *col, int *row)
{
	bool	status;
	char	*ongoing_line;
	int		ongoing_col;

	while (true)
	{
		ongoing_line = get_next_line(fd);
		if (!ongoing_line)
			break ;
		ongoing_col = get_col_count(ongoing_line);
		status = set_cols_status(ongoing_col, col, *row);
		free(ongoing_line);
		if (!status)
			return (false);
		++(*row);
	}
	if (!*col && !*row)
		return (false);
	return (true);
}
