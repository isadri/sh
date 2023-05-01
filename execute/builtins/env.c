/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:31:51 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/29 17:31:53 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	display_current_environment(void);

int	envcmd(char **args)
{
	if (args[0] != NULL)
	{
		ft_fprintf(2, "env: `%s': No such file or a directory\n", args[1]);
		return (EOF);
	}
	display_current_environment();
	update_exit_status(0);
	return (true);
}

static void	display_current_environment(void)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		ft_fprintf(1, "%s", envlist->key);
		if (envlist->value != NULL)
			ft_fprintf(1, "=%s", envlist->value);
		ft_fprintf(1, "\n");
		envlist = envlist->next;
	}
}
