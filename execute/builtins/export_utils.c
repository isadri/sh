/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:27:26 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 15:32:10 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		update_existed_variable(t_env *envlist, char *value);
static t_env	*key_already_exists(char *variable);

int	set_value_of_new_envvar(char *new_envvar, char **value, size_t len)
{
	size_t	size;

	if (new_envvar[len] == '\0')
		return (ADD);
	if (new_envvar[len] == '=' && new_envvar[len + 1] == '\0')
		*value = ft_strdup("\0");
	else if (new_envvar[len] == '+')
	{
		size = ft_strlen(new_envvar) - (len + 2);
		if (new_envvar[len + 2] == '\0')
			*value = ft_strdup("\0");
		else
			*value = ft_substr(new_envvar, len + 2, size);
		return (JOIN);
	}
	size = ft_strlen(new_envvar) - (len + 1);
	*value = ft_substr(new_envvar, len + 1, size);
	return (ADD);
}

void	join_new_envvar(char *key, char *value)
{
	t_env	*envlist;
	char	*new_value;

	new_value = NULL;
	envlist = key_already_exists(key);
	if (envlist != NULL)
	{
		free(key);
		new_value = ft_strjoin(envlist->value, value);
		free(value);
		envlist->value = new_value;
		return ;
	}
	add_envvar(&g_gbl.envlist, key, value);
}

void	add_new_envvar(char *key, char *value)
{
	t_env	*envlist;

	envlist = key_already_exists(key);
	if (envlist != NULL)
		update_existed_variable(envlist, value);
	else
		add_envvar(&g_gbl.envlist, key, value);
}

static void	update_existed_variable(t_env *envlist, char *value)
{
	if (value == NULL)
		return ;
	free(envlist->value);
	envlist->value = value;
}

static t_env	*key_already_exists(char *variable)
{
	t_env	*envlist;

	envlist = g_gbl.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, variable) == 0)
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}