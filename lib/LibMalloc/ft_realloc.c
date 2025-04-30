/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:54 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 17:08:28 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_malloc_header	*get_header(void *ptr)
{
	void	*header_ptr;

	header_ptr = (char *)ptr - HEADER_SIZE;
	if ((t_uintptr)header_ptr % ALIGNMENT != 0)
		return (NULL);
	return ((t_malloc_header *)header_ptr);
}

static void	*copy_and_free_old(void *new_ptr, void *ptr, size_t old_size,
		size_t new_size)
{
	size_t	copy_size;

	if (!new_ptr)
		return (NULL);
	copy_size = old_size;
	if (old_size > new_size)
		copy_size = new_size;
	return (my_memcpy(new_ptr, ptr, copy_size));
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	t_malloc_header	*header;
	void			*new_ptr;

	if (!ptr)
		return (ft_malloc(new_size));
	if (new_size == 0)
		return (NULL);
	header = get_header(ptr);
	if (!header || header->size == 0 || header->size > LARGE_ALLOC_THRESHOLD)
		return (NULL);
	if (new_size <= header->size)
		return (ptr);
	new_ptr = ft_malloc(new_size);
	return (copy_and_free_old(new_ptr, ptr, header->size, new_size));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	ptr = ft_malloc(total_size);
	if (!ptr)
		return (NULL);
	return (my_memset(ptr, 0, total_size));
}
