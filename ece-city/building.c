#include <allegro.h>
#include <stdio.h>
#include "ecegame.h"
#include "render.h"
#include "input.h"
#include "simulationvars.h"
#include "simulation.h"
#include "assets.h"

void ajouterBuilding(struct Game *game, int x, int y) {
    //Créer la structure building
    //create a link
    struct BuildingNode *buildingNode = (struct BuildingNode *) malloc(sizeof(struct BuildingNode));

    buildingNode->building.type = game->selectedBuilding;
    buildingNode->building.x = x;
    buildingNode->building.y = y;
    if (game->selectedBuilding == HOUSE) {
        buildingNode->building.capacity = 0;
        buildingNode->building.createdAt = game->duration;
        buildingNode->building.updatedAt = game->duration;
        buildingNode->building.w = 3;
        buildingNode->building.h = 3;
    } else if (game->selectedBuilding == WATER_TOWER) {
        buildingNode->building.capacity = 5000;
        buildingNode->building.createdAt = game->duration;
        buildingNode->building.updatedAt = game->duration;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
    } else if (game->selectedBuilding == POWER_STATION) {
        buildingNode->building.capacity = 5000;
        buildingNode->building.createdAt = game->duration;
        buildingNode->building.updatedAt = game->duration;
        buildingNode->building.w = 4;
        buildingNode->building.h = 6;
    }

    for(int k = 0;k<buildingNode->building.w;k++){
        for(int d = 0;d<buildingNode->building.h;d++) {
            game->world.level0[x + k][y + d] = game->selectedBuilding;
        }
    }
    buildingNode->next = game->buildings.next;
    game->buildings.next = buildingNode;
}

void update(struct Game *game){
    struct BuildingNode *ptr = &game->buildings;
    while (ptr != NULL) {
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