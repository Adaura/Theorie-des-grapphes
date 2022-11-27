#include <allegro.h>
#include <stdio.h>
#include "ecegame.h"
#include "render.h"
#include "input.h"
#include "simulationvars.h"
#include "simulation.h"
#include "assets.h"


//ajout d un building
void ajouterBuilding(struct Game *game, int x, int y, enum building type) {
    //Créer la structure building
    //create a link
    struct BuildingNode *buildingNode = (struct BuildingNode *) malloc(
            sizeof(struct BuildingNode));//malloc des buildings

    buildingNode->building.type = type;
    buildingNode->building.x = x;
    buildingNode->building.y = y;
    buildingNode->building.createdAt = game->duration;
    buildingNode->building.updatedAt = game->duration;
    if (type == HOUSE) {//initialisation dans le cas d'une maison
        buildingNode->building.capacity = 0;
        buildingNode->building.w = 3;
        buildingNode->building.h = 3;
        buildingNode->building.cost = 1000;
    } else if (type == WATER_TOWER) {//initialisation dans le cas d'un chateau d eau
        buildingNode->building.capacity = 5000;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
        buildingNode->building.cost = 100000;
    } else if (type == POWER_STATION) {//initialisation dans le cas d'une centrale electrique
        buildingNode->building.capacity = 5000;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
        buildingNode->building.cost = 100000;
    } else if (type == ROAD) {//initialisation dans le cas d'une route
        buildingNode->building.w = 1;
        buildingNode->building.h = 1;
        buildingNode->building.cost = 10;
    } else if (type == FIRE_STATION) {//initialisation dans le cas d'une caserne
        buildingNode->building.capacity = 20;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
        buildingNode->building.cost = 10000;
    }

    //Check argent
    if (game->flouz - buildingNode->building.cost < 0) {
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

    //update map
    for (int k = 0; k < buildingNode->building.w; k++) {
        for (int d = 0; d < buildingNode->building.h; d++) {
            game->world.level0[x + k][y + d] = type;
        }
    }
    //noeud suivant
    game->flouz -= buildingNode->building.cost;
    buildingNode->next = game->buildings.next;
    game->buildings.next = buildingNode;
}

//algo theorie des grapphes
bool pathToPowerStation(struct Game *game) {
    return false;
}

//algo theorie des grapphes
bool pathToWaterTower(struct Game *game) {
    return false;
}

//mise  a  jour des batiments
void updateBuildingState(struct Building *building, struct Game *game) {
    // Case building technique
    building->valid = false;
    if (building->type == POWER_STATION || building->type == WATER_TOWER ||
        building->type == FIRE_STATION) {//cas de validite des batiments sauf  maison
        for (int i = 0; i < building->w; i++) {
            if (game->world.level0[building->x + i][building->y - 1] == ROAD) {
                building->valid = true;
                break;
            }
            if (game->world.level0[building->x + i][building->y + building->h] == ROAD) {
                building->valid = true;
                break;
            }
            if (game->world.level0[building->x - 1][building->y + i] == ROAD) {
                building->valid = true;
                break;
            }
            if (game->world.level0[building->x + building->w][building->y + i] == ROAD) {
                building->valid = true;
                break;
            }
        }
    } else if (building->type == HOUSE) {//cas d  une  maison
        for (int i = 0; i < building->w; i++) {
            if (game->world.level0[building->x + i][building->y - 1] == ROAD
                && game->world.level_1[building->x + i][building->y - 1] == WATER_PIPE
                && game->world.level_2[building->x + i][building->y - 1] == ELECTRICITY_CABLE) {
                building->valid = true;
                break;
            }
            if (game->world.level0[building->x + i][building->y + building->h] == ROAD
                && game->world.level_1[building->x + i][building->y + building->h] == WATER_PIPE
                && game->world.level_2[building->x + i][building->y + building->h] == ELECTRICITY_CABLE) {
                building->valid = true;
                break;
            }
            if (game->world.level0[building->x - 1][building->y + i] == ROAD
                && game->world.level_1[building->x - 1][building->y + i] == WATER_PIPE
                && game->world.level_2[building->x - 1][building->y + i] == ELECTRICITY_CABLE) {
                building->valid = true;
                break;
            }
            if (game->world.level0[building->x + building->w][building->y + i] == ROAD
                && game->world.level_1[building->x + building->w][building->y + i] == WATER_PIPE
                && game->world.level_2[building->x + building->w][building->y + i] == ELECTRICITY_CABLE) {
                building->valid = true;
                break;
            }
        }
    }
}

bool adjacentRoad(int x, int y, struct Game *game) {
    if (game->world.level0[x - 1][y] == ROAD
        || game->world.level0[x + 1][y] == ROAD
        || game->world.level0[x][y - 1] == ROAD
        || game->world.level0[x][y + 1] == ROAD) {
        return true;
    } else {
        return false;
    }
}

void tagNetworkLine(int x, int y, int visited[GRID_NB_X][GRID_NB_Y], struct Game *game) {
    while (visited[x][y] == 0 && game->world.level0[x][y] == ROAD && adjacentRoad(x, y, game)) {
        game->world.level_2[x][y] = ELECTRICITY_CABLE;
        visited[x][y] = 1;
        tagNetworkLine(x - 1, y, visited, game);
        tagNetworkLine(x + 1, y, visited, game);
        tagNetworkLine(x, y + 1, visited, game);
        tagNetworkLine(x, y - 1, visited, game);
    }
}

void tagWaterPipe(int x, int y, int visited[GRID_NB_X][GRID_NB_Y], struct Game *game) {
    while (visited[x][y] == 0 && game->world.level0[x][y] == ROAD && adjacentRoad(x, y, game)) {
        game->world.level_1[x][y] = WATER_PIPE;
        visited[x][y] = 1;
        tagWaterPipe(x - 1, y, visited, game);
        tagWaterPipe(x + 1, y, visited, game);
        tagWaterPipe(x, y + 1, visited, game);
        tagWaterPipe(x, y - 1, visited, game);
    }
}

void updateElectricityNetwork(struct Game *game) {
    //Initialiser la matrice des visites des sommets
    int visited[GRID_NB_X][GRID_NB_Y];
    for (int i = 0; i < GRID_NB_X; i++) {
        for (int j = 0; j < GRID_NB_Y; j++) {
            visited[i][j] = 0;
        }
    }

    struct BuildingNode *ptr = &game->buildings;
    while (ptr != NULL) {
        if (ptr->building.type == POWER_STATION) {
            for (int i = 0; i < ptr->building.w; i++) {
                tagNetworkLine(ptr->building.x + i, ptr->building.y - 1, visited, game);
                tagNetworkLine(ptr->building.x + i, ptr->building.y + ptr->building.h, visited, game);
            }
            for (int i = 0; i < ptr->building.h; i++) {
                tagNetworkLine(ptr->building.x - 1, ptr->building.y + i, visited, game);
                tagNetworkLine(ptr->building.x + ptr->building.w, ptr->building.y + i, visited, game);
            }
        }
        ptr = ptr->next;
    }
}

void updateWaterNetwork(struct Game *game) {
    //Initialiser la matrice des visites des sommets
    int visited[GRID_NB_X][GRID_NB_Y];
    for (int i = 0; i < GRID_NB_X; i++) {
        for (int j = 0; j < GRID_NB_Y; j++) {
            visited[i][j] = 0;
        }
    }

    struct BuildingNode *ptr = &game->buildings;
    while (ptr != NULL) {
        if (ptr->building.type == WATER_TOWER) {
            for (int i = 0; i < ptr->building.w; i++) {
                tagWaterPipe(ptr->building.x + i, ptr->building.y - 1, visited, game);
                tagWaterPipe(ptr->building.x + i, ptr->building.y + ptr->building.h, visited, game);
            }
            for (int i = 0; i < ptr->building.h; i++) {
                tagWaterPipe(ptr->building.x - 1, ptr->building.y + i, visited, game);
                tagWaterPipe(ptr->building.x + ptr->building.w, ptr->building.y + i, visited, game);
            }
        }
        ptr = ptr->next;
    }
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

        if (ptr->building.type == HOUSE && ptr->building.valid) {
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
    updateElectricityNetwork(game);
    updateWaterNetwork(game);
}