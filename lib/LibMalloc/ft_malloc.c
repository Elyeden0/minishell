/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:49 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 22:08:48 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	*align_pointer(void *ptr)
{
	return ((void *)(((t_uintptr)ptr + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1)));
}

t_garbage_table	*get_garbage_table(void)
{
	static t_garbage_table	table = {NULL, NULL, NULL, 0};

	return (&table);
}

static void	*allocate_large_block(size_t size, t_garbage_table *table)
{
	void			*large_alloc;
	t_malloc_header	*header;
	t_garbage		*new_large_block;

	large_alloc = malloc(size + HEADER_SIZE);
	if (!large_alloc)
		return (NULL);
	header = large_alloc;
	header->size = size;
	new_large_block = malloc(sizeof(t_garbage));
	if (!new_large_block)
		return (NULL);
	new_large_block->data = large_alloc;
	new_large_block->next = table->large_blocks;
	table->large_blocks = new_large_block;
	return ((char *)large_alloc + HEADER_SIZE);
}

static void	allocate_new_block(t_garbage_table *table)
{
	t_garbage	*new_garbage;
	void		*new_block;

	new_block = malloc(BLOCK_SIZE);
	if (!new_block)
		return ;
	new_garbage = malloc(sizeof(t_garbage));
	if (!new_garbage)
	{
		free(new_block);
		return ;
	}
	new_garbage->data = new_block;
	new_garbage->next = table->blocks;
	table->blocks = new_garbage;
	table->current_block = new_block;
	table->offset = 0;
}

void	*ft_malloc(size_t size)
{
	t_garbage_table	*table;
	void			*ptr;
	void			*aligned_ptr;
	t_malloc_header	*header;
	size_t			total_size;

	if (size == 0)
		return (NULL);
	size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
	table = get_garbage_table();
	if (size >= LARGE_ALLOC_THRESHOLD)
		return (allocate_large_block(size, table));
	total_size = HEADER_SIZE + ALIGNMENT - 1 + size;
	if (!table->current_block || table->offset + total_size > BLOCK_SIZE)
		allocate_new_block(table);
	if (!table->current_block)
		return (NULL);
	ptr = (char *)table->current_block + table->offset;
	aligned_ptr = align_pointer((char *)ptr + HEADER_SIZE);
	header = (t_malloc_header *)((char *)aligned_ptr - HEADER_SIZE);
	header->size = size;
	table->offset = (char *)aligned_ptr + size - (char *)table->current_block;
	return (aligned_ptr);
}
