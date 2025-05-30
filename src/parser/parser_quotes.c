/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/30 14:21:21 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(char *token)
{
	size_t	len;
	char	*result;

	if (!token)
		return (NULL);
	len = ft_strlen(token);
	if (len == 0)
		return (ft_strdup(""));
	if (len >= 2 && ((token[0] == '"' && token[len - 1] == '"')
			|| (token[0] == '\'' && token[len - 1] == '\'')))
	{
		if (len == 2)
			return (ft_strdup(""));
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		ft_strlcpy(result, token + 1, len - 1);
		return (result);
	}
	return (ft_strdup(token));
}

int	is_variable(char *token)
{
	if (!token || token[0] != '$')
		return (0);
	if (token[1] == '?' || (token[1] >= 'A' && token[1] <= 'Z'))
		return (1);
	return (0);
}

static char	*get_var_name(char *token, size_t *var_len)
{
	char	*var_name;
	size_t	i;

	*var_len = 0;
	i = 1;
	while (token[i])
	{
		if (!(token[i] >= 'A' && token[i] <= 'Z') && !(token[i] >= 'a'
				&& token[i] <= 'z') && !(token[i] >= '0' && token[i] <= '9')
			&& token[i] != '_')
			break ;
		(*var_len)++;
		i++;
	}
	if (*var_len == 0)
		return (NULL);
	var_name = malloc(*var_len + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < *var_len)
	{
		var_name[i] = token[i + 1];
		i++;
	}
	var_name[*var_len] = '\0';
	return (var_name);
}

char	*expand_variable(char *token, t_master *master)
{
	t_env	*env;
	char	*var_name;
	size_t	var_name_len;

	if (!token || token[0] != '$')
		return (ft_strdup(token));
	if (!ft_strncmp(token, "$?", 2))
		return (ft_itoa(master->errorcode));
	var_name = get_var_name(token, &var_name_len);
	if (!var_name)
		return (ft_strdup("$"));
	env = master->env;
	while (env)
	{
		if (!ft_strcmp(var_name, env->key))
		{
			free(var_name);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free(var_name);
	return (ft_strdup(""));
}
