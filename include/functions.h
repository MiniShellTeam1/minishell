/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:53:54 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 14:54:34 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <stdlib.h>
# include <unistd.h>

void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(char *str1, char *str2);
char	*ft_itoa(int num);
int		ft_strlen(char *str);
char	*ft_strjoin3(char *str1, char *str2, char *st3);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif