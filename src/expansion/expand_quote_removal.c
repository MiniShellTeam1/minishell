/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:43:42 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *token)
{
	char	*result;
	size_t	result_len;

	if (!token)
		return (NULL);
	result_len = calculate_unquoted_length(token);
	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	return (build_unquoted_string(token, result));
}

size_t	calculate_unquoted_length(const char *token)
{
	size_t	len;
	size_t	i;
	int		in_single;
	int		in_double;

	len = 0;
	i = 0;
	in_single = 0;
	in_double = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		else
			len++;
		i++;
	}
	return (len);
}

char	*build_unquoted_string(const char *token, char *result)
{
	size_t	i;
	size_t	j;
	int		in_single;
	int		in_double;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		else
		{
			result[j] = token[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	has_quotes(const char *token)
{
	size_t	i;

	if (!token)
		return (0);
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*process_word_complete(const char *token, t_master *master)
{
	char	*expanded;
	char	*final_result;

	expanded = expand_word(token, master);
	if (!expanded)
		return (NULL);
	if (!has_quotes(expanded))
		return (expanded);
	final_result = remove_quotes(expanded);
	free(expanded);
	return (final_result);
}
