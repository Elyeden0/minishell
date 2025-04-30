/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:50:27 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 19:51:49 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_string(char *src)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	dest = ft_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	copy_to_buffer(char *dest, char *src, int *index)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[*index] = src[i];
		(*index)++;
		i++;
	}
}

char	*combine_name_params(char *name, char *params)
{
	char	*result;
	int		name_len;
	int		params_len;
	int		index;

	name_len = 0;
	while (name[name_len])
		name_len++;
	params_len = 0;
	while (params[params_len])
		params_len++;
	result = ft_malloc(sizeof(char) * (name_len + params_len + 1));
	index = 0;
	copy_to_buffer(result, name, &index);
	copy_to_buffer(result, params, &index);
	result[index] = '\0';
	return (result);
}

void	check_existing_vars(t_env *env, int *has_pwd, int *has_oldpwd,
		int *has_path)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->name && !ft_strncmp(tmp->name, "PWD=", 4))
			*has_pwd = 1;
		else if (tmp->name && !ft_strncmp(tmp->name, "OLDPWD=", 7))
			*has_oldpwd = 1;
		else if (tmp->name && !ft_strncmp(tmp->name, "PATH=", 5))
			*has_path = 1;
		tmp = tmp->next;
	}
}

char	*copy_name_with_equal(char *envp)
{
	int		i;
	char	*name;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	name = ft_malloc(sizeof(char) * (i + 2));
	i = 0;
	while (envp[i] && envp[i] != '=')
	{
		name[i] = envp[i];
		i++;
	}
	if (envp[i] == '=')
		name[i++] = '=';
	name[i] = '\0';
	return (name);
}
