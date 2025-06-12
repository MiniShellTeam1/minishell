/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:48:52 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/06/12 11:21:07 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

int	ft_strcmp(char *str1, char *str2)
{
	int	x;

	x = 0;
	while (str1[x] && str2[x])
	{
		if (str1[x] != str2[x])
			return (1);
		x++;
	}
	if (str1[x] || str2[x])
		return (1);
	return (0);
}

static int	ft_get_num_length(int num, int *is_negative)
{
	int	temp;
	int	length;

	temp = num;
	length = 0;
	*is_negative = 0;
	if (num < 0)
	{
		*is_negative = 1;
		temp = -temp;
	}
	if (temp == 0)
		length = 1;
	else
	{
		while (temp != 0)
		{
			temp /= 10;
			length++;
		}
	}
	if (*is_negative)
		length++;
	return (length);
}

static void	ft_fill_nmb_str(char *str, int num, int length, int is_negative)
{
	int	x;

	x = length - 1;
	if (num == 0)
		str[x] = '0';
	else
	{
		while (num > 0)
		{
			str[x] = (num % 10) + '0';
			num /= 10;
			x--;
		}
	}
	if (is_negative)
		str[0] = '-';
}

char	*ft_itoa(int num)
{
	char	*str;
	int		length;
	int		is_negative;
	int		original_num;

	original_num = num;
	if (num < 0)
		num = -num;
	length = ft_get_num_length(original_num, &is_negative);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	str[length] = '\0';
	ft_fill_nmb_str(str, num, length, is_negative);
	return (str);
}
