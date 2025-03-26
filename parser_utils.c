#include "parser_utils.h"

char *strip_quotes(char *token)
{
    size_t  len;
    char    *result;
    size_t  i;

    len = ft_strlen(token);
    if (len < 2 || (token[0] != '"' && token[0] != '\''))
        return (ft_strdup(token));
    result = malloc(len - 1);
    if (!result)
        return (NULL);
    i = 0;
    while (i < len - 2)
    {
        result[i] = token[i + 1];
        i++;
    }
    result[i] = '\0';
    return (result);
}

int is_variable(char *token)
{
    if (!token || token[0] != '$')
        return (0);
    if (token[1] == '?' || (token[1] >= 'A' && token[1] <= 'Z'))
        return (1);
    return (0);
}

int set_redirect(t_command *cmd, char *token, char *next_token)
{
    if (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
    {
        cmd->append = (!ft_strcmp(token, ">>"));
        cmd->redirect_out = ft_strdup(next_token);
        return (!cmd->redirect_out ? 0 : 1);
    }
    if (!ft_strcmp(token, "<"))
    {
        cmd->redirect_in = ft_strdup(next_token);
        return (!cmd->redirect_in ? 0 : 1);
    }
    return (0);
}