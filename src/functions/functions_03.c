/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:47:45 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/05/03 23:55:35 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t i;

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

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t dst_len;
    size_t src_len;
    size_t i;

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

static int	ft_countwords(char *tocount, char seperator)
{
	int	x;
	int	wordcount;

	x = 0;
	wordcount = 0;
	while (tocount[x])
	{
		while (tocount[x] && tocount[x] == seperator)
			x++;
		if (tocount[x] && tocount[x] != seperator)
			wordcount++;
		while (tocount[x] && tocount[x] != seperator)
			x++;
	}
	return (wordcount);
}

/* counts the characters of the specific word */

static int	ft_countchar(char *tocount, char seperator)
{
	int	pos;
	int	wordlen;

	pos = 0;
	wordlen = 0;
	while (tocount[pos] && tocount[pos] == seperator)
		pos++;
	while (tocount[pos] && tocount[pos] != seperator)
	{
		wordlen++;
		pos++;
	}
	return (wordlen);
}

/* frees the given array starting from the specific point given as 'size' */

static void	*ft_freearrsplit(char **tofree, int size)
{
	int	x;

	x = 0;
	while (x < size)
	{
		free(tofree[x]);
		x++;
	}
	free(tofree);
	return (NULL);
}

/* allocates memory for each word and writes the string into it */

static char	**ft_splitstrings(char **splitted, char *tosplit, char seperator,
		int wordcount)
{
	int	x;
	int	y;
	int	z;
	int	charcount;

	x = 0;
	z = 0;
	while (x < wordcount)
	{
		y = 0;
		while (tosplit[z] == seperator)
			z++;
		charcount = ft_countchar(&tosplit[z], seperator);
		splitted[x] = malloc(sizeof(char) * (charcount + 1));
		if (!splitted[x])
			return (ft_freearrsplit(splitted, x));
		while (tosplit[z] && y < charcount)
		{
			splitted[x][y] = tosplit[z++];
			y++;
		}
		splitted[x][y] = 0;
		x++;
	}
	return (splitted);
}

/* splits a string into a string array and returns the array*/

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
