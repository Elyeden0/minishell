/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:58:48 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 02:48:10 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdio.h>

static char	*get_export_name(char *arg, int *append)
{
	char	*eq;
	int		name_len;
	char	*name;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (NULL);
	*append = 0;
	if (eq != arg)
	{
		if (*(eq - 1) == '+')
			*append = 1;
	}
	name_len = (eq - arg);
	if (*append)
		name_len--;
	name = ft_malloc(name_len + 1);
	if (!name)
		return (NULL);
	ft_memcpy(name, arg, name_len);
	name[name_len] = '\0';
	return (name);
}

static int	handle_append_mode(t_env *node, char *name, char *eq)
{
	char	*old;
	char	*new_val;
	char	*data;
	char	*full;

	old = "";
	if (node->params)
		old = node->params;
	new_val = ft_strjoin(old, eq + 1);
	if (!new_val)
		return (1);
	data = ft_strjoin(name, "=");
	if (!data)
		return (1);
	full = ft_strjoin(data, new_val);
	if (!full)
		return (1);
	node->data = full;
	node->name = data;
	node->params = ft_strchr(node->data, '=') + 1;
	node->show = 1;
	return (0);
}

static void	update_or_create_node(t_env **env, char *arg)
{
	t_env	*node;
	t_env	*new;
	char	*name;

	name = ft_strndup(arg, strlen_equal(arg));
	node = find_env(*env, name);
	if (node)
	{
		node->data = ft_strdup(arg);
		node->name = ft_strjoin(name, "=");
		node->params = ft_strchr(node->data, '=') + 1;
		node->show = 1;
	}
	else
	{
		new = create_node_env(arg);
		if (!new)
			return ;
		new->show = 1;
		link_new_env(env, new);
	}
}

static int	process_export_arg(t_env **env, char *arg)
{
	char	*eq;
	int		append;
	char	*name;
	t_env	*node;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	name = get_export_name(arg, &append);
	if (!name)
		return (0);
	if (!is_valid_identifier(name))
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	node = find_env(*env, name);
	if (append && node)
		return (handle_append_mode(node, name, eq));
	update_or_create_node(env, arg);
	return (0);
}

int	builtin_export(t_env **env, char **args)
{
	int	status;
	int	i;

	if (!args || !args[0])
	{
		print_export(*env);
		return (0);
	}
	status = 0;
	i = 0;
	while (args[i])
	{
		if (process_export_arg(env, args[i]))
			status = 1;
		i++;
	}
	return (status);
}
