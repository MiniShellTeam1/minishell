/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feanor <feanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/03 08:21:17 by feanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_single_variable(const char *token, size_t *pos, t_master *master)
{
	char	*var_name;
	char	*var_value;
	size_t	var_len;

	if (!should_expand_variable(token, *pos))
	{
		(*pos)++;
		return (ft_strdup("$"));
	}
	var_name = get_var_name(token, *pos, &var_len);
	if (!var_name)
	{
		(*pos)++;
		return (ft_strdup("$"));
	}
	var_value = get_var_value(var_name, master);
	free(var_name);
	*pos += var_len + 1;
	return (var_value);
}

char	*expand_literal_section(const char *token, size_t start, size_t end)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = token[start + i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

char	*join_expansion_parts(char *existing, char *new_part)
{
	char	*result;

	if (!existing)
		return (new_part);
	if (!new_part)
		return (existing);
	result = ft_strjoin(existing, new_part);
	free(existing);
	free(new_part);
	return (result);
}

int	find_variable_end(const char *token, size_t dollar_pos)
{
	size_t	i;

	i = dollar_pos + 1;
	if (token[i] == '?')
		return (i + 1);
	while (token[i] && is_valid_var_char(token[i]))
		i++;
	return (i);
}

char	*handle_expansion_error(char *partial_result)
{
	if (partial_result)
		free(partial_result);
	return (NULL);
}