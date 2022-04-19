/*
** EPITECH PROJECT, 2022
** pano
** File description:
** utils
*/

#include "../include/panoramix.h"

int my_getnbr(char const *str)
{
    int i = 0;
    long nbr = 0;
    int sign = 1;

    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            sign *= -1;
        }
        i += 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        nbr = nbr * 10 + str[i] - 48;
        i += 1;
    }
    nbr *= sign;
    if (nbr < -2147483648 || nbr > 2147483647)
        return (0);
    return ((int)nbr);
}

void print_data(data_t *data)
{
    printf("nb_vil =: %d\npot_sz: %d\nnb_fights: %d\nnb_refills: %d\n",
    data->nb_villagers, data->pot_size, data->nb_fights, data->nb_refills);
}