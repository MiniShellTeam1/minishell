/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_field_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:53:47 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:21:31 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_field(const char *str, size_t start, size_t end)
{
	char	*field;
	size_t	len;
	size_t	i;

	len = end - start;
	field = malloc(len + 1);
	if (!field)
		return (NULL);
	i = 0;
	while (i < len)
	{
		field[i] = str[start + i];
		i++;
	}
	field[len] = '\0';
	return (field);
}

static int	handle_field_end(const char *str, t_split_data *data)
{
	data->fields[data->field_index] = extract_field(str, data->field_start,
			data->i);
	if (!data->fields[data->field_index])
	{
		free_fields_on_error(data->fields, data->field_index);
		return (0);
	}
	data->field_index++;
	data->in_field = 0;
	return (1);
}

static void	handle_field_start(t_split_data *data)
{
	data->in_field = 1;
	data->field_start = data->i;
}

int	process_string_splitting(const char *str, t_split_data *data)
{
	while (str[data->i])
	{
		if (is_ifs_char(str[data->i]))
		{
			if (data->in_field)
			{
				if (!handle_field_end(str, data))
					return (0);
			}
		}
		else if (!data->in_field)
			handle_field_start(data);
		data->i++;
	}
	if (data->in_field)
		return (handle_field_end(str, data));
	return (1);
}

int	should_split_field(const char *token, size_t var_start)
{
	return (!is_in_single_quotes(token, var_start) && get_quote_state(token,
			var_start) != QUOTE_DOUBLE);
}
