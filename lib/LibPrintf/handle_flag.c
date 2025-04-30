/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:22 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 18:06:55 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_apply_hash_flag(t_format *format, char *str, int *len)
{
	char	*new_str;
	char	*prefix;
	int		new_len;

	if ((format->flags & FLAG_HASH) && (format->specifier == 'x'
			|| format->specifier == 'X') && str[0] != '0')
	{
		prefix = "0x";
		if (format->specifier == 'X')
			prefix = "0X";
		new_len = *len + 2;
		new_str = ft_malloc(new_len + 1);
		if (!new_str)
			return (str);
		ft_strcpy(new_str, prefix);
		ft_strcpy(new_str + 2, str);
		str = new_str;
		*len = new_len;
	}
	return (str);
}

static void	ft_fill_zero_padding(char *new_str, char *str, int zero_padding,
		int has_sign)
{
	if (has_sign)
	{
		new_str[0] = str[0];
		ft_memset(new_str + 1, '0', zero_padding);
		ft_strcpy(new_str + 1 + zero_padding, str + 1);
	}
	else
	{
		ft_memset(new_str, '0', zero_padding);
		ft_strcpy(new_str + zero_padding, str);
	}
}

static int	ft_needs_zero_padding(t_format *format, int width, int len)
{
	if (!(format->flags & FLAG_ZERO))
		return (0);
	if (width <= len)
		return (0);
	if (format->flags & FLAG_MINUS)
		return (0);
	if (format->precision >= 0)
		return (0);
	return (1);
}

char	*ft_apply_zero_padding(t_format *format, char *str, int *len, int width)
{
	int		zero_padding;
	char	*new_str;
	int		has_sign;

	if (!ft_needs_zero_padding(format, width, *len))
		return (str);
	zero_padding = width - *len;
	new_str = ft_malloc(*len + zero_padding + 1);
	if (!new_str)
		return (str);
	has_sign = (str[0] == '+' || str[0] == '-' || str[0] == ' ');
	ft_fill_zero_padding(new_str, str, zero_padding, has_sign);
	str = new_str;
	*len = ft_strlen(str);
	return (str);
}
