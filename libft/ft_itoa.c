/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 07:34:16 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/14 07:34:16 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_digits(int n, int base)
{
	int	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n && ++count)
		n /= base;
	return (count);
}

static void	ft_itoa_helper(int n, char *ret, int len)
{
	static const char	digits[] = "0123456789";

	if (n < 0)
	{
		ret[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		ret[--len] = digits[n % 10];
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ret;

	len = ft_count_digits(n, 10);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (n == 0)
		ret[0] = '0';
	else if (n == -2147483648)
		ft_strlcpy(ret, "-2147483648", len + 1);
	else
		ft_itoa_helper(n, ret, len);
	return (ret);
}
