/*
** EPITECH PROJECT, 2022
** pano
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <semaphore.h>
    #include <pthread.h>

    typedef struct s_info {
        int nb_villagers;
        int pot_size;
        int pot;
        int nb_fights;
        int nb_refills;
        sem_t *refill_done;
        sem_t *needs_refill;
        pthread_mutex_t *drinking;
    } info_t;

    typedef struct s_data {
        int nb_villagers;
        int pot_size;
        int nb_fights;
        int nb_refills;
    } data_t;

    typedef struct s_game {
        int id;
        int nb_fights;
        info_t *info;
    } game_t;

    int my_getnbr(char const *);
    int game(data_t *);
    int free_and_destroy(data_t *, game_t **, info_t *);
#endif /* !PANORAMIX_H_ */
