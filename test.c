#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *inttostr(int res)
{
    char *str = malloc(1024 + 1024);
    char *rev = malloc(1024 + 1024);

    int i = 0;
    int j = 0;

    while (res > 0)
    {
        str[i] = res % 10 + '0';
        i++;
        res /= 10;
    }
    i--;
    while (str[i])
    {
         rev[j]=str[i];
        j++;
        i--;
    }
    return(rev);
}

int main()
{
    printf("%s",inttostr(123));
}