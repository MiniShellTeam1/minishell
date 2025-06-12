/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:00:00 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:09:29 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countwords(char *tocount, char seperator)
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

static char	*ft_allocate_and_fill(char *tosplit, int *z, char seperator)
{
	char	*word;
	int		charcount;
	int		y;

	while (tosplit[*z] == seperator)
		(*z)++;
	charcount = ft_countchar(&tosplit[*z], seperator);
	word = malloc(sizeof(char) * (charcount + 1));
	if (!word)
		return (NULL);
	y = 0;
	while (tosplit[*z] && y < charcount)
	{
		word[y] = tosplit[(*z)++];
		y++;
	}
	word[y] = '\0';
	return (word);
}

char	**ft_splitstrings(char **splitted, char *tosplit, char seperator,
		int wordcount)
{
	int		x;
	int		z;

	x = 0;
	z = 0;
	while (x < wordcount)
	{
		splitted[x] = ft_allocate_and_fill(tosplit, &z, seperator);
		if (!splitted[x])
			return (ft_freearrsplit(splitted, x));
		x++;
	}
	return (splitted);
}
