/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_len_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:10:22 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 17:10:55 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*skip_ansi_sequence(const char *s)
{
	s += 2;
	while (*s && !isalpha((unsigned char)*s))
		s++;
	if (*s)
		s++;
	return (s);
}

size_t	visible_len(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == '\001')
		{
			s++;
			while (*s && *s != '\002')
				s++;
			if (*s == '\002')
				s++;
		}
		else if (*s == '\x1b' && *(s + 1) == '[')
			s = skip_ansi_sequence(s);
		else
		{
			len++;
			s++;
		}
	}
	return (len);
}
