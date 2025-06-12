/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:05:58 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	advance_input(t_lexer_data *data)
{
	if (!data || !data->input || !*(data->input))
		return (0);
	(*(data->input))++;
	return (1);
}

char	get_current_char(t_lexer_data *data)
{
	if (!data || !data->input || !*(data->input))
		return ('\0');
	return (**(data->input));
}

int	lexer_error(const char *message)
{
	if (message)
		ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
