#include <stdio.h>
#include "simulation.h"
#include "simulationvars.h"
#include "input.h"
#include "building.h"
#include "map.h"

//initialisation des donnees du jeu
void init_game_world(struct Game *game){
    //Init game params
    game->citizens = 0;
    game->duration = 0;
    game->water = 0;
    game->electricity = 0;
    game->flouz = FLOUZ_INITIAL_AMOUNT;
    game->buildings.next = NULL;

    printf("### %d\n", game->flouz);
}

//lancement de l initialisation
void simulation_init(struct Game *game){
    init_game_world(game);
    map_init(game);
}

//mise a jour du jeu
void simulation_update(struct Game *game){
    game->currentLevel = input_selectedLevel;
    game->electricity = 0;
    game->water = 0;
    game->citizens = 0;
    game->waterTowerNb = 0;
    game->powerStationNb = 0;
    game->housesNb = 0;
    if(game->currentLevel == 0){
        game->selectedBuilding = input_selectedBuilding;
    }else{
        game->selectedBuilding = EMPTY;
    }
    //printf("Selectoon Mode %d\n", mouseCoord->selectionMode);
    if(game->currentLevel == 0 && game->selectedBuilding != EMPTY && mouseCoord->selected == true && mouseCoord->selectionMode == GRID){
        ajouterBuilding(game, mouseCoord->x, mouseCoord->y, game->selectedBuilding);
        game->selectedBuilding = EMPTY;
    }

    building_update(game);
    map_update(game);
}