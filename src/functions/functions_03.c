/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:47:45 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 16:34:16 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_overflow(long result, int digit, int sign, int *overflow)
{
	if (sign == 1)
	{
		if (result > (LONG_MAX - digit) / 10)
		{
			*overflow = 1;
			return (0);
		}
	}
	else
	{
		if (result > (-(LONG_MIN + digit)) / 10)
		{
			*overflow = 1;
			return (0);
		}
	}
	return (1);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

long	ft_atol(char *str, int *overflow)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	*overflow = 0;
	while ((*str >= '\a' && *str <= '\n') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (!ft_check_overflow(result, digit, sign, overflow))
			return (0);
		result = result * 10 + digit;
		str++;
	}
	return (sign * result);
}


char	**ft_split(char *tosplit, char seperator)
{
	char	**splitted;
	int		wordcount;

	if (!tosplit)
		return (NULL);
	wordcount = ft_countwords(tosplit, seperator);
	splitted = malloc(sizeof(char *) * (wordcount + 1));
	if (!splitted)
		return (NULL);
	splitted[wordcount] = NULL;
	splitted = ft_splitstrings(splitted, tosplit, seperator, wordcount);
	if (!splitted)
		return (NULL);
	return (splitted);
}
