#include "minishell.h"

static char *strip_delimiter_quotes(char *delimiter)
{
    char *result;
    size_t len;
    
    if (!delimiter)
        return (NULL);
        
    len = ft_strlen(delimiter);
    
    // Handle quoted delimiters: 'lim', "lim", lim'' */
    if (len >= 2)
    {
        if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') ||
            (delimiter[0] == '"' && delimiter[len - 1] == '"'))
        {
            // Remove outer quotes 
            result = ft_strndup(delimiter + 1, len - 2);
        }
        else if (len >= 2 && delimiter[len - 1] == '\'' && delimiter[len - 2] == '\'')
        {
            // Handle lim'' case 
            result = ft_strndup(delimiter, len - 2);
        }
        else
        {
            result = ft_strdup(delimiter);
        }
    }
    else
    {
        result = ft_strdup(delimiter);
    }
    
    return (result);
}

static int should_expand_heredoc(char *delimiter)
{
    size_t len;
    
    if (!delimiter)
        return (1);  // Default: expand
        
    len = ft_strlen(delimiter);
    
    // Don't expand if delimiter was quoted
    if (len >= 2)
    {
        if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') ||
            (delimiter[0] == '"' && delimiter[len - 1] == '"') ||
            (len >= 2 && delimiter[len - 1] == '\'' && delimiter[len - 2] == '\''))
        {
            return (0);  // Quoted delimiter - no expansion
        }
    }
    
    return (1);  // Unquoted delimiter - expand variables
}

static char *process_heredoc_line(char *line, t_master *master, int should_expand)
{
    char *result;
    
    if (!line)
        return (NULL);
        
    if (should_expand)
    {
        // Expand variables in the line
        result = expand_word(line, master);
        if (!result)
            return (ft_strdup(line));
    }
    else
    {
        // No expansion - return line as-is
        result = ft_strdup(line);
    }
    
    return (result);
}

static char *concat_heredoc_line(char *current, char *new_line)
{
    char *temp;
    char *result;

    if (!current)
    {
        result = ft_strjoin(new_line, "\n");
        return (result);
    }
    
    temp = ft_strjoin(current, new_line);
    if (!temp)
        return (NULL);
    
    result = ft_strjoin(temp, "\n");
    free(temp);
    
    return (result);
}

void handle_heredoc(t_command *cmd, t_master *master)
{
    char *line;
    char *processed_line;
    char *heredoc_content;
    char *delimiter;
    char *clean_delimiter;
    size_t delim_len;
    int should_expand;
    
    if (!cmd || !cmd->infiles || !cmd->infiles[0])
        return;
    
    // Check if this is a heredoc (starts with <<)
    if (ft_strncmp(cmd->infiles[0], "<<", 2) != 0)
        return;
    
    // Extract delimiter (skip "<<")
    delimiter = cmd->infiles[0] + 2;
    if (!delimiter || !*delimiter)
        return;
    
    // Determine if we should expand variables
    should_expand = should_expand_heredoc(delimiter);
    
    // Strip quotes from delimiter for comparison
    clean_delimiter = strip_delimiter_quotes(delimiter);
    if (!clean_delimiter)
        return;
    
    delim_len = ft_strlen(clean_delimiter);
    heredoc_content = NULL;
    
    // Read heredoc lines until delimiter is found
    while (1)
    {
        write(STDOUT_FILENO, "heredoc> ", 9);
        line = readline("");
        
        if (!line)  // EOF
            break;
        
        // Check if line matches delimiter exactly
        if ((size_t)ft_strlen(line) == delim_len && 
            ft_strncmp(line, clean_delimiter, delim_len) == 0)
        {
            free(line);
            break;
        }
        
        // Process the line (expand variables if needed)
        processed_line = process_heredoc_line(line, master, should_expand);
        if (!processed_line)
        {
            free(line);
            if (heredoc_content)
                free(heredoc_content);
            free(clean_delimiter);
            return;
        }
        
        // Add line to heredoc content
        char *new_content = concat_heredoc_line(heredoc_content, processed_line);
        if (heredoc_content)
            free(heredoc_content);
        heredoc_content = new_content;
        
        free(line);
        free(processed_line);
    }
    
    free(clean_delimiter);
    
    // Store heredoc content in command
    if (cmd->heredoc_input)
        free(cmd->heredoc_input);
    cmd->heredoc_input = heredoc_content;
    cmd->is_heredoc = 1;
}