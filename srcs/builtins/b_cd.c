/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:39:26 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 10:35:30 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	too_many_args(char **args)
{
	if (args[0] && args[1])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

char	*handle_home(t_env *env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home[0])
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	return (ft_strdup(home));
}

char	*handle_oldpwd(t_env *env, int *pf)
{
	char	*tmp;

	tmp = get_env_value(env, "OLDPWD");
	if (!tmp[0])
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (NULL);
	}
	*pf = 1;
	return (ft_strdup(tmp));
}

int	do_cd(t_env **env, char *tgt, int pf)
{
	char	*prev;

	prev = get_env_value(*env, "PWD");
	if (chdir(tgt) != 0)
	{
		printf("minishell: cd: %s: %s\n", tgt, strerror(errno));
		return (1);
	}
	update_pwd_vars(env, prev, tgt);
	if (pf)
		printf("%s\n", get_env_value(*env, "PWD"));
	return (0);
}

int	builtin_cd(t_env **env, char **args)
{
	int		pf;
	char	*tgt;
	int		r;

	if (too_many_args(args))
		return (1);
	pf = 0;
	tgt = build_target(*env, args, &pf);
	if (!tgt)
		return (1);
	r = do_cd(env, tgt, pf);
	return (r);
}
