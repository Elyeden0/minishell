/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:04 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 01:06:05 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_prefix(const char *prefix, char **dir_path, char **partial,
		int *has_slash)
{
	char	*s;

	s = ft_strrchr(prefix, '/');
	if (s)
	{
		*dir_path = ft_strndup(prefix, s - prefix + 1);
		*partial = ft_strdup(s + 1);
		*has_slash = 1;
	}
	else
	{
		*dir_path = ft_strdup("./");
		*partial = ft_strdup(prefix);
		*has_slash = 0;
	}
}

static void	add_dotdot(t_list **lst, const char *partial, int has_slash)
{
	if (!has_slash && ft_strcmp(partial, "..") == 0)
		ft_lstadd_unique_str(lst, ft_strdup("../"));
}

static void	add_dir_entry(t_list **lst, const char *dir_path, struct dirent *e)
{
	char	*fp;
	int		dirok;
	char	*entry;

	fp = ft_strjoin(dir_path, e->d_name);
	dirok = is_dir(fp);
	if (dirok)
		entry = ft_strjoin(e->d_name, "/");
	else
		entry = ft_strdup(e->d_name);
	ft_lstadd_unique_str(lst, entry);
}

static void	scan_dir(t_list **lst, const char *dir_path, const char *partial)
{
	DIR				*d;
	struct dirent	*e;

	d = opendir(dir_path);
	if (!d)
		return ;
	e = readdir(d);
	while (e)
	{
		if (!ft_strcmp(e->d_name, ".") || !ft_strcmp(e->d_name, ".."))
		{
			e = readdir(d);
			continue ;
		}
		if (ft_strncmp(e->d_name, partial, ft_strlen(partial)) == 0)
			add_dir_entry(lst, dir_path, e);
		e = readdir(d);
	}
	closedir(d);
}

char	**get_file_suggestions(const char *prefix)
{
	t_list	*list;
	char	*dir_path;
	char	*partial;
	int		has_slash;
	char	**out;

	list = NULL;
	if (ft_strcmp(prefix, ".") == 0)
	{
		ft_lstadd_unique_str(&list, ft_strdup("."));
		ft_lstadd_unique_str(&list, ft_strdup(".."));
	}
	split_prefix(prefix, &dir_path, &partial, &has_slash);
	add_dotdot(&list, partial, has_slash);
	scan_dir(&list, dir_path, partial);
	out = ft_list_to_array(list);
	sort_strings(out, ft_lstsize(list));
	return (out);
}
