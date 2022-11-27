#include <allegro.h>
#include <stdio.h>
#include "ecegame.h"
#include "render.h"
#include "input.h"
#include "simulationvars.h"
#include "simulation.h"
#include "building.h"

/* gameEndFlag:
 * Indicateur de fin de jeu
 */
int gameEndFlag = 0;
int debugFlag = 0;
static struct Game game;

//Compteur de secondes pour le temps de jeu
volatile int counter = 0;
void game_timer_callback()
{
    counter++;
}



void loadFile(struct Game *game){
    FILE *fp = fopen("../paris.txt", "r");
    char ch;
    if (fp == NULL)
    {
        allegro_message("pb fichier font inexistant");
        allegro_exit();
        exit(EXIT_FAILURE);

    }
    char loadedMap[45][35];
    for(int i = 0;i<35;i++){
        for(int j = 0;j<45;j++){
            ch=fgetc(fp);
            if(ch == '\n'){
                ch=fgetc(fp);
            }
            loadedMap[j][i] = ch;
        }
    }
    int visited[GRID_NB_X][GRID_NB_Y];
    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++)
        {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++)
        {
            if(loadedMap[i][j] == 'r'){
                ajouterBuilding(game, i, j, ROAD);
                visited[i][j] = 1;
            }else if(loadedMap[i][j] == 'h'){
                if(visited[i][j] == 0){
                    ajouterBuilding(game, i, j, HOUSE);
                    visited[i][j] = 1;
                }
                for(int k = 0;k<3;k++){
                    for(int d = 0;d<3;d++) {
                        visited[i + k][j + d] = 1;
                    }
                }
            }else if(loadedMap[i][j] == 'w'){
                if(visited[i][j] == 0){
                    ajouterBuilding(game, i, j, WATER_TOWER);
                    visited[i][j] = 1;
                }
                for(int k = 0;k<4;k++){
                    for(int d = 0;d<6;d++) {
                        visited[i + k][j + d] = 1;
                    }
                }
            }else if(loadedMap[i][j] == 'e'){
                if(visited[i][j] == 0){
                    ajouterBuilding(game, i, j, POWER_STATION);
                    visited[i][j] = 1;
                }
                for(int k = 0;k<4;k++){
                    for(int d = 0;d<6;d++) {
                        visited[i + k][j + d] = 1;
                    }
                }
            }
        }
    }
    fclose(fp);
}
END_OF_FUNCTION (game_timer_callback);
LOCK_FUNCTION (game_timer_callback);
LOCK_VARIABLE (counter);
/* ecegame_init:
 *  This function sets everything up ready to play through the
 *  game once.
 */
void ecegame_init() {
    gameEndFlag = 0;
    install_int (game_timer_callback, 1000);
    input_init();
    simulation_init(&game);
    render_init();
    loadFile(&game);
}

/* game_shutdown:
 *  Undo everything that game_init set up.
 */
void ecegame_shutdown() {
    //objects_shutdown();
    input_shutdown();
    render_shutdown();
}

/* game_run:
 *  This function actually plays the game.
 */
void ecegame_run() {
    while (!gameEndFlag) {
        game.duration = counter;
        input_update();
        //objects_update();
        simulation_update(&game);
        render_update(game);
        rest(40);
    }
}