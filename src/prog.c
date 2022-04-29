/*
** EPITECH PROJECT, 2022
** pano
** File description:
** prog
*/

#include "../include/panoramix.h"

void villagers(game_t *data)
{
    printf("Villager %d: Going to battle !\n", data->id);
    while (data->nb_fights > 0) {
        pthread_mutex_lock(data->info->drinking);
        printf("Villager %d: I need a drink... \
I see %d servings left.\n", data->id, data->info->pot);
        if (data->info->pot <= 0) {
            printf("Villager %d: Hey Pano wake up! \
We need more potion.\n", data->id);
            sem_post(data->info->needs_refill);
            sem_wait(data->info->refill_done);
        }
        if (data->info->pot > 0) {
            data->info->pot--;
        }
        pthread_mutex_unlock(data->info->drinking);
        data->nb_fights--;
        printf("Villager %d: Take that roman scum! \
Only %d left.\n", data->id, data->nb_fights);
    }
    printf("Villager %d: I'm going to sleep now.\n", data->id);
}

void druid(game_t *data)
{
    printf("Druid: I'm ready... but sleepy...\n");
    while (data->info->nb_refills > 0) {
        sem_wait(data->info->needs_refill);
        data->info->pot = data->info->pot_size;
        data->info->nb_refills--;
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can \
can only make %d more refills after this one.\n", data->info->nb_refills);
        sem_post(data->info->refill_done);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
}

info_t *init_info(data_t *data, pthread_mutex_t *mtx, sem_t *a, sem_t *b)
{
    info_t *info = malloc(sizeof(info_t));

    info->nb_villagers = data->nb_villagers;
    info->pot_size = data->pot_size;
    info->pot = data->pot_size;
    info->nb_fights = data->nb_fights;
    info->nb_refills = data->nb_refills;
    info->refill_done = a;
    info->needs_refill = b;
    info->drinking = mtx;
    return (info);
}

game_t **inits(game_t **infos, data_t *data, info_t *info, pthread_t *threads)
{
    infos[0] = malloc(sizeof(data_t));
    infos[0]->info = info;
    infos[0]->id = 0;
    infos[0]->nb_fights = data->nb_fights;
    pthread_create(&threads[0], NULL, (void *)druid, (void *)infos[0]);
    for (int i = 1; i < (data->nb_villagers + 1); i++) {
        infos[i] = malloc(sizeof(data_t));
        infos[i]->info = info;
        infos[i]->nb_fights = data->nb_fights;
        infos[i]->id = i;
    }
    return (infos);
}

int game(data_t *data)
{
    game_t **infos = malloc(sizeof(game_t *) * (data->nb_villagers + 1));
    info_t *info;
    pthread_t* threads = malloc((data->nb_villagers + 1) * sizeof(pthread_t));
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    sem_t *needs_refill = malloc(sizeof(sem_t));
    sem_t *refill_done = malloc(sizeof(sem_t));

    pthread_mutex_init(mtx, NULL);
    sem_init(needs_refill, 0, 0);
    sem_init(refill_done, 0, 0);
    info = init_info(data, mtx, refill_done, needs_refill);
    infos = inits(infos, data, info, threads);
    for (int i = 1; i < (data->nb_villagers + 1); i++)
        pthread_create(&threads[i], NULL, (void *)villagers, (void *)infos[i]);
    for (int i = 0; i < (data->nb_villagers + 1); i++)
        pthread_join(threads[i], NULL);
    return (free_and_destroy(data, infos, info));
}