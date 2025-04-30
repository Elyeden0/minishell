/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:52 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 19:14:29 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>

# define BLOCK_SIZE 262144
# define HEADER_SIZE 16
# define ALIGNMENT 16
# define LARGE_ALLOC_THRESHOLD 250000

typedef struct s_malloc_header
{
	size_t				size;
}						t_malloc_header;

typedef struct s_garbage
{
	void				*data;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_garbage_table
{
	t_garbage			*blocks;
	t_garbage			*large_blocks;
	void				*current_block;
	size_t				offset;
}						t_garbage_table;

void					init_garbage_table(void);
t_garbage_table			*get_garbage_table(void);
void					*ft_malloc(size_t size);
void					*ft_calloc(size_t count, size_t size);
void					*ft_realloc(void *ptr, size_t new_size);
void					ft_free_all(void);
void					*my_memcpy(void *dest, const void *src, size_t n);
void					*my_memset(void *s, int c, size_t n);

typedef unsigned long	t_uintptr;

#endif /* FT_MALLOC_H */
