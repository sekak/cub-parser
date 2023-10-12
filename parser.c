#include "parser.h"

//check character

int checked_file(char *ac)
{
    int fd = open(ac, O_RDONLY);
    if (fd == -1)
        return (0);
    return (fd);
}

void part_of_take_path(t_parser *parser, char *str, int i, int j)
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

void take_path(t_parser *parser, int i, char *str, int j)
{
    j += 2;
    while (str[j] == ' ')
        j++;
    if (checked_file(str + j) != 0)
        parser->error = 0;
    else
        part_of_take_path(parser, str, i, j);
    while (str[j] && str[j] != ' ')
        j++;
    while (str[j] && str[j] == ' ')
        j++;
    if (str[j] && str[j] != ' ' && str[j] != '\0' 
        && str[j] != '\n')
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
        rev[j] = str[i];
        j++;
        i--;
    }
    return (rev);
}

void take_colors(t_parser *parser, char *str, int i, char c)
{
    // i++;
    (void)parser;
    int trr = 0;
    int res = 0;
    // while (str[i] == ' ' && str[i])
    //     i++;
    while (str[i])
    {
        while (str[i] == ' ' && str[i])
            i++;
        if (str[i] == ',' || str[i] == '\n')
        {
            if (res > 255 || res < 0)
                parser->error = 0;
            if (c == 'f' && trr == 0)
            {
                parser->fcolor.fr = res;
                trr++;
            }
            else if (c == 'f' && trr == 1)
            {
                parser->fcolor.fg = res;
                trr++;
            }
            else if (c == 'f' && trr == 2)
            {
                parser->fcolor.fb = res;
                trr++;
            }
            if (c == 'c' && trr == 0)
            {
                parser->ccolor.cr = res;
                trr++;
            }
            else if (c == 'c' && trr == 1)
            {
                parser->ccolor.cg = res;
                trr++;
            }
            else if (c == 'c' && trr == 2)
            {
                parser->ccolor.cb = res;
                trr++;
            }
            res = 0;
            if (str[i] == ',')
                i++;
        }
        if (str[i] <= '9' && str[i] >= '0')
            res = (res * 10) + str[i] - '0';
        i++;
    }
}

int check_color(t_parser *parser, char *str, int i, char c)
{
    i++;
    int j = i;
    int comma = 0;
    while (str[i] && parser->error)
    {
        while (str[i] == ' ')
            i++;
        if (!((str[i] <= '9' && str[i] >= '0') || str[i] == ',' || str[i] == '\n' || str[i] == ' '))
        {
            parser->error = 0;
            // printf("hana");
        }
        if (str[i] == ',')
            comma++;
        i++;
    }
    if (comma > 2)
        parser->error = 0;
    take_colors(parser, str, j, c);
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
        // printf("dddd");
        if (str[j] == 'F' && str[j + 1] == ' ')
        {
            check_color(parser, str, j, 'f');
        }
        else if (str[j] == 'C' && str[j + 1] == ' ')
            check_color(parser, str, i, 'c');
        else
            parser->error = 0;
        i++;
    }

    if (map(parser, fd) == 0)
        return (0);

    return (str);
}

int textures(t_parser *parser, char **ac)
{
    // parser = malloc(sizeof(t_parser));
    parser->no = malloc(1024 * 1024);
    parser->so = malloc(1024 * 1024);
    parser->we = malloc(1024 * 1024);
    parser->ea = malloc(1024 * 1024);
    parser->map = malloc(1024 * 1024);

    if (parser->no == NULL || parser->ea == NULL || parser->we == NULL || parser->so == NULL)
        return (0);
    if (checked_file(ac[1]) == 0)
        return (0);
    return (1);
}


void free_map(t_parser *parser)
{
    int i = 0;
    while(parser->len_map >= i)
    {
        free(parser->map[i]);
        i++;
    }
    free(parser->we);
    free(parser->ea);
    free(parser->so);
    free(parser->no);
 }
int alloc(char **ac)
{
    t_parser parser;

    parser.error = 1;
    parser.len_map = 0;
    parser.list = NULL;
    textures(&parser, ac);
    line_by_line(ac, &parser);
    if (parser.error == 0)
        return (0);

    printf("%s\n", parser.no);
    printf("%s\n", parser.so);
    printf("%s\n", parser.we);
    printf("%s\n", parser.ea);
    printf("%d\n", parser.ccolor.cr);
    printf("%d\n", parser.ccolor.cg);
    printf("%d\n", parser.ccolor.cb);
    printf("%d\n", parser.fcolor.fr);
    printf("%d\n", parser.fcolor.fg);
    printf("%d\n", parser.fcolor.fb);
    // int i = 0;
    // // printf("%d",parser.len_map);
    // while (parser.map[i])
    // {
    //     printf("%s\n", parser.map[i]);
    //     i++;
    // }
    // printf("%d\n",i);
    //  free_map(&parser);
    return (1);
}

int check_file(char *str)
{
    int fd;

    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

int check_extension(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' &&
            str[i + 3] == 'b' && str[i + 4] == '\0')
            return (0);
        i++;
    }
    return (1);
}


int main(int av, char **ac)
{
    (void)ac;
    
    if (av == 2)
    {
        if (check_extension(ac[1]) == 1)
        {
            printf("Error\n");
            return (0);
        }
        if (check_file(ac[1]) == 0)
        {
            printf("Error\n");
            return (0);
        }
        if (alloc(ac) == 0)
        {
            printf("Error");
            return 0;
        }
    }
    else
        printf("argument invalide.");
    // pause();
    return (0);
}
 