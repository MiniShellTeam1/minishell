/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:47:45 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/23 11:30:12 by mhuthmay         ###   ########.fr       */
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
