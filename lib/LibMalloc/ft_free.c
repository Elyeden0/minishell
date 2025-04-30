/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:36 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 17:06:37 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	ft_free_blocks(t_garbage **blocks)
{
	t_garbage	*block;
	t_garbage	*next;

	block = *blocks;
	while (block)
	{
		next = block->next;
		free(block->data);
		free(block);
		block = next;
	}
	*blocks = NULL;
}

void	ft_free_all(void)
{
	t_garbage_table	*table;

	table = get_garbage_table();
	ft_free_blocks(&table->blocks);
	table->current_block = NULL;
	table->offset = 0;
	ft_free_blocks(&table->large_blocks);
}
