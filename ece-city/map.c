/*----------------------------------------------------------------
 * map.c -- Implémentation de la carte de jeu
 *----------------------------------------------------------------
 */
#include <stdio.h>
#include <allegro.h>
#include "render.h"
#include "assets.h"
#include "simulationvars.h"

//initialisation de la carte
void map_init(struct Game *game){
    int w = CASE_X * GRID_NB_X + 1;
    int h = CASE_Y * GRID_NB_Y + 1;

    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++) {

            //game->world.level0[i][j] = EMPTY;
            //game->world.level_1[i][j] = EMPTY;
            //game->world.level_2[i][j] = EMPTY;

            //game->world.level0[i][j].type = EMPTY;
            //game->world.level_1[i][j].type = EMPTY;
            //game->world.level_2[i][j].type = EMPTY;
        }
    }
}

//mise  a jour de la carte
void map_update(struct Game *game){
    //renderGrid(level0);

    //blit(level0, current, 0, 0, 0, 0, screen->w, screen->h);
}