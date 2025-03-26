/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:37:05 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/16 17:02:43 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*temp;
	size_t	total_size;

	if (size != 0 && nmemb > (SIZE_MAX) / size)
		return (NULL);
	total_size = nmemb * size;
	temp = malloc(total_size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, total_size);
	return (temp);
}
