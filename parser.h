#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "./libft/libft.h"

typedef struct p_color
{
    int cr;
    int cg;
    int cb;
} c_color;

typedef struct t_color
{
    int fr;
    int fg;
    int fb;
} f_folor;

typedef struct p_parser
{
    t_list  *list;
    char **map;
    char *no;
    char *so;
    char *we;
    char *ea;
    int error;
    c_color ccolor;
    f_folor fcolor;
    int len_map;
    char player;
} t_parser;



int map(t_parser *parser, int fd);
int check_file(char *str);
#endif