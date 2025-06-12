/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_01b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:30:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:20:15 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

static void	ft_copy_first_string(char *dest, char *src, int *pos)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[*pos] = src[i];
		i++;
		(*pos)++;
	}
}

static void	ft_cpy_rem_str(char *dest, char *str2, char *str3, int *pos)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		dest[*pos] = str2[i];
		i++;
		(*pos)++;
	}
	i = 0;
	while (str3[i])
	{
		dest[*pos] = str3[i];
		i++;
		(*pos)++;
	}
}

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	int		len;
	char	*joinedstr;
	int		pos;

	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	joinedstr = malloc(sizeof(char) * (len + 1));
	if (!joinedstr)
		return (NULL);
	pos = 0;
	ft_copy_first_string(joinedstr, str1, &pos);
	ft_cpy_rem_str(joinedstr, str2, str3, &pos);
	joinedstr[pos] = '\0';
	return (joinedstr);
}
