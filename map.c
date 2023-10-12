#include "parser.h"

// void check_side_map(t_parser *parser)
// {
//     int i;
//     int j;
//     int x;

//     i = 0;
//      while (parser->len_map >= i)
//     {
//         j = 0;
//          x = 0;
//         while (parser->map[i][j] == ' ')
//             j++;
//         if (parser->map[i][j] == '0')
//             parser->Error = 0;
//         while(parser->map[i][j] != ' ' && parser->map[i][j] != '\n')
//             j++;
//         j--;

//         printf("%c||\n",parser->map[i][j]);
//         printf("%c", parser->map[i][j]);
//         i++;
//     }
// }

// void check_wall(t_parser *parser)
// {
//     // int i=0;
//     int j;
//     j = 0;
//     while (parser->map[0][j])
//     {
//         if (parser->map[0][j] != '1' && parser->map[0][j] != '\n' && parser->map[0][j] != ' ')
//             parser->Error = 0;
//         j++;
//     }
//     j = 0;
//     while (parser->map[parser->len_map][j])
//     {
//         if (parser->map[parser->len_map][j] != '1' && parser->map[parser->len_map][j] != '\n' && parser->map[parser->len_map][j] != ' ')
//             parser->Error = 0;
//         j++;
//     }
//     check_side_map(parser);
// }

// int check_map(t_parser *parser)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;

//     // check_wall(parser);
//     while (parser->len_map >= i)
//     {
//         j = 0;
//         while (parser->map[i][j])
//         {
//             if (parser->map[i][j] != '\n' && parser->map[i][j] != 'N' && parser->map[i][j] != 'S' && parser->map[i][j] != 'W' && parser->map[i][j] != 'E' && parser->map[i][j] != '1' && parser->map[i][j] != '0' && parser->map[i][j] != ' ')
//             {
//                 parser->Error = 0;
//                 return (0);
//             }
//             // else
//             printf("%c", parser->map[i][j]);
//             j++;
//         }
//         i++;
//     }
//     return (1);
// }

void check_map(t_parser *parser)
{
    int i = 0;
    int j = 0;

    while (parser->len_map >= i)
    {
        j = 0;
        while (parser->map[i][j])
        {
            if (parser->map[i][j] == '0')
            {

                if (parser->map[i][j + 1] == ' ' || parser->map[i][j + 1] == '\n' || parser->map[i][j + 1] == '\0' || parser->map[i][j - 1] == ' ' || parser->len_map == i || i == 0)
                    parser->error = 0;
            }
            j++;
        }
        i++;
    }
}

int check_newline_space(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\0')
            printf("hanahanahan");
        i++;
    }
    // if (str[0] == '\n' || str[0] == '\0')
    //     return (0);
    // while (str[i] == ' ' && str[i])
    //     i++;
    // if (str[i] != '1' && str[i] != '0')
    //     return (0);

    return (1);
}

int store_map(t_parser *parser, char *str)
{
    int len = 0;
    static int i = 0;

    while (str[len])
        len++;

    if (!(parser->map[i] = malloc(sizeof(char *) * (len + 1))))
        return (0);
    strcpy(parser->map[i], str);
    i++;

    return (1);
}

int map(t_parser *parser, int fd)
{
    int i = 0;
    char *str = malloc(1024 * 1024);
    str = get_next_line(fd);
    (void)parser;
    while (1)
    {
        while (str[i] == ' ')
            i++;
        if (str[i] == '1' || str[i] == '0')
            break;
        else
        {
            str = get_next_line(fd);
            i = -1;
        }
        i++;
    }
    // printf("%s\n",str);
    while(strchr(str, '1'))
    {
        ft_lstadd_back(&parser->list, ft_lstnew(str));
        str = get_next_line(fd);
        if (!str)
            break ;
    }

    return (1);
}
