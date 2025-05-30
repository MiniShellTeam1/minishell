/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/30 15:46:02 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_var_name(char *token, size_t *var_len)
{
    char *var_name;
    size_t i;

    *var_len = 0;
    i = 1;
    
    // Special case: $? is complete by itself
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
    
    // Regular variable name
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

static char *get_var_value(char *var_name, t_master *master)
{
	t_env *env;

	if (!var_name)
		return (ft_strdup(""));
	if (!ft_strcmp(var_name, "?"))
		return (ft_itoa(master->errorcode));
	
	env = master->env;
	while (env)
	{
		if (!ft_strcmp(var_name, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static char *expand_all_variables(char *token, t_master *master)
{
	char *result;
	char *new_result;
	size_t i;
	size_t start;
	char *var_name;
	char *var_value;
	size_t var_len;
	char *literal_part;
	
	result = ft_strdup("");
	if (!result)
		return (NULL);
	
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			var_name = get_var_name(token + i, &var_len);
			if (var_name && var_len > 0)
			{
				var_value = get_var_value(var_name, master);
				if (var_value)
				{
					new_result = ft_strjoin(result, var_value);
					free(result);
					free(var_value);
					if (!new_result)
					{
						free(var_name);
						return (NULL);
					}
					result = new_result;
				}
				free(var_name);
				i += var_len + 1;
			}
			else
			{
				new_result = ft_strjoin(result, "$");
				free(result);
				if (!new_result)
					return (NULL);
				result = new_result;
				i++;
			}
		}
		else
		{
			start = i;
			while (token[i] && token[i] != '$')
				i++;
			
			literal_part = ft_strndup(token + start, i - start);
			if (!literal_part)
			{
				free(result);
				return (NULL);
			}
			new_result = ft_strjoin(result, literal_part);
			free(result);
			free(literal_part);
			if (!new_result)
				return (NULL);
			result = new_result;
		}
	}
	return (result);
}

int process_token_variable(t_parser_data *data)
{
    char *expanded;
    char *stripped;

    // printf("PARSER DEBUG - Original token: '%s'\n", data->token);
    
    expanded = expand_all_variables(data->token, data->master);
    if (!expanded)
        return (0);

    // printf("PARSER DEBUG - After expansion: '%s'\n", expanded);

    stripped = strip_quotes(expanded);
    free(expanded);
    if (!stripped)
        return (0);

    // printf("PARSER DEBUG - After strip_quotes: '%s'\n", stripped);

    if (!add_arg(*(data->cmd), stripped))
    {
        free(stripped);
        return (0);
    }

    // printf("PARSER DEBUG - Added argument: '%s'\n", stripped);
    free(stripped);
    return (1);
}
