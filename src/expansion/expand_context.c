/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:43:12 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_single_quotes(const char *token, size_t pos)
{
	size_t	i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos && token[i])
	{
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single);
}

int	should_expand_variable(const char *token, size_t dollar_pos)
{
	return (!is_in_single_quotes(token, dollar_pos));
}

t_quote_state	get_quote_state(const char *token, size_t pos)
{
	size_t	i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos && token[i])
	{
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single)
		return (QUOTE_SINGLE);
	if (in_double)
		return (QUOTE_DOUBLE);
	return (QUOTE_NONE);
}

int	has_expandable_variables(const char *token)
{
	size_t	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && should_expand_variable(token, i))
			return (1);
		i++;
	}
	return (0);
}

size_t	skip_quoted_section(const char *token, size_t start_pos)
{
	char	quote_char;
	size_t	i;

	quote_char = token[start_pos];
	i = start_pos + 1;
	while (token[i] && token[i] != quote_char)
		i++;
	if (token[i] == quote_char)
		i++;
	return (i);
}
