/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 02:51:31 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 10:35:37 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
