/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:20 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 03:33:11 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_handle_char(va_list args, t_format *format)
{
	char	c;
	char	*str;

	(void)format;
	c = (char)va_arg(args, int);
	str = ft_malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_handle_string(va_list args, t_format *format)
{
	char	*arg;
	int		len;
	char	*str;

	arg = va_arg(args, char *);
	if (!arg)
		arg = "(null)";
	len = ft_strlen(arg);
	if (format->precision == 0)
		return (ft_strdup(""));
	if (format->precision < 6 && format->precision > 0 && ft_strcmp(arg,
			"(null)") == 0)
		return (ft_strdup(""));
	if (format->precision >= 0 && format->precision < len)
		len = format->precision;
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strncpy(str, arg, len);
	str[len] = '\0';
	return (str);
}

char	*ft_handle_pointer(va_list args, t_format *format)
{
	unsigned long long	ptr;
	char				*hex_str;
	int					len;
	char				*full_str;

	(void)format;
	ptr = (unsigned long long)va_arg(args, void *);
	if (ptr == 0)
		return (ft_strdup("(nil)"));
	hex_str = ft_xtoa(ptr, 0);
	len = ft_strlen(hex_str) + 2;
	full_str = ft_malloc(len + 1);
	if (!full_str)
		return (NULL);
	full_str[0] = '0';
	full_str[1] = 'x';
	ft_strcpy(full_str + 2, hex_str);
	return (full_str);
}
