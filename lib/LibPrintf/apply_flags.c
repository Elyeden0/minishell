/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:07 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 18:06:48 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_handle_zero_precision(t_format *format, char *str, int *len)
{
	if (format->precision == 0 && str[0] == '0' && str[1] == '\0'
		&& (format->specifier == 'd' || format->specifier == 'i'
			|| format->specifier == 'u' || format->specifier == 'x'
			|| format->specifier == 'X'))
	{
		str = ft_malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		*len = 0;
	}
	return (str);
}

static char	*ft_apply_precision(t_format *format, char *str, int *len,
		int is_negative)
{
	int		zero_padding;
	char	*new_str;
	int		i;

	if (format->precision >= 0 && format->specifier != 's')
	{
		zero_padding = format->precision - (*len - is_negative);
		if (zero_padding > 0)
		{
			new_str = ft_malloc(*len + zero_padding + 1);
			if (!new_str)
				return (str);
			i = 0;
			if (is_negative)
				new_str[i++] = '-';
			ft_memset(new_str + i, '0', zero_padding);
			ft_strcpy(new_str + i + zero_padding, str + is_negative);
			str = new_str;
			*len = ft_strlen(str);
		}
	}
	return (str);
}

static char	*ft_apply_sign(t_format *format, char *str, int *len,
		int is_negative)
{
	char	*new_str;
	char	sign;

	if ((format->flags & FLAG_PLUS || format->flags & FLAG_SPACE)
		&& !is_negative)
	{
		new_str = ft_malloc(*len + 2);
		if (!new_str)
			return (str);
		sign = ' ';
		if (format->flags & FLAG_PLUS)
			sign = '+';
		new_str[0] = sign;
		ft_strcpy(new_str + 1, str);
		str = new_str;
		*len = ft_strlen(str);
	}
	return (str);
}

static char	*ft_apply_width(t_format *format, char *str, int len, int width)
{
	int		padding;
	char	*new_str;

	if (width > len)
	{
		padding = width - len;
		new_str = ft_malloc(width + 1);
		if (!new_str)
			return (str);
		if (format->flags & FLAG_MINUS)
		{
			ft_strcpy(new_str, str);
			ft_memset(new_str + len, ' ', padding);
		}
		else
		{
			ft_memset(new_str, ' ', padding);
			ft_strcpy(new_str + padding, str);
		}
		new_str[width] = '\0';
		str = new_str;
	}
	return (str);
}

char	*ft_apply_flags(t_format *format, char *str)
{
	int	len;
	int	is_negative;
	int	width;

	len = ft_strlen(str);
	width = format->width;
	is_negative = (str[0] == '-');
	str = ft_handle_zero_precision(format, str, &len);
	str = ft_apply_precision(format, str, &len, is_negative);
	str = ft_apply_sign(format, str, &len, is_negative);
	str = ft_apply_hash_flag(format, str, &len);
	str = ft_apply_zero_padding(format, str, &len, width);
	str = ft_apply_width(format, str, len, width);
	return (str);
}
