/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:10 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 03:33:38 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../LibMalloc/ft_malloc.h"
# include <stdarg.h>
# include <unistd.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# define FLAG_MINUS 1
# define FLAG_ZERO 2
# define FLAG_HASH 4
# define FLAG_SPACE 8
# define FLAG_PLUS 16

typedef struct s_format
{
	int			flags;
	int			width;
	int			precision;
	char		specifier;
}				t_format;

typedef char	*(*t_handler)(va_list args, t_format *format);

int				ft_printf(const char *format, ...);

char			*ft_handle_char(va_list args, t_format *format);
char			*ft_handle_string(va_list args, t_format *format);
char			*ft_handle_int(va_list args, t_format *format);
char			*ft_handle_unsigned(va_list args, t_format *format);
char			*ft_handle_hex(va_list args, t_format *format);
char			*ft_handle_pointer(va_list args, t_format *format);
char			*ft_handle_percent(va_list args, t_format *format);

int				ft_parse_format(const char **format, t_format *f);
char			*ft_apply_flags(t_format *format, char *str);

char			*ft_itoa(int n);
char			*ft_utoa(unsigned int n);
char			*ft_xtoa(unsigned long long n, int uppercase);

char			*ft_apply_hash_flag(t_format *format, char *str, int *len);
char			*ft_apply_zero_padding(t_format *format, char *str, int *len,
					int width);

void			*ft_memset(void *s, int c, unsigned int n);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);

#endif
