/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:56:35 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 15:41:58 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_malloc.h"
# include "ft_printf.h"
# include "libft.h"
# include "liblist.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define BOLD_GREEN "\001\033[1;32m\002"
# define BOLD_BLUE "\001\033[1;34m\002"
# define BOLD_YELLOW "\001\033[1;33m\002"
# define RESET_COLOR "\001\033[0m\002"

// environnement
typedef struct s_env
{
	char						*data;
	int							show;
	char						*name;
	char						*params;
	struct s_env				*next;
}								t_env;

// historique
typedef struct s_hist
{
	char						*line;
	struct s_hist				*prev;
	struct s_hist				*next;
}								t_hist;

// gestion de readline
typedef struct s_v
{
	char						*buf;
	char						c;
	ssize_t						r;
	size_t						cap;
	size_t						pos;
}								t_v;

// variables pour readline + historique
typedef struct s_hv
{
	const char					*prompt;
	char						*buf;
	size_t						*pos;
	t_hist						**tail;
	t_hist						**curr;
	char						*save;
}								t_hv;

// état global (termios + historique)
typedef struct s_state
{
	int							inited;
	struct termios				orig;
	struct termios				raw;
	t_hist						*tail;
	t_hist						*curr;
}								t_state;

// ============================ LEXER / TOKENS ============================= //

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_AND_IF,
	T_OR_IF,
	T_SEMI,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT,
	T_APPEND,
	T_LPAREN,
	T_RPAREN,
	T_EOL
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_lexer
{
	char						*input;
	size_t						pos;
	t_token						*head;
	t_token						*tail;
}								t_lexer;

// pour le parsing des parenthèses
typedef struct s_paren_ctx
{
	t_token_type				*toks;
	int							count;
	int							*stack;
	int							top;
}								t_paren_ctx;

// ============================== EXPANSION ================================ //

typedef struct s_expander
{
	const char					*s;
	t_env						*env;
	int							last_status;
	char						*res;
	int							i;
}								t_expander;

typedef struct s_expand_data
{
	t_token						**tokens;
	t_token						*prev;
	t_token						*cur;
}								t_expand_data;

// ============================== AST / EXEC =============================== //

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SEMI,
	AST_SUBSHELL
}								t_ast_type;

typedef struct s_redir
{
	t_token_type				type;
	char						*target;
	struct s_redir				*next;
}								t_redir;

typedef struct s_ast
{
	t_ast_type					type;
	char						**argv;
	t_redir						*redirs;
	struct s_ast				*left;
	struct s_ast				*right;
	struct s_ast				*child;
}								t_ast;

extern volatile sig_atomic_t	g_signal;

// Libc / Utils
void							*ft_memcpy(void *dest, const void *src,
									size_t n);
void							*ft_memmove(void *dest, const void *src,
									size_t n);
char							*ft_strchr(const char *s, int c);
char							*ft_strndup(const char *s, size_t n);
char							*ft_strjoin(char const *s1, char const *s2);
int								is_alpha(char c);
int								ft_isalnum(int c);

// Signals
void							ft_sigint_handler(int sig);
void							ft_sigquit_handler(int sig);
void							ft_setup_signal(void);

// Terminal management (termios)
void							ft_init_termios(int *inited,
									struct termios *orig, struct termios *raw);
void							ft_restore_termios(const struct termios *orig);

// Prompt et readline (édition de ligne)
void							ft_print_prompt(const char *prompt);
char							*ft_readline(const char *prompt);
void							ft_handle_backspace(char *buf, size_t *pos);
void							ft_insert_mid(char **buf, size_t *pos, char c);
void							ft_insert_char(char **buf, size_t *pos,
									size_t *cap, char c);
int								ft_handle_escape(t_hv *hv);
void							ft_add_history(char *line, t_hist **tail);
void							ft_history_up(t_hv *hv);
void							ft_history_down(t_hv *hv);

// Gestion readline : reset spécial (ctrl-d, ctrl-c)
char							*ft_sigint_reset(const struct termios *orig,
									char **bp);
char							*ft_eof_reset(const struct termios *orig,
									char *buf);

// Syntax error (prélexer pour erreurs de syntaxe)
int								syntax_error(const char *line);
void							report(char *s);
const char						*token_to_str(t_token_type type);
void							skip_spaces(const char *l, int *i);
int								skip_quotes(const char *l, int *i);

// Tokenizer simplifié pour syntax_error
t_token_type					next_token(const char *l, int *i);
void							lex_line(const char *l, t_token_type t[],
									int *c);
t_token_type					get_redir_double(const char *l, int *i);
t_token_type					get_logic_double(const char *l, int *i);
t_token_type					get_double_op(const char *l, int *i);
t_token_type					get_single_op(const char *l, int *i);
t_token_type					get_operator(const char *l, int *i);

// Vérification de syntaxe
int								is_cmd_op(t_token_type t);
int								handle_cmd_op_error(t_token_type t[], int j,
									int c);
int								check_cmd_ops(t_token_type t[], int c);
int								check_redir_ops(t_token_type t[], int c);
int								check_paren_ops(t_token_type t[], int c);

// Lexer final (utilisé pour AST)
t_lexer							*lexer_init(char *line);
void							lexer_add_token(t_lexer *lx, t_token_type type,
									char *value);
void							tokenize(t_lexer *lx);
int								process_redirection_char(t_lexer *lx, char c,
									t_token_type single, t_token_type dbl);
int								handle_and_or(t_lexer *lx);
int								handle_single_char(t_lexer *lx);
int								handle_redirection(t_lexer *lx);
void							handle_word(t_lexer *lx);
void							handle_quote(t_lexer *lx, char *buf, size_t *i,
									char quote);
void							handle_regular_char(t_lexer *lx, char *buf,
									size_t *i);
char							lexer_peek(t_lexer *lx);
void							lexer_advance(t_lexer *lx);
int								is_op_char(char c);
void							skip_whitespace(t_lexer *lx);

// Expansion ($, $? et wildcard)
void							expand_tokens(t_token *tok, t_env *env,
									int last_status);
void							expand_star_tokens(t_token **tokens);
char							*append_str(const char *dest, const char *src);
char							*itoa_status(int n);
void							handle_single(t_expander *ex);
char							*get_env_value(t_env *env, const char *key);
int								star_match(const char *pattern,
									const char *str);
void							sort_strings(char **arr, int n);
int								count_matching_files(const char *pattern);

// Builtins
int								builtin_pwd(t_env *env);
int								builtin_env(t_env *env, char **args);
int								builtin_unset(t_env *env, char **args);
int								builtin_export(t_env **env, char **args);
int								builtin_exit(char **args, int last_status);
int								builtin_echo(char **args);
int								builtin_cd(t_env **env, char **args);
void							print_export(t_env *env);
t_env							*create_node_env(char *envp);
t_env							*find_env(t_env *env, const char *name);
void							check_path_pwd_env(t_env *env);
t_env							*create_custom_node(char *name, char *params,
									int show);
char							*copy_string(char *src);
void							copy_to_buffer(char *dest, char *src,
									int *index);
char							*combine_name_params(char *name, char *params);
void							check_existing_vars(t_env *env, int *has_pwd,
									int *has_oldpwd, int *has_path);
char							*copy_name_with_equal(char *envp);
int								too_many_args(char **args);
char							*handle_home(t_env *env);
char							*handle_oldpwd(t_env *env, int *pf);
char							*build_target(t_env *env, char **args, int *pf);
int								do_cd(t_env **env, char *tgt, int pf);
int								set_env_var(t_env **env, const char *n,
									const char *v);
int								add_new_env(t_env **env, char *d);
int								update_existing_env(t_env *node, const char *n,
									const char *d);
int								update_pwd_vars(t_env **env, const char *prev,
									const char *tgt);
void							link_new_env(t_env **env, t_env *node);
int								is_valid_identifier(char *name);
size_t							strlen_equal(char *arg);

// AST parsing
t_ast							*parse_ast(t_lexer *lexer);
t_ast							*parse_list(t_token **cur);
t_ast							*parse_and_or(t_token **cur);
t_ast							*parse_pipeline(t_token **cur);
t_ast							*parse_simple_cmd(t_token **cur);
char							**collect_arguments(t_token **cur);
void							add_redirection(t_redir **head, t_redir **tail,
									t_redir *new_node);
t_redir							*collect_redirections(t_token **cur);

// AST builders
t_ast							*ast_new_cmd(char **argv, t_redir *redirs);
t_ast							*ast_new_binary(t_ast_type type, t_ast *left,
									t_ast *right);
t_ast							*ast_new_subshell(t_ast *child);
t_redir							*redir_new(t_token_type type,
									const char *target);

// AST utils
t_token_type					peek_type(t_token *cur);
bool							consume_token(t_token_type type, t_token **cur);

// Debug outils
void							debug_print_tokens(t_lexer *lx);
void							debug_print_ast(t_ast *node, int depth);

// Exec
int								exec_ast(t_ast *node, t_env **env,
									int last_status);
bool							is_builtin(const char *cmd);
int								run_builtin(char **argv, t_env **env,
									int last_status);
char							**env_to_charpp(t_env *env);
int								wait_child(pid_t pid);
int								exec_cmd(t_ast *cmd, t_env **env,
									int last_status);
void							apply_redirections(t_redir *redirs);
int								exec_pipeline(t_ast *node, t_env **env,
									int last_status);
void							redir_heredoc(const char *delimiter);

#endif
