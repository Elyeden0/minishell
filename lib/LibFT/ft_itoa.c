/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:54:53 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 17:07:36 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static unsigned int	ft_nbrlen(int n)
{
	unsigned int	len;
	unsigned int	num;

	len = 1;
	num = ft_abs(n);
	while (num >= 10)
	{
		len++;
		num /= 10;
	}
	if (n < 0)
	{
		return (len + 1);
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	unsigned int	len;

	num = ft_abs(n);
	len = ft_nbrlen(n);
	str = (char *)ft_malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
