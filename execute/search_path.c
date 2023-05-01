/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:19 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/29 17:33:20 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			is_a_path_or_a_directory(char *cmd);

int	search_and_set_path_for_cmds(t_pipeline *plist)
{
	char	*cmd_path;

	if (*(plist->cmd) == '\0')
		return (cmd_notfound(plist->cmd), update_exit_status(127), EOF);
	if (is_a_path_or_a_directory(plist->cmd))
		return (true);
	cmd_path = getpath(plist->cmd);
	if (cmd_path == NULL)
		return (EOF);
	free(plist->cmd);
	plist->cmd = cmd_path;
	return (true);
}

int	is_a_path_or_a_directory(char *cmd)
{
	return (*cmd == '.' || *cmd == '/' || is_a_directory(cmd));
}
