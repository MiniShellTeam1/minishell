#include "executor.h"

void ft_putstr_fd(char *str, int fd)
{
    int x;

    x = 0;
    while (str[x])
    {
        write(fd, &str[x], 1);
        x++;
    }
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

int ft_strlen(char *str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char *ft_strjoin3(char *str1, char *str2, char *st3)
{
	int len;
	char *joinedstr;

	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str2);
	joinedstr = malloc(sizeof(char) * (len + 1));
	if (!joinedstr)
		return (NULL);
	return (NULL);
}

int ft_strncmp(char *str1, char *str2, int n)
{
	int x;

	x = 0;
	while(str1[x] && str2[x] && x < n)
	{
		if (str1[x] != str2[x])
			return (1);
		x++;
	}
	return (0);
}

int ft_strchr(char *str, char c)
{
	int x; 

	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			return (1);
		x++;
	}
	return (0);
}
