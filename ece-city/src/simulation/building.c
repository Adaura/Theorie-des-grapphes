#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

void ajouterBuilding(struct Game game, enum building type, int x, int y, int w, int h){
    //Créer la structure building
    //create a link
    struct BuildingNode *buildingNode = (struct BuildingNode*) malloc(sizeof(struct BuildingNode));

    buildingNode->building.type = type;
    buildingNode->building.x = x;
    buildingNode->building.y = y;
    buildingNode->building.w = w;
    buildingNode->building.h = h;
    if(type == HOUSE){
        buildingNode->building.capacity = 0;
        buildingNode->building.createdAt = game.duration;
        buildingNode->building.updatedAt = game.duration;
    }else if(type == WATER_TOWER){
        buildingNode->building.capacity = 5000;
        buildingNode->building.createdAt = game.duration;
        buildingNode->building.updatedAt = game.duration;
    }else if(type == POWER_STATION){
        buildingNode->building.capacity = 5000;
        buildingNode->building.createdAt = game.duration;
        buildingNode->building.updatedAt = game.duration;
    }

    if(type == HOUSE || type == WATER_TOWER|| type == POWER_STATION){
        buildingNode->next = game.buildings.next;
        game.buildings.next = buildingNode;
    }
}
