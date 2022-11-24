#ifndef SIMULATION_H
#define SIMULATION_H

#define CASE_X 20 /* largeur en pixel de la case */
#define CASE_Y 20 /* hateur en pixel de la case */

#define GRID_NB_X 45 /* largeur en pixel de la case */
#define GRID_NB_Y 35 /* hateur en pixel de la case */

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGH 768

enum building { EMPTY, ROAD, HOUSE, WATER_TOWER, POWER_STATION, WATER_PIPE, ELECTRICITY_CABLE};

struct Case {
    enum building type;
};

struct World {
    struct Case level0[GRID_NB_X][GRID_NB_Y];
    struct Case level_1[GRID_NB_X][GRID_NB_Y];
    struct Case level_2[GRID_NB_X][GRID_NB_Y];
};

extern struct World world;

struct Building {
    enum building type;
    int capacity;
    int createdAt;
    int updatedAt;
};

struct BuildingNode {
    struct Building building;
    struct BuildingNode *next;
} *ptr;

struct Game {
    int flouz;
    int citizens;
    int water;
    int electricity;
    int selectedItem; // 0 : rien de sélectionné;
    struct BuildingNode buildings;
};

#endif