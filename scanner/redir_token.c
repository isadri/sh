/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:14:40 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:00:25 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_tokentype	redir_input(char **pipeline, char **lexeme);
static t_tokentype	redir_output(char **pipeline, char **lexeme);

t_tokentype	getredir_token(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	type = NIL;
	if (s_match(pipeline, '<'))
		type = redir_input(pipeline, lexeme);
	else if (s_match(pipeline, '>'))
		type = redir_output(pipeline, lexeme);
	return (type);
}

static t_tokentype	redir_input(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	type = NIL;
	if (s_match(pipeline, '<'))
	{
		*lexeme = ft_strdup("<<");
		type = HEREDOC;
	}
	else
	{
		*lexeme = ft_strdup("<");
		type = REDIR_IN;
	}
	return (type);
}

static t_tokentype	redir_output(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	type = NIL;
	if (s_match(pipeline, '>'))
	{
		*lexeme = ft_strdup(">>");
		type = REDIR_OUT_APPEND;
	}
	else
	{
		*lexeme = ft_strdup(">");
		type = REDIR_OUT;
	}
	return (type);
}

int	isredir_opt(char c)
{
	return (c == '<' || c == '>');
}
