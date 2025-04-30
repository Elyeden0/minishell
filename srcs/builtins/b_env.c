/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 02:39:48 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 12:44:27 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/LibFT/libft.h"
#include "../../include/minishell.h"


int	builtin_env(t_env *env, char **args)
{
	t_env	*tmp;

	(void)args;
	tmp = env;
	while (tmp)
	{
		if (tmp->show)
			printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*find_env(t_env *env, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->name, name, len))
		{
			if (ft_strlen(env->name) == len + 1)
				return (env);
			else
				return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

int	builtin_unset(t_env *env, char **args)
{
	int		i;
	t_env	*node;

	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		node = find_env(env, args[i]);
		if (node)
		{
			node->show = 0;
			node->params = "";
		}
		i++;
	}
	return (0);
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->show)
		{
			printf("declare -x ");
			printf("%s", env->name);
			if (env->params)
				printf("=\"%s\"", env->params);
			printf("\n");
		}
		env = env->next;
	}
}
