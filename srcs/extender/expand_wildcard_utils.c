/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:13:39 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 00:18:51 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	star_match(const char *pattern, const char *str)
{
	while (*pattern && *pattern != '*')
	{
		if (*pattern != *str)
			return (0);
		pattern++;
		str++;
	}
	if (!*pattern)
		return (*str == '\0');
	while (*pattern == '*')
		pattern++;
	if (!*pattern)
		return (1);
	while (*str)
	{
		if (star_match(pattern, str))
			return (1);
		str++;
	}
	return (0);
}

void	sort_strings(char **arr, int n)
{
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	while (i < n)
	{
		tmp = arr[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(arr[j], tmp) > 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
		i++;
	}
}

int	count_matching_files(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	entry = readdir(dir);
	while (entry)
	{
		if (star_match(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}
