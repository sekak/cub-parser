#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct p_parser
{
    char **map;
    char *no;
    char *so;
    char *we;
    char *c;
    char *f;
    char *ea;
    int error;
} t_parser;

int checked_file(char *ac)
{
    int fd = open(ac, O_RDONLY);
    if (fd == -1)
        return (0);
    return (fd);
}

void take_path(t_parser *parser, int i, char *str, int j)
{
    j += 2;
    while (str[j] == ' ')
        j++;
    if (checked_file(str + j) != 0)
        parser->error = 0;
    else
    {
        if (i == 1)
            strcpy(parser->no, str + j);
        else if (i == 2)
            strcpy(parser->so, str + j);
        else if (i == 3)
            strcpy(parser->we, str + j);
        else if (i == 4)
            strcpy(parser->ea, str + j);
    }
    while (str[j] && str[j] != ' ')
        j++;
    while (str[j] && str[j] == ' ')
        j++;
    if (str[j] && str[j] != ' ' && str[j] != '\0' && str[j] != '\n')
        parser->error = 0;
}

int check_character(char c, t_parser *parser)
{
    (void)parser;
    if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
    {
        printf("%c", c);
        return (0);
    }
    else
        parser->error = 0;

    return (1);
}

int check_color(t_parser *parser, char *str, int i)
{
    i++;
    // int j = 0;
    int comma = 0;
    while (str[i] && parser->error)
    {
        while (str[i] == ' ')
            i++;
        if (!((str[i] <= '9' && str[i] >= '0') || str[i] == ',' || str[i] == '\n' || str[i] == ' '))
        {
            parser->error = 0;
            printf("hana");
        }
        if (str[i] == ',')
        {
            comma++;
        }
        if (comma > 2)
        {
            parser->error = 0;
        }
        i++;
    }
    return (1);
}

char *line_by_line(char **ac, t_parser *parser)
{
    int i;
    int j;
    int fd;
    char *str;
    i = 0;
    j = 0;
    fd = checked_file(ac[1]);
    str = malloc(1024 * 1024);
    int t;

    while (i < 4)
    {
        str = get_next_line(fd);
        t = 0;
        while (str[t] == ' ')
        {
            // printf("1");
            t++;
        }

        while (str[t] == '\n' || str[0] == '\n')
        {
            // printf("2\n");
            str = get_next_line(fd);
            while (str[t] == ' ')
            {
                // printf("1");
                t++;
            }
        }

        j = 0;
        while (str[j] == ' ')
            j++;
        if (str[j] == 'N' && str[j + 1] == 'O')
            take_path(parser, 1, str, j);
        else if (str[j] == 'S' && str[j + 1] == 'O')
            take_path(parser, 2, str, j);
        else if (str[j] == 'W' && str[j + 1] == 'E')
            take_path(parser, 3, str, j);
        else if (str[j] == 'E' && str[j + 1] == 'A')
            take_path(parser, 4, str, j);
        else
            parser->error = 0;
        i++;
    }
    i = 0;
    while (i < 2)
    {
        str = get_next_line(fd);
        t = 0;
        while (str[t] == ' ')
        {
            printf("1");
            t++;
        }

        while (str[t] == '\n' || str[0] == '\n')
        {
            // printf("2\n");
            str = get_next_line(fd);
            while (str[t] == ' ')
            {
                printf("1");
                t++;
            }
        }
        j = 0;
        while (str[j] == ' ')
            j++;
        // printf("dddd");
        if (str[j] == 'F' && str[j + 1] == ' ')
        {
            check_color(parser, str, j);
        }
        else if (str[j] == 'C' && str[j + 1] == ' ')
            check_color(parser, str, i);
        else
            parser->error = 0;
        i++;
    }

    return (str);
}

int textures(t_parser *parser, char **ac)
{
    parser->no = malloc(1024 * 1024);
    parser->so = malloc(1024 * 1024);
    parser->we = malloc(1024 * 1024);
    parser->ea = malloc(1024 * 1024);
    parser->f = malloc(1024 * 1024);
    parser->c = malloc(1024 * 1024);
    if (parser->no == NULL || parser->ea == NULL || parser->we == NULL || parser->so == NULL)
        return (0);
    if (checked_file(ac[1]) == 0)
        return (0);
    return (1);
}

int alloc(char **ac)
{
    t_parser parser;

    parser.error = 1;
    textures(&parser, ac);
    line_by_line(ac, &parser);
    if (parser.error == 0)
        return (0);

    printf("%s\n", parser.no);
    printf("%s\n", parser.so);
    printf("%s\n", parser.we);
    printf("%s\n", parser.ea);
    // printf("%s\n", parser.f);
    // printf("%s\n", parser.c);
    return (1);
}

int main(int av, char **ac)
{
    (void)ac;
    if (av == 2)
    {
        if (alloc(ac) == 0)
        {
            printf("eroor");
            return 0;
        }
    }
    else
        printf("argument invalide.");
    return (0);
}