/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:43:21 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 18:55:05 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static int	ft_itoa_length_base(unsigned long long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long long)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

static void	ft_itoa_fill(char *str, int n, int len, int base)
{
	int	i;

	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == INT_MIN)
		{
			str[len - 1] = '8';
			n /= 10;
		}
		n = -n;
	}
	i = len - 1;
	while (i >= 0)
	{
		if (str[0] == '-' && i == 0)
			break ;
		str[i] = '0' + (n % base);
		n /= base;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long long	nb;
	int			i;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
		nb = -nb;
	len = ft_itoa_length_base(nb, 10);
	if (n < 0)
		len++;
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		str[i] = '\0';
		i++;
	}
	return (ft_itoa_fill(str, n, len, 10), str);
}

char	*ft_utoa(unsigned int n)
{
	int				len;
	char			*str;
	unsigned int	num;

	num = n;
	len = ft_itoa_length_base(num, 10);
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

char	*ft_xtoa(unsigned long long n, int uppercase)
{
	int					len;
	char				*str;
	char				*base_chars;
	unsigned long long	num;

	num = n;
	if (uppercase)
		base_chars = "0123456789ABCDEF";
	else
		base_chars = "0123456789abcdef";
	len = ft_itoa_length_base(num, 16);
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = base_chars[num % 16];
		num /= 16;
	}
	return (str);
}
