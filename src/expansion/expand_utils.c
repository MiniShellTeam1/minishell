/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 09:16:50 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(const char *token, size_t start_pos, size_t *var_len)
{
	char	*var_name;
	size_t	i;

	*var_len = 0;
	i = start_pos + 1;
	if (token[i] == '?')
	{
		*var_len = 1;
		var_name = malloc(2);
		if (!var_name)
			return (NULL);
		var_name[0] = '?';
		var_name[1] = '\0';
		return (var_name);
	}
	while (token[i] && is_valid_var_char(token[i]))
	{
		(*var_len)++;
		i++;
	}
	return (create_var_name_string(token, start_pos + 1, *var_len));
}

char	*get_var_value(const char *var_name, t_master *master)
{
	t_env	*env;

	if (!var_name || !master)
		return (ft_strdup(""));
	if (!ft_strcmp((char *)var_name, "?"))
		return (ft_itoa(master->errorcode));
	env = master->env;
	while (env)
	{
		if (!ft_strcmp((char *)var_name, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

int	is_valid_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
			(c >= '0' && c <= '9') || c == '_');
}

char	*create_var_name_string(const char *token, size_t start, size_t len)
{
	char	*var_name;
	size_t	i;

	if (len == 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_name[i] = token[start + i];
		i++;
	}
	var_name[len] = '\0';
	return (var_name);
}

size_t	find_next_dollar(const char *token, size_t start_pos)
{
	size_t	i;

	i = start_pos;
	while (token[i])
	{
		if (token[i] == '$')
			return (i);
		i++;
	}
	return (i);
}