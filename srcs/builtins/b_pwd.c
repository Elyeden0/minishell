/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 02:37:23 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 23:37:10 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	char	*pwd;
	size_t	l;

	if (getcwd(buf, sizeof(buf)))
		return (printf("%s\n", buf), 0);
	{
		pwd = get_env_value(env, "PWD");
		l = ft_strlen(pwd);
		if (l >= 2 && (ft_strncmp(pwd + l - 2, "/.", 2) == 0 || (l >= 3
					&& ft_strncmp(pwd + l - 3, "/..", 3) == 0)))
			return (printf("%s\n", pwd), 0);
	}
	perror("minishell: pwd");
	return (1);
}
