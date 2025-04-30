/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:00 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 16:56:01 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*my_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	while (n)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

void	*my_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n)
	{
		*p = (unsigned char)c;
		p++;
		n--;
	}
	return (s);
}
