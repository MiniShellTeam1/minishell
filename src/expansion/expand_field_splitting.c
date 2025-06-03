#include "minishell.h"

static int is_ifs_char(char c)
{
    // Default IFS is space, tab, newline
    return (c == ' ' || c == '\t' || c == '\n');
}

static size_t count_fields(const char *str)
{
    size_t count = 0;
    int in_field = 0;
    size_t i = 0;
    
    while (str[i])
    {
        if (is_ifs_char(str[i]))
        {
            in_field = 0;
        }
        else if (!in_field)
        {
            in_field = 1;
            count++;
        }
        i++;
    }
    return (count);
}

static char *extract_field(const char *str, size_t start, size_t end)
{
    char *field;
    size_t len;
    size_t i;
    
    len = end - start;
    field = malloc(len + 1);
    if (!field)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        field[i] = str[start + i];
        i++;
    }
    field[len] = '\0';
    return (field);
}

char **split_fields(const char *str)
{
    char **fields;
    size_t field_count;
    size_t field_index;
    size_t i;
    size_t field_start;
    int in_field;
    
    if (!str)
        return (NULL);
    
    field_count = count_fields(str);
    if (field_count == 0)
        return (NULL);
    
    fields = malloc(sizeof(char *) * (field_count + 1));
    if (!fields)
        return (NULL);
    
    field_index = 0;
    i = 0;
    in_field = 0;
    field_start = 0;
    
    while (str[i])
    {
        if (is_ifs_char(str[i]))
        {
            if (in_field)
            {
                fields[field_index] = extract_field(str, field_start, i);
                if (!fields[field_index])
                {
                    // Free previously allocated fields
                    while (field_index > 0)
                        free(fields[--field_index]);
                    free(fields);
                    return (NULL);
                }
                field_index++;
                in_field = 0;
            }
        }
        else if (!in_field)
        {
            in_field = 1;
            field_start = i;
        }
        i++;
    }
    
    // Handle last field if string doesn't end with IFS
    if (in_field)
    {
        fields[field_index] = extract_field(str, field_start, i);
        if (!fields[field_index])
        {
            while (field_index > 0)
                free(fields[--field_index]);
            free(fields);
            return (NULL);
        }
        field_index++;
    }
    
    fields[field_index] = NULL;
    return (fields);
}

int should_split_field(const char *original_token, size_t var_start)
{
    // Check if the variable is quoted
    return (!is_in_single_quotes(original_token, var_start) && 
            get_quote_state(original_token, var_start) != QUOTE_DOUBLE);
}