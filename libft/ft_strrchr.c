/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:19:49 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/16 15:03:20 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = 0;
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			temp = (char *)s;
		++s;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (temp);
}

// int main()
// {
// 	printf("%s", ft_strrchr("teste", 1024));
// }