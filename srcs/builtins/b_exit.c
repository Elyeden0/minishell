/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 02:49:38 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 01:07:37 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_cd_error(char *target)
{
	printf("minishell: cd: %s: %s\n", target, strerror(errno));
	return (1);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, int last_status)
{
	int	exit_code;

	printf("exit\n");
	if (!args || !args[0])
	{
		ft_free_all();
		exit(last_status);
	}
	if (!is_numeric(args[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		ft_free_all();
		exit(2);
	}
	exit_code = ft_atoi(args[0]);
	ft_free_all();
	exit(exit_code % 256);
}
