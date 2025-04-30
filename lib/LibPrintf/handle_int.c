/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:24 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 16:56:26 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_int(va_list args, t_format *format)
{
	long long	n;

	if (format->specifier == 'd' || format->specifier == 'i')
		n = va_arg(args, int);
	else if (format->specifier == 'l')
		n = va_arg(args, long);
	else if (format->specifier == 'L')
		n = va_arg(args, long long);
	else
		return (NULL);
	return (ft_itoa(n));
}

char	*ft_handle_unsigned(va_list args, t_format *format)
{
	unsigned int	n;

	(void)format;
	n = va_arg(args, unsigned int);
	return (ft_utoa(n));
}

char	*ft_handle_hex(va_list args, t_format *format)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_xtoa(n, format->specifier == 'X'));
}

char	*ft_handle_percent(va_list args, t_format *format)
{
	(void)args;
	(void)format;
	return (ft_strdup("%"));
}
