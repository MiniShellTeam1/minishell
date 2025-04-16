/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:50 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 14:38:34 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

#include "parser.h"

char *strip_quotes(char *token);
int is_variable(char *token);
char *expand_variable(char *token);
int set_redirect(t_command *cmd, char *token, char *next_token);

#endif