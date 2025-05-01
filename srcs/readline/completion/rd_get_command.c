/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:58:28 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 01:04:43 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_paths(t_cmd_suggestions *s, t_env *env)
{
	s->list = NULL;
	s->path_dup = ft_strdup(get_env_value(env, "PATH"));
	s->paths = NULL;
	if (s->path_dup && *(s->path_dup))
		s->paths = ft_split(s->path_dup, ":");
}

static void	add_path_commands(t_cmd_suggestions *s, const char *prefix)
{
	int				i;
	struct dirent	*ent;

	if (!s->paths)
		return ;
	i = 0;
	while (s->paths[i])
	{
		s->dir = opendir(s->paths[i]);
		if (!s->dir)
		{
			i++;
			continue ;
		}
		ent = readdir(s->dir);
		while (ent)
		{
			if (ent->d_type != DT_DIR && match_prefix(ent->d_name, prefix))
				ft_lstadd_unique_str(&s->list, ft_strdup(ent->d_name));
			ent = readdir(s->dir);
		}
		closedir(s->dir);
		i++;
	}
}

static void	add_builtins(t_cmd_suggestions *s, const char *prefix)
{
	static const char	*g_builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset", NULL};
	int					i;

	i = 0;
	while (g_builtins[i])
	{
		if (match_prefix(g_builtins[i], prefix))
			ft_lstadd_unique_str(&s->list, ft_strdup(g_builtins[i]));
		i++;
	}
}

char	**get_command_suggestions(const char *prefix, t_env *env)
{
	t_cmd_suggestions	s;
	char				**out;

	init_paths(&s, env);
	add_path_commands(&s, prefix);
	add_builtins(&s, prefix);
	out = ft_list_to_array(s.list);
	sort_strings(out, ft_lstsize(s.list));
	return (out);
}
