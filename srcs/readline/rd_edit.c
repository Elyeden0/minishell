/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:55:48 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 00:54:03 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	size_t				i;

	d = dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;

	d = dest;
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}

void	ft_handle_backspace(char *buf, size_t *pos)
{
	size_t	len;
	size_t	suffix_len;

	if (*pos == 0)
		return ;
	len = ft_strlen(buf);
	ft_memmove(buf + *pos - 1, buf + *pos, len - *pos + 1);
	(*pos)--;
	write(1, "\x1b[D\x1b[K", 6);
	suffix_len = ft_strlen(buf + *pos);
	write(1, buf + *pos, suffix_len);
	while (suffix_len--)
		write(1, "\x1b[D", 3);
}

void	ft_insert_mid(char **buf, size_t *pos, char c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(*buf);
	ft_memmove(*buf + *pos + 1, *buf + *pos, len - *pos + 1);
	(*buf)[*pos] = c;
	(*pos)++;
	write(1, "\x1b[K", 4);
	write(1, *buf + *pos - 1, len - (*pos - 1) + 1);
	i = 0;
	while (i < len - (*pos - 1))
	{
		write(1, "\x1b[D", 3);
		i++;
	}
}

void	ft_insert_char(char **buf, size_t *pos, size_t *cap, char c)
{
	size_t	len;

	len = ft_strlen(*buf);
	if (len + 1 >= *cap)
	{
		*cap *= 2;
		*buf = ft_realloc(*buf, *cap);
	}
	if (*pos < len)
		ft_insert_mid(buf, pos, c);
	else
	{
		(*buf)[(*pos)++] = c;
		(*buf)[*pos] = '\0';
		write(1, &c, 1);
	}
}
