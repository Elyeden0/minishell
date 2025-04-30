/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorreal <emorreal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:54:55 by Evan              #+#    #+#             */
/*   Updated: 2025/04/08 17:25:42 by emorreal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	count_words(const char *str, const char *charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_charset(*str, charset) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_charset(*str, charset))
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*malloc_word(const char *str, const char *charset)
{
	int		len;
	char	*word;
	int		i;

	i = 0;
	len = 0;
	while (str[len] && !is_charset(str[len], charset))
		len++;
	word = ft_malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	skip_charset(char **str, const char *charset)
{
	while (**str && is_charset(**str, charset))
		(*str)++;
}

char	**ft_split(char *str, char *charset)
{
	int		count;
	char	**tab;
	int		i;

	if (!str || !charset)
		return (NULL);
	count = count_words(str, charset);
	if (count == 0)
		return (NULL);
	tab = ft_malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!tab)
		return (NULL);
	while (*str)
	{
		skip_charset(&str, charset);
		if (*str)
		{
			tab[i++] = malloc_word(str, charset);
			while (*str && !is_charset(*str, charset))
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
