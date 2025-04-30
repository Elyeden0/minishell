/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:32:42 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 10:35:34 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*build_target(t_env *env, char **args, int *pf)
{
	char	*arg;
	char	*home;

	arg = args[0];
	if (!arg || (arg[0] == '~' && arg[1] == '\0'))
		return (handle_home(env));
	if (arg[0] == '~' && arg[1] == '/')
	{
		home = get_env_value(env, "HOME");
		if (!home[0])
		{
			printf("minishell: cd: HOME not set\n");
			return (NULL);
		}
		return (ft_strjoin(home, arg + 1));
	}
	if (arg[0] == '-' && arg[1] == '\0')
		return (handle_oldpwd(env, pf));
	return (ft_strdup(arg));
}

int	update_existing_env(t_env *node, const char *n, const char *d)
{
	node->data = (char *)d;
	node->params = node->data + ft_strlen(n) + 1;
	node->show = 1;
	return (0);
}

int	add_new_env(t_env **env, char *d)
{
	t_env	*node;
	t_env	*tmp;

	node = create_node_env(d);
	if (!node)
		return (1);
	node->show = 1;
	tmp = *env;
	if (!tmp)
		*env = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (0);
}

int	set_env_var(t_env **env, const char *n, const char *v)
{
	char	*nv;
	char	*d;
	t_env	*node;

	nv = ft_strjoin(n, "=");
	if (!nv)
		return (1);
	d = ft_strjoin(nv, v);
	if (!d)
		return (1);
	node = find_env(*env, n);
	if (node)
		return (update_existing_env(node, n, d));
	return (add_new_env(env, d));
}

int	update_pwd_vars(t_env **env, const char *prev, const char *tgt)
{
	char	buf[PATH_MAX];
	char	*fb;
	char	*f2;

	fb = ft_strjoin(prev, "/");
	set_env_var(env, "OLDPWD", prev);
	if (getcwd(buf, sizeof(buf)))
		return (set_env_var(env, "PWD", buf));
	printf("minishell: cd: error retrieving current directory: %s\n",
		strerror(errno));
	fb = ft_strjoin(prev, "/");
	f2 = ft_strjoin(fb, tgt);
	set_env_var(env, "PWD", f2);
	return (0);
}
