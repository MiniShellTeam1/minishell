/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 07:34:24 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/14 07:34:24 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static size_t	ft_toklen(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

static char	*gen_substr(char const **s, char c)
{
	const char	*start;
	size_t		len;

	start = *s;
	len = 0;
	while (*start && *start != c)
	{
		start++;
		len++;
	}
	*s = start;
	return (ft_substr(*s - len, 0, len));
}

static int	process_substring(char ***ret, const char **s, char c, size_t *i)
{
	if (**s != c)
	{
		(*ret)[*i] = gen_substr(s, c);
		if (!(*ret)[*i])
		{
			ft_free_split(*ret);
			return (0);
		}
		(*i)++;
	}
	else
		(*s)++;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	ret = ft_calloc((ft_toklen(s, c) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (*s || (!*s && c == '\0'))
	{
		if (!process_substring(&ret, &s, c, &i))
			return (NULL);
		if (c == '\0')
			break ;
	}
	return (ret);
}
