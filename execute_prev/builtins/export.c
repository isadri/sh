/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:27:34 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/27 10:20:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	display_exported_variables(void);
static int	export_new_envvar(char *new_envvar);
static bool	is_not_a_valid_envvar(char *envvar);
static void	invalid_identifier(char *identifier);

int	exportcmd(char **args)
{
	int	i;

	if (args[0] == NULL)
		return (display_exported_variables());
	i = -1;
	while (args[++i])
	{
		if (export_new_envvar(args[i]) == EOF)
			return (EOF);
	}
	update_exit_status(0);
	return (true);
}

static int	display_exported_variables(void)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, "_") == 0)
		{
			envlist = envlist->next;
			continue ;
		}
		printf("declare -x %s", envlist->key);
		if (envlist->value != NULL)
			printf("=\"%s\"", envlist->value);
		printf("\n");
		envlist = envlist->next;
	}
	return (true);
}

static int	export_new_envvar(char *new_envvar)
{
	char	*key;
	char	*value;
	size_t	len;

	if (is_not_a_valid_envvar(new_envvar))
		return (EOF);
	len = 0;
	while (new_envvar[len] && new_envvar[len] != '=' && new_envvar[len] != '+')
		len++;
	key = ft_substr(new_envvar, 0, len);
	value = NULL;
	if (set_value_of_new_envvar(new_envvar, &value, len) == ADD)
		add_new_envvar(key, value);
	else
		join_new_envvar(key, value);
	return (true);
}

static bool	is_not_a_valid_envvar(char *envvar)
{
	int	i;

	if (!ft_isalpha(envvar[0]) && envvar[0] != '_')
		return (invalid_identifier(envvar), true);
	i = 1;
	while (envvar[i] && envvar[i] != '=')
	{
		if (!ft_isalnum(envvar[i]) && envvar[i] != '_' && envvar[i] != '+')
			return (invalid_identifier(envvar), true);
		if (envvar[i] == '+' && envvar[i + 1] != '=')
			return (invalid_identifier(envvar), true);
		i++;
	}
	return (false);
}

static void	invalid_identifier(char *identifier)
{
	ft_fprintf(2, "sh: export: `%s': not a valid identifier\n", identifier);
	update_exit_status(1);
}