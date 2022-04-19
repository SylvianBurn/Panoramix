/*
** EPITECH PROJECT, 2022
** pano
** File description:
** main
*/

#include "../include/panoramix.h"

int print_usage()
{
    printf("USAGE:  ./panoramix <nb_villagers> <pot_size> <nb_fights>");
    printf(" <nb_refills>\n");
    return (0);
}

int check_args(char **av)
{
    if (my_getnbr(av[1]) < 0 || my_getnbr(av[2]) < 0 || my_getnbr(av[3]) < 0 ||
    my_getnbr(av[4]) < 0) {
        printf("Values must be >0.\n");
        return (84);
    }
    return (0);
}

int prog(char **av)
{
    data_t *data = malloc(sizeof(data_t));

    data->nb_villagers = my_getnbr(av[1]);
    data->pot_size = my_getnbr(av[2]);
    data->nb_fights = my_getnbr(av[3]);
    data->nb_refills = my_getnbr(av[4]);
    game(data);
    free (data);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (print_usage());
    else if (ac != 5) {
        printf("Wrong number of arguments.\n");
        return (84);
    } else {
        if (check_args(av) == 84)
            return (84);
        else
            return (prog(av));
    }
}