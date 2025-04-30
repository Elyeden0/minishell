/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:27 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 16:56:29 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_parse_flags(const char **format, t_format *f)
{
	while (**format == '-' || **format == '0' || **format == '#'
		|| **format == ' ' || **format == '+')
	{
		if (**format == '-')
			f->flags |= FLAG_MINUS;
		if (**format == '0')
			f->flags |= FLAG_ZERO;
		if (**format == '#')
			f->flags |= FLAG_HASH;
		if (**format == ' ')
			f->flags |= FLAG_SPACE;
		if (**format == '+')
			f->flags |= FLAG_PLUS;
		(*format)++;
	}
}

static void	ft_parse_width(const char **format, t_format *f)
{
	while (**format >= '0' && **format <= '9')
	{
		f->width = f->width * 10 + (**format - '0');
		(*format)++;
	}
}

static void	ft_parse_precision(const char **format, t_format *f)
{
	if (**format == '.')
	{
		(*format)++;
		f->precision = 0;
		while (**format >= '0' && **format <= '9')
		{
			f->precision = f->precision * 10 + (**format - '0');
			(*format)++;
		}
	}
}

int	ft_parse_format(const char **format, t_format *f)
{
	f->flags = 0;
	f->width = 0;
	f->precision = -1;
	ft_parse_flags(format, f);
	ft_parse_width(format, f);
	ft_parse_precision(format, f);
	f->specifier = **format;
	if (!f->specifier)
		return (-1);
	return (0);
}
