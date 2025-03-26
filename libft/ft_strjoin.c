/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:41:18 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/14 15:15:30 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, s1, len +1);
	ft_strlcat(temp, s2, len +1);
	return (temp);
}
