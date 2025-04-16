/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:59 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 13:23:00 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include "../lexing/lexer.h"

t_command   *parser(t_token_list *tokens);
t_command   *init_command(void);
void        free_command(t_command *cmd);
int         add_arg(t_command *cmd, char *arg);
int         process_token(t_command **cmd, char *token, int *pipe_flag);
int         set_redirect(t_command *cmd, char *token, char *next_token);

#endif