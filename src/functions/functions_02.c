/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:19 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/23 11:51:08 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin(const char *s1, const char *s2)
{
    char *temp;
    size_t len;

    if (!s1 || !s2)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2);
    temp = malloc(sizeof(char) * (len + 1));
    if (!temp)
        return (NULL);
    ft_strlcpy(temp, s1, len + 1);
    ft_strlcpy(temp + ft_strlen(s1), s2, ft_strlen(s2) + 1);
    return (temp);
}

char *ft_strdup(const char *s1)
{
    char *temp;
    size_t len;

    len = ft_strlen(s1);
    temp = malloc(sizeof(char) * (len + 1));
    if (!temp)
        return (NULL);
    ft_strlcpy(temp, s1, len + 1);
    return (temp);
}

char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len = ft_strlen(s);
    if (n < len)
        len = n;
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, s, len + 1);
    return (dup);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    if (n == 0)
        return (0);
    while (s1[i] == s2[i] && s1[i] != '\0')
    {
        if (i < (n - 1))
            i++;
        else
            return (0);
    }
    return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int ft_strchr(char *str, char c)
{
	int x; 

	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			return (1);
		x++;
	}
	return (0);
}
