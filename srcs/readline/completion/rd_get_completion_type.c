/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:54:12 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:56:41 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_direct_path_or_empty(const char *buf, size_t pos)
{
	if (pos >= 1 && buf[0] == '/')
		return (1);
	if (pos >= 2 && buf[0] == '.' && buf[1] == '/')
		return (1);
	if (!buf || pos == 0)
		return (2);
	return (0);
}

static size_t	get_segment_start(const char *buf, size_t pos)
{
	size_t	i;
	size_t	seg_start;

	seg_start = 0;
	i = 0;
	while (i < pos)
	{
		if ((buf[i] == '&' && i + 1 < pos && buf[i + 1] == '&')
			|| (buf[i] == '|' && i + 1 < pos && buf[i + 1] == '|'))
		{
			seg_start = i + 2;
			i++;
		}
		else if (buf[i] == '|' || buf[i] == ';' || buf[i] == '(')
			seg_start = i + 1;
		i++;
	}
	return (seg_start);
}

static int	has_space_in_segment(const char *buf, size_t start, size_t end)
{
	size_t	i;

	i = start;
	while (i < end && isspace((unsigned char)buf[i]))
		i++;
	if (i >= end)
		return (0);
	while (i < end)
	{
		if (isspace((unsigned char)buf[i]))
			return (1);
		i++;
	}
	return (0);
}

t_completion_type	get_completion_type(const char *buf, size_t pos)
{
	size_t	res;
	size_t	seg_start;

	res = is_direct_path_or_empty(buf, pos);
	if (res == 1)
		return (CT_ARG);
	if (res == 2)
		return (CT_CMD);
	seg_start = get_segment_start(buf, pos);
	if (has_space_in_segment(buf, seg_start, pos))
		return (CT_ARG);
	return (CT_CMD);
}
