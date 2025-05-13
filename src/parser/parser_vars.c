/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/13 02:04:36 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			&& token[i] != '_' && token[i] != '?')
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

int	process_token_variable(t_parser_data *data)
{
	char *expanded, *result, *temp_token;
	t_token_list *new_tokens;
	size_t i, pos, var_len;
	char *new_result;

	result = ft_strdup("");
	if (!result)
		return (0);
	temp_token = data->token;
	pos = 0;
	while (temp_token[pos])
	{
		if (temp_token[pos] == '$')
		{
			expanded = expand_variable(temp_token + pos, data->master);
			if (!expanded)
			{
				free(result);
				return (0);
			}

			new_result = ft_strjoin(result, expanded);
			free(result);
			free(expanded);
			if (!new_result)
				return (0);
			result = new_result;

			get_var_name(temp_token + pos, &var_len);
			pos += var_len + 1;
		}
		else
		{
			size_t start = pos;
			while (temp_token[pos] && temp_token[pos] != '$')
				pos++;

			char *prefix = ft_strndup(temp_token + start, pos - start);
			if (!prefix)
			{
				free(result);
				return (0);
			}
			new_result = ft_strjoin(result, prefix);
			free(result);
			free(prefix);
			if (!new_result)
				return (0);
			result = new_result;
		}
	}

	new_tokens = lexer(result);
	free(result);

	if (!new_tokens)
		return (0);

	i = 0;
	while (i < new_tokens->count)
	{
		char *stripped = strip_quotes(new_tokens->tokens[i]);
		if (!stripped)
		{
			free_token_list(new_tokens);
			return (0);
		}

		if (!add_arg(*(data->cmd), stripped))
		{
			free(stripped);
			free_token_list(new_tokens);
			return (0);
		}

		free(stripped);
		i++;
	}

	free_token_list(new_tokens);
	return (1);
}