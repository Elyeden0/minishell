/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:50:51 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 22:56:42 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_params_after_equal(char *envp)
{
	int		i;
	char	*start;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (envp[i] == '=')
		start = envp + i + 1;
	else
		start = "";
	return (copy_string(start));
}

t_env	*find_last_node(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_env	*create_custom_node(char *name, char *params, int show)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = copy_string(name);
	node->params = copy_string(params);
	node->data = combine_name_params(name, params);
	node->show = show;
	node->next = NULL;
	return (node);
}

void	check_path_pwd_env(t_env *env)
{
	int		has_pwd;
	int		has_oldpwd;
	int		has_path;
	t_env	*last;
	char	cwd[4096];

	has_pwd = 0;
	has_oldpwd = 0;
	has_path = 0;
	check_existing_vars(env, &has_pwd, &has_oldpwd, &has_path);
	last = find_last_node(env);
	if (!has_pwd && getcwd(cwd, 4096))
	{
		last->next = create_custom_node("PWD=", cwd, 1);
		last = last->next;
	}
	if (!has_oldpwd)
	{
		last->next = create_custom_node("OLDPWD=", "", 0);
		last = last->next;
	}
	if (!has_path)
		last->next = create_custom_node("PATH=",
				"/usr/local/sbin:/usr/local/bin:/usr/bin", 0);
}

t_env	*create_node_env(char *envp)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = copy_string(envp);
	node->show = 1;
	node->name = copy_name_with_equal(envp);
	node->params = copy_params_after_equal(envp);
	node->next = NULL;
	return (node);
}
