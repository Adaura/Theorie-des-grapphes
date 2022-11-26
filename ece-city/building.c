#include <allegro.h>
#include <stdio.h>
#include "ecegame.h"
#include "render.h"
#include "input.h"
#include "simulationvars.h"
#include "simulation.h"
#include "assets.h"


//ajout d un building
void ajouterBuilding(struct Game *game, int x, int y) {
    //Créer la structure building
    //create a link
    struct BuildingNode *buildingNode = (struct BuildingNode *) malloc(sizeof(struct BuildingNode));//malloc des buildings

    buildingNode->building.type = game->selectedBuilding;
    buildingNode->building.x = x;
    buildingNode->building.y = y;
    buildingNode->building.createdAt = game->duration;
    buildingNode->building.updatedAt = game->duration;
    if (game->selectedBuilding == HOUSE) {//initialisation dans le cas d'une maison
        buildingNode->building.capacity = 0;
        buildingNode->building.w = 3;
        buildingNode->building.h = 3;
        buildingNode->building.cost= 1000;
    } else if (game->selectedBuilding == WATER_TOWER) {//initialisation dans le cas d'un chateau d eau
        buildingNode->building.capacity = 5000;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
        buildingNode->building.cost= 100000;
    } else if (game->selectedBuilding == POWER_STATION) {//initialisation dans le cas d'une centrale electrique
        buildingNode->building.capacity = 5000;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
        buildingNode->building.cost= 100000;
    } else if (game->selectedBuilding == ROAD) {//initialisation dans le cas d'une route
        buildingNode->building.w = 1;
        buildingNode->building.h = 1;
        buildingNode->building.cost= 10;
    }else if (game->selectedBuilding == FIRE_STATION) {//initialisation dans le cas d'une caserne
        buildingNode->building.capacity = 20;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
        buildingNode->building.cost= 10000;
    }

    //Check argent
    if(game->flouz - buildingNode->building.cost < 0){
        return;
    }

    // Check zone validity
    for (int k = 0; k < buildingNode->building.w; k++) {
        for (int d = 0; d < buildingNode->building.h; d++) {
            if (game->world.level0[x + k][y + d] != EMPTY) {
                return;
            }
        }
    }

    for (int k = 0; k < buildingNode->building.w; k++) {
        for (int d = 0; d < buildingNode->building.h; d++) {
            game->world.level0[x + k][y + d] = game->selectedBuilding;
        }
    }
//noeud suivant
    game->flouz -= buildingNode->building.cost;
    buildingNode->next = game->buildings.next;
    game->buildings.next = buildingNode;
}

//algo theorie des grapphes
bool pathToPowerStation(struct Game *game){
    return false;
}

//algo theorie des grapphes
bool pathToWaterTower(struct Game *game){
    return false;
}

//mise  a  jour des batiments
void updateBuildingState(struct Building *building, struct Game *game) {
    // Case building technique
    bool valid = false;
    if (building->type == POWER_STATION || building->type == WATER_TOWER || building->type == FIRE_STATION) {//cas de validite des batiments sauf  maison
        for (int i = 0; i < building->w; i++) {
            if (game->world.level0[building->x + i][building->y - 1] == ROAD) {
                valid = true;
                break;
            }
            if (game->world.level0[building->x + i][building->y + building->h] == ROAD) {
                valid = true;
                break;
            }
            if (game->world.level0[building->x - 1][building->y + i] == ROAD) {
                valid = true;
                break;
            }
            if (game->world.level0[building->x + building->w][building->y + i] == ROAD) {
                valid = true;
                break;
            }
        }
    } else if (building->type == HOUSE) {//cas d  une  maison
        if (pathToPowerStation(game) && pathToWaterTower(game)) {
            valid = true;
        }
    } else {
        valid = true;
    }
    building->valid = valid;
}

//mise a  jour du jeu regulierement
void update(struct Game *game) {
    struct BuildingNode *ptr = &game->buildings;
    while (ptr != NULL) {
        updateBuildingState(&ptr->building, game);
        if (ptr->building.type == POWER_STATION) {
            game->electricity += ptr->building.capacity;
            game->powerStationNb++;
        }
        if (ptr->building.type == WATER_TOWER) {
            game->water += ptr->building.capacity;
            game->waterTowerNb++;
        }

        if (ptr->building.type == HOUSE) {
            if (game->duration - ptr->building.createdAt >= CYCLE_DURATION && ptr->building.capacity == 0) {
                game->flouz += ptr->building.capacity * TAX_PER_CITIZEN;
                ptr->building.capacity = 10;
                ptr->building.updatedAt = game->duration;
            } else if (game->duration - ptr->building.updatedAt >= CYCLE_DURATION && ptr->building.capacity == 10) {
                game->flouz += ptr->building.capacity * TAX_PER_CITIZEN;
                ptr->building.capacity = 50;
                ptr->building.updatedAt = game->duration;
            } else if (game->duration - ptr->building.updatedAt >= CYCLE_DURATION && ptr->building.capacity == 50) {
                game->flouz += ptr->building.capacity * TAX_PER_CITIZEN;
                ptr->building.capacity = 100;
                ptr->building.updatedAt = game->duration;
            } else if (game->duration - ptr->building.updatedAt >= CYCLE_DURATION && ptr->building.capacity == 100) {
                ptr->building.capacity = 1000;
                ptr->building.updatedAt = game->duration;
            }
            game->citizens += ptr->building.capacity;
            game->housesNb++;
        }

        ptr = ptr->next;
    }
}

void building_update(struct Game *game) {
    update(game);
}