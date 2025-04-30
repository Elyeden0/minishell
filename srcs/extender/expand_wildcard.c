/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/04/29 00:20:22 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**collect_matches(const char *pattern, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				n;

	*count = count_matching_files(pattern);
	if (*count <= 0)
		return (NULL);
	matches = ft_malloc(sizeof(char *) * (*count + 1));
	matches[*count] = NULL;
	dir = opendir(".");
	n = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (star_match(pattern, entry->d_name))
			matches[n++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	sort_strings(matches, *count);
	return (matches);
}

static t_token	*create_expanded_list(char **matches, int count)
{
	t_token	*first;
	t_token	*last;
	t_token	*new_node;
	int		i;

	first = NULL;
	last = NULL;
	i = 0;
	while (i < count)
	{
		new_node = ft_malloc(sizeof(*new_node));
		new_node->type = T_WORD;
		new_node->value = matches[i];
		new_node->next = NULL;
		if (!first)
			first = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
	return (first);
}

static void	replace_star_token(t_expand_data d, char **matches, int count)
{
	t_token	*first_new;
	t_token	*last_new;
	t_token	*next;

	first_new = create_expanded_list(matches, count);
	if (!first_new)
		return ;
	last_new = first_new;
	while (last_new->next)
		last_new = last_new->next;
	next = d.cur->next;
	if (d.prev)
		d.prev->next = first_new;
	else
		*d.tokens = first_new;
	last_new->next = next;
}

void	expand_star_tokens(t_token **tokens)
{
	t_expand_data	d;
	char			**matches;
	int				count;

	d.prev = NULL;
	d.cur = *tokens;
	d.tokens = tokens;
	while (d.cur)
	{
		if (d.cur->type == T_WORD && ft_strchr(d.cur->value, '*'))
		{
			matches = collect_matches(d.cur->value, &count);
			if (matches)
			{
				replace_star_token(d, matches, count);
				while (d.cur->next && d.cur->next != NULL)
					d.cur = d.cur->next;
			}
		}
		d.prev = d.cur;
		d.cur = d.cur->next;
	}
}
