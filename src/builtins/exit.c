#include "minishell.h"
#include "errormsg.h"

void ft_exit(t_command cmd)
{
    unsigned char errorcode; //! diese variable in einer struct speichern und dort setzen

    if (!cmd.args[1])
        errorcode = 0;
    else
        errorcode = (unsigned char)atoi(cmd.args[1]); //!mit ft_atoi ersetzen aus libft
    ft_putstr_fd("exit\n", 1);
    if (cmd.args[2])
    {
        ft_printerror(cmd.args[0], NULL, TOO_MANY_ARGUMENTS);
        errno = 1;
        return ;
    }
    //!Overflow check hinzufügen
    //! if (overflow true)
    //! errno = 2;
    //! return ;
    exit(errorcode);
}

int main()
{
    /* t_command test;
    char *args3[] = {"exit", "-222", "", NULL};
    test.args = args3;
    ft_exit(test);
    return (errno); */
    return -1;
}