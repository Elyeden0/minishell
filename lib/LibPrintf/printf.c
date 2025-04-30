/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:30 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 17:43:25 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_handler	*ft_get_handlers(void)
{
	static t_handler	handlers[256];

	handlers['c'] = ft_handle_char;
	handlers['s'] = ft_handle_string;
	handlers['d'] = ft_handle_int;
	handlers['i'] = ft_handle_int;
	handlers['u'] = ft_handle_unsigned;
	handlers['x'] = ft_handle_hex;
	handlers['X'] = ft_handle_hex;
	handlers['p'] = ft_handle_pointer;
	handlers['%'] = ft_handle_percent;
	return (handlers);
}

static int	ft_print_char(va_list args, t_format *f)
{
	char	c;
	int		padding;
	int		total_printed;

	c = (char)va_arg(args, int);
	padding = 0;
	total_printed = 0;
	if (f->width > 1)
		padding = f->width - 1;
	if (f->flags & FLAG_MINUS)
	{
		total_printed += write(1, &c, 1);
		while (padding--)
			total_printed += write(1, " ", 1);
	}
	else
	{
		while (padding--)
			total_printed += write(1, " ", 1);
		total_printed += write(1, &c, 1);
	}
	return (total_printed);
}

static int	ft_process_format(va_list args, t_format *f, t_handler *handlers)
{
	char	*formatted_str;
	int		total_printed;

	total_printed = 0;
	if (f->specifier == 'c')
		return (ft_print_char(args, f));
	if (handlers[(int)f->specifier])
	{
		formatted_str = handlers[(int)f->specifier](args, f);
		formatted_str = ft_apply_flags(f, formatted_str);
		total_printed += write(1, formatted_str, ft_strlen(formatted_str));
	}
	return (total_printed);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	f;
	int			total_printed;
	t_handler	*handlers;

	handlers = ft_get_handlers();
	total_printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_parse_format(&format, &f) == -1)
				return (-1);
			total_printed += ft_process_format(args, &f, handlers);
		}
		else
			total_printed += write(1, format, 1);
		if (*format)
			format++;
	}
	va_end(args);
	return (total_printed);
}
