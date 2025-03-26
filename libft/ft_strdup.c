/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:10:37 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/14 15:15:27 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(s1);
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, s1, len + 1);
	return (temp);
}
