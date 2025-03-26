/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:16:34 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/16 08:07:41 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	c;
	size_t	i;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	c = ft_strlen(dst);
	i = 0;
	while (src[i] && c + 1 < size)
	{
		dst[c] = src[i];
		c++;
		i++;
	}
	dst[c] = 0;
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
