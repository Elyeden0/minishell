/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:02:29 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 03:02:33 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

int	run_builtin(char **argv, t_env **env, int last_status)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv + 1));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(env, argv + 1));
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd(*env));
	if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(env, argv + 1));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(*env, argv + 1));
	if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(*env, NULL));
	if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv + 1, last_status));
	return (1);
}
