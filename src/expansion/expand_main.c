/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 08:21:28 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_word(const char *token, t_master *master)
{
	char	*result;

	if (!token || !master)
		return (NULL);
	if (!has_expandable_variables(token))
		return (ft_strdup(token));
	result = process_token_expansion(token, master);
	if (!result)
		return (handle_expansion_error(NULL));
	return (result);
}

char	*process_token_expansion(const char *token, t_master *master)
{
	char	*result;
	size_t	pos;
	size_t	start;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	pos = 0;
	start = 0;
	while (token[pos])
	{
		if (token[pos] == '$')
		{
			result = append_literal_part(result, token, start, pos);
			if (!result)
				return (NULL);
			result = append_variable_part(result, token, &pos, master);
			if (!result)
				return (NULL);
			start = pos;
		}
		else
			pos++;
	}
	return (append_literal_part(result, token, start, pos));
}

char	*append_literal_part(char *result, const char *token, size_t start, size_t end)
{
	char	*literal;
	char	*new_result;

	if (start >= end)
		return (result);
	literal = expand_literal_section(token, start, end);
	if (!literal)
		return (handle_expansion_error(result));
	new_result = join_expansion_parts(result, literal);
	return (new_result);
}

char	*append_variable_part(char *result, const char *token, size_t *pos, t_master *master)
{
	char	*var_expansion;
	char	*new_result;

	var_expansion = expand_single_variable(token, pos, master);
	if (!var_expansion)
		return (handle_expansion_error(result));
	new_result = join_expansion_parts(result, var_expansion);
	return (new_result);
}

int	needs_expansion(const char *token)
{
	if (!token)
		return (0);
	return (has_expandable_variables(token));
}