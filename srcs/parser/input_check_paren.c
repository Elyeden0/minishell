/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_paren.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 02:23:44 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 02:23:51 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_lparen(int idx, t_paren_ctx *ctx)
{
	t_token_type	next;

	if (idx + 1 >= ctx->count)
	{
		report("newline");
		return (1);
	}
	next = ctx->toks[idx + 1];
	if (next != T_WORD && next != T_LPAREN)
	{
		report((char *)token_to_str(next));
		return (1);
	}
	ctx->stack[ctx->top++] = idx;
	return (0);
}

static int	process_rparen(int idx, t_paren_ctx *ctx)
{
	t_token_type	prev;

	if (ctx->top == 0)
	{
		report((char *)token_to_str(T_RPAREN));
		return (1);
	}
	prev = ctx->toks[idx - 1];
	if (prev != T_WORD && prev != T_RPAREN)
	{
		report((char *)token_to_str(T_RPAREN));
		return (1);
	}
	ctx->top--;
	return (0);
}

static int	iterate_parens(t_paren_ctx *ctx)
{
	int	j;

	j = 0;
	while (j < ctx->count)
	{
		if (ctx->toks[j] == T_LPAREN)
		{
			if (process_lparen(j, ctx))
				return (1);
		}
		else if (ctx->toks[j] == T_RPAREN)
		{
			if (process_rparen(j, ctx))
				return (1);
		}
		j++;
	}
	return (0);
}

int	check_paren_ops(t_token_type toks[], int count)
{
	t_paren_ctx	ctx;
	int			*stack;
	int			err;

	stack = ft_malloc(sizeof(*stack) * count);
	if (!stack)
		return (1);
	ctx.toks = toks;
	ctx.count = count;
	ctx.stack = stack;
	ctx.top = 0;
	err = iterate_parens(&ctx);
	if (!err && ctx.top > 0)
	{
		report("newline");
		err = 1;
	}
	return (err);
}
