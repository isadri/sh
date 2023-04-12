/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:02:43 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 01:57:50y iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		join_sequence(char **lexeme, char *ptr, size_t len);
static int		get_sequence_length(char *tmp_ptr, char c);

char	*quote(char **ptr, char c)
{
	char	*lexeme;
	char	*tmp_ptr;
	int		len;

	tmp_ptr = *ptr;
	len = get_sequence_length(tmp_ptr, c);
	lexeme = NULL;
	if (tmp_ptr[len] == '\0')
	{
		ft_fprintf(2, "bash: syntax error\n");
		return (NULL);
	}
	join_sequence(&lexeme, tmp_ptr, len + 1);
	*ptr += (len + 1);
	return (lexeme);
}

static void	join_sequence(char **lexeme, char *ptr, size_t len)
{
	char	*sub;

	sub = ft_substr(ptr, 0, len);
	*lexeme = ft_strjoin(*lexeme, sub);
	free(sub);
}

static int	get_sequence_length(char *tmp_ptr, char c)
{
	size_t	len;

	len = 0;	//	skip the quote character
	if (tmp_ptr[len] == c)
		len++;
	while (tmp_ptr[len] != '\0' && tmp_ptr[len] != c)
		len++;
	return (len);
}