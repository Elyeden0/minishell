/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:03 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 22:00:14 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../LibMalloc/ft_malloc.h"

int		ft_atoi(const char *str);
char	*ft_strtrim(const char *s1, const char *set);
int		ft_strncmp(const char *s1, const char *s2, int n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
char	**ft_split(char *str, char *charset);

#endif
