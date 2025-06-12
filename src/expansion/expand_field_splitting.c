/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_field_splitting.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:49:38 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 10:54:32 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ifs_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static size_t	count_fields(const char *str)
{
	size_t	count;
	int		in_field;
	size_t	i;

	count = 0;
	in_field = 0;
	i = 0;
	while (str[i])
	{
		if (is_ifs_char(str[i]))
			in_field = 0;
		else if (!in_field)
		{
			in_field = 1;
			count++;
		}
		i++;
	}
	return (count);
}

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

static void	free_fields_on_error(char **fields, size_t field_index)
{
	while (field_index > 0)
		free(fields[--field_index]);
	free(fields);
}

char	**split_fields(const char *str)
{
	t_split_data	data;

	if (!str)
		return (NULL);
	data.field_count = count_fields(str);
	if (data.field_count == 0)
		return (NULL);
	data.fields = malloc(sizeof(char *) * (data.field_count + 1));
	if (!data.fields)
		return (NULL);
	data.field_index = 0;
	data.i = 0;
	data.in_field = 0;
	data.field_start = 0;
	if (!process_string_splitting(str, &data))
		return (NULL);
	data.fields[data.field_index] = NULL;
	return (data.fields);
}
