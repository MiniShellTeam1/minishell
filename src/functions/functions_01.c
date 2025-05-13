#include "minishell.h"

void ft_putstr_fd(char *str, int fd)
{
    if (str)
        write(fd, str, ft_strlen(str));
}

int ft_strcmp(char *str1, char *str2)
{
	int x;

	x = 0;
	while(str1[x] && str2[x])
	{
		if (str1[x] != str2[x])
			return (1);
		x++;
	}
	if (str1[x] || str2[x])
		return (1);
	return (0);
}

char *ft_itoa(int num)
{
    char *str;
    int temp = num;
    int length = 0;
    int isNegative = 0;
    int x;

    if (num < 0)
    {
        isNegative = 1;
        num *= -1;
    }
    if (num == 0)
        length = 1;
    else
    {
        while (temp != 0)
        {
            temp /= 10;
            length++;
        }
    }
    if (isNegative)
        length++;
    str = malloc(sizeof(char) * (length + 1));
    if (!str)
        return (NULL);
    str[length] = '\0';
    x = length - 1;
    if (num == 0)
        str[x] = '0';
    else
    {
        while (num > 0)
        {
            str[x] = (num % 10) + '0';
            num /= 10;
            x--;
        }
    }
    if (isNegative)
        str[0] = '-';
    return (str);
}

int ft_strlen(const char *str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char *ft_strjoin3(char *str1, char *str2, char *str3)
{
	int len;
	char *joinedstr;
    int x;
    int y;

    x = 0;
    y = 0;
	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	joinedstr = malloc(sizeof(char) * (len + 1));
	if (!joinedstr)
		return (NULL);
    while (str1[x])
    {
        joinedstr[x] = str1[x];
        x++;
    }
    while (str2[y])
    {
        joinedstr[x] = str2[y];
        y++;
        x++;
    }
    y = 0;
    while (str3[y])
    {
        joinedstr[x] = str3[y];
        y++;
        x++;
    }
    joinedstr[x] = 0;
    return (joinedstr);
}