/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:23:29 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 13:23:30 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_command {
    char            *cmdpath;
    char            **args;
    char            **infiles;
    char            **outfiles;
    char            *errormsg;
    int             append;
    char            *heredoc_input;
    struct s_command *next;
} t_command;

typedef struct s_env {
    // placeholder for nico
} s_env;

typedef struct s_master {
    struct s_command *cmds;
    struct s_env     *env;
    unsigned char    errorcode;
} t_master;

#endif