/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:13:58 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 14:15:37 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	debug_print_tokens(t_lexer *lx)
// {
// 	t_token	*cur;
// 	int		i;
// 	static const char *names[] = {[T_WORD] = "WORD",
// 									[T_PIPE] = "PIPE",
// 									[T_AND_IF] = "AND_IF",
// 									[T_OR_IF] = "OR_IF",
// 									[T_SEMI] = "SEMI",
// 									[T_REDIR_IN] = "REDIR_IN",
// 									[T_HEREDOC] = "HEREDOC",
// 									[T_REDIR_OUT] = "REDIR_OUT",
// 									[T_APPEND] = "APPEND",
// 									[T_LPAREN] = "LPAREN", /* ajouté */
// 									[T_RPAREN] = "RPAREN", /* ajouté */
// 									[T_EOL] = "EOL"};
// 	cur = lx->head;
// 	i = 0;
// 	while (cur)
// 	{
// 		printf("[%02d] %s", i, names[cur->type]);
// 		if (cur->value)
// 			printf(" => '%s'", cur->value);
// 		printf("\n");
// 		cur = cur->next;
// 		i++;
// 	}
// }

// const char	*ast_type_str(t_ast_type type)
// {
// 	if (type == AST_CMD)
// 		return "CMD";
// 	if (type == AST_PIPE)
// 		return "PIPE";
// 	if (type == AST_AND)
// 		return "AND";
// 	if (type == AST_OR)
// 		return "OR";
// 	if (type == AST_SEMI)
// 		return "SEMI";
// 	if (type == AST_SUBSHELL)
// 		return "SUBSHELL";
// 	return "UNKNOWN";
// }

// const char	*redir_type_str(t_token_type type)
// {
// 	if (type == T_REDIR_IN)
// 		return "<";
// 	if (type == T_REDIR_OUT)
// 		return ">";
// 	if (type == T_APPEND)
// 		return ">>";
// 	if (type == T_HEREDOC)
// 		return "<<";
// 	return "?";
// }

// void	debug_print_ast(t_ast *node, int depth)
// {
// 	int		i;
// 	t_redir	*r;

// 	if (!node)
// 		return ;
// 	// indentation
// 	for (i = 0; i < depth; i++)
// 		printf("  ");
// 	// affichage du nœud courant
// 	printf("%s\n", ast_type_str(node->type));
// 	// détails selon le type
// 	if (node->type == AST_CMD)
// 	{
// 		// afficher argv
// 		for (i = 0; node->argv && node->argv[i]; i++)
// 		{
// 			for (int j = 0; j < depth + 1; j++)
// 				printf("  ");
// 			printf("arg[%d]: '%s'\n", i, node->argv[i]);
// 		}
// 		// afficher redirections
// 		r = node->redirs;
// 		while (r)
// 		{
// 			for (int j = 0; j < depth + 1; j++)
// 				printf("  ");
// 			printf("redir: %s '%s'\n", redir_type_str(r->type), r->target);
// 			r = r->next;
// 		}
// 	}
// 	else if (node->type == AST_SUBSHELL)
// 	{
// 		// enfant unique
// 		debug_print_ast(node->child, depth + 1);
// 	}
// 	else
// 	{
// 		// binaire : left et right
// 		debug_print_ast(node->left, depth + 1);
// 		debug_print_ast(node->right, depth + 1);
// 	}
// }
