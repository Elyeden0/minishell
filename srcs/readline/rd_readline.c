/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:56:05 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:19:26 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_readline_loop(t_v *v, t_hv *hv, struct termios *orig,
		t_env *env)
{
	ssize_t				r;

	while (1)
	{
		r = read(STDIN_FILENO, &v->c, 1);
		if (r < 0 && errno == EINTR && g_signal == SIGINT)
			return (ft_sigint_reset(orig, &v->buf));
		if (r <= 0 || (v->c == 4 && v->pos == 0))
			return (ft_eof_reset(orig, v->buf));
		if (v->c == '\n')
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (v->c == 127)
			ft_handle_backspace(v->buf, &v->pos);
		else if (v->c == 27 && ft_handle_escape(hv))
			;
		else if ((unsigned char)v->c >= 32 && (unsigned char)v->c <= 126)
			ft_insert_char(&v->buf, &v->pos, &v->cap, v->c);
		else if (v->c == '\t')
			handle_tab_completion(v, hv, env);
	}
	ft_restore_termios(orig);
	return (v->buf);
}

char	*ft_readline(const char *prompt, t_env *env)
{
	static t_state	st;
	t_v				v;
	t_hv			hv;
	char			*res;

	st.curr = NULL;
	ft_init_termios(&st.inited, &st.orig, &st.raw);
	ft_print_prompt(prompt);
	v.cap = 128;
	v.pos = 0;
	v.buf = ft_malloc(v.cap);
	if (!v.buf)
		return (NULL);
	v.buf[0] = '\0';
	hv.prompt = prompt;
	hv.buf = v.buf;
	hv.pos = &v.pos;
	hv.tail = &st.tail;
	hv.curr = &st.curr;
	hv.save = NULL;
	res = ft_readline_loop(&v, &hv, &st.orig, env);
	if (res)
		ft_add_history(res, &st.tail);
	return (res);
}
