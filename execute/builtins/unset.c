/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:27:43 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 14:13:40 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_envvar(char *envvar);
static void	delete_envvar_node(t_env *envlist, t_env *tmp_ptr);
static bool	variable_is_found(char *key, char *envvar);

int	unsetcmd(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		unset_envvar(args[i]);
	update_exit_status(0);
	return (true);
}

static void	unset_envvar(char *envvar)
{
	t_env	*envlist;
	t_env	*tmp_ptr;

	envlist = g_gbl.envlist;
	tmp_ptr = g_gbl.envlist;
	while (envlist)
	{
		if (variable_is_found(envlist->key, envvar))
			break ;
		tmp_ptr = envlist;
		envlist = envlist->next;
	}
	if (envlist == NULL)
		return ;
	delete_envvar_node(envlist, tmp_ptr);
}

static void	delete_envvar_node(t_env *envlist, t_env *tmp_ptr)
{
	if (envlist == g_gbl.envlist)
		g_gbl.envlist = g_gbl.envlist->next;
	free(envlist->key);
	free(envlist->value);
	tmp_ptr->next = envlist->next;
	free(envlist);
}

static bool	variable_is_found(char *key, char *envvar)
{
	return (!ft_strcmp(key, envvar));
}
