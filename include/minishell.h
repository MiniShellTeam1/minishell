/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:23:29 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/04/16 14:55:43 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "functions.h"
# include "parser.h"

typedef struct s_env {
    char            *key;
    char            *value;
    struct s_env    *prev;
    struct s_env    *next;
} t_env;

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

typedef struct s_master {
    struct s_command *cmds;
    struct s_env     *env;
    unsigned char    errorcode;
} t_master;

// Lexer and Parser
typedef enum {
    NORMAL,
    IN_SINGLE_QUOTE,
    IN_DOUBLE_QUOTE,
    IN_WORD,
    IN_OPERATOR
} t_state;

typedef struct {
    char    **tokens;
    size_t  count;
    size_t  capacity;
} t_token_list;

t_token_list    *lexer(const char *input);
t_token_list    *init_token_list(void);
int             add_token(t_token_list *tokens, char *buffer);
void            free_token_list(t_token_list *tokens);
int             process_char(t_state *state, const char **input, t_token_list *tokens, char *buffer, size_t *buf_pos);

t_command       *parser(t_token_list *tokens);
t_command       *init_command(void);
void            free_command(t_command *cmd);
int             add_arg(t_command *cmd, char *arg);
int             process_token(t_command **cmd, char *token, int *pipe_flag);
int             set_redirect(t_command *cmd, char *token, char *next_token);

char            *strip_quotes(char *token);
int             is_variable(char *token);
char            *expand_variable(char *token);

// Executor
void            executor(t_master *master);

// Built-ins
int             ft_cd(t_master *master);
void            ft_echo(t_command cmd);
void            ft_env(t_master master);
void            ft_exit(t_command cmd);
void            ft_export(t_master *master);
int             ft_pwd(void);
void            ft_unset(t_master *master);

// Environment
t_env           *ft_createenvlist(char **envp);
void            ft_addvar(t_env **env, char *key, char *value);
void            ft_delvar(t_env **env, char *key);
char            *ft_getkey(char *var);
char            *ft_getvalue(char *var);
void            ft_freevar(t_env *var);
char            *ft_addlvl(char *stringlvl);

// Error Handling
void            ft_printerror(char *cmd, char *errfile, char *errormsg);

// Debug
void            print_tokens(t_token_list *tokens);
void            print_parsed_commands(t_command *cmd);
void            print_master(t_master *master);
void            debug_shell_state(t_token_list *tokens, t_command *cmd, t_master *master, const char *stage);


#endif