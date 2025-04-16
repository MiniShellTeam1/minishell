/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:23:18 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 13:23:19 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"
# include "lexing/lexer.h"

void print_tokens(t_token_list *tokens);
void print_parsed_commands(t_command *cmd);
void print_master(t_master *master);
void debug_shell_state(t_token_list *tokens, t_command *cmd, t_master *master, const char *stage);

#endif