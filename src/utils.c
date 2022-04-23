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

void my_freeer(info_t *info, data_t *data, game_t **infos)
{
    free(info);
    for (int i = 0; i < (data->nb_villagers + 1); i++)
        free(infos[i]);
    free(infos);
}

int free_and_destroy(data_t *data, game_t **infos, info_t *info)
{
    int ret = 0;

    if (pthread_mutex_destroy(info->drinking) != 0) {
        write(2, "Failed to destroy mutex.\n", 25);
        ret++;
    }
    if (sem_destroy(info->needs_refill) == -1) {
        write(2, "Failed to destroy semaphore.\n", 29);
        ret++;
    }
    if (sem_destroy(info->refill_done) == -1) {
        write(2, "Failed to destroy semaphore.\n", 29);
        ret++;
    }
    my_freeer(info, data, infos);
    if (ret != 0)
        ret = 84;
    else
        ret = 0;
    return (ret);
}
