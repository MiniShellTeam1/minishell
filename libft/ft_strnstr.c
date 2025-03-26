/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:48:46 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/14 15:15:47 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_temp;
	char	*little_temp;
	size_t	i;

	if (!ft_strlen(little))
		return ((char *)big);
	if (!ft_strlen(big) || len < ft_strlen(little))
		return (0);
	i = len - ft_strlen(little) + 1;
	while (i-- && *big)
	{
		big_temp = (char *)big;
		little_temp = (char *)little;
		while (*little_temp && *little_temp == *big_temp)
		{
			++big_temp;
			++little_temp;
		}
		if (!*little_temp)
			return ((char *)big);
		++big;
	}
	return (0);
}
