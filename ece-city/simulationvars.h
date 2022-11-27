#ifndef SIMULATION_H
#define SIMULATION_H

#include<stdbool.h>

#define CASE_X 20 /* largeur en pixel de la case */
#define CASE_Y 20 /* hateur en pixel de la case */

#define GRID_NB_X 45 /* largeur en pixel de la case */
#define GRID_NB_Y 35 /* hateur en pixel de la case */

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGH 768

#define FLOUZ_INITIAL_AMOUNT 500000
#define TAX_PER_CITIZEN 10
#define CYCLE_DURATION 2

#define ROAD_CASE_W = 1;
#define ROAD_CASE_H = 1;
#define HOUSE_CASE_W = 3;
#define HOUSE_CASE_H = 3;
#define BUILDING_CASE_W = 4;
#define BUILDING_CASE_H = 6;

extern int gameEndFlag;
extern int debugFlag;

//type des differents batiments
enum building { EMPTY, ROAD, HOUSE, WATER_TOWER, POWER_STATION,FIRE_STATION, WATER_PIPE, ELECTRICITY_CABLE};

struct Case {
    enum building type;
};

//structure des differents niveau de la grille
struct World {
    enum building level0[GRID_NB_X][GRID_NB_Y];
    enum building level_1[GRID_NB_X][GRID_NB_Y];
    enum building level_2[GRID_NB_X][GRID_NB_Y];
};

struct Building {
    enum building type;
    bool valid;
    int cost;
    int capacity;
    int createdAt;
    int updatedAt;
    int x;
    int y;
    int w;
    int h;
};

//noeud des batiments
struct BuildingNode {
    struct Building building;
    struct BuildingNode *next;
};

enum SELECTION_MODE {GRID, BUILDING, LEVELS};

struct Coord{
    int x;
    int y;
    int px; //Coords in pixel
    int py; //Coords in pixel
    enum SELECTION_MODE selectionMode;
    bool selected;
};

enum GameMode {CAPITALISME, COMMUNISME};

//structure regroupant les differentes structure
struct Game {
    enum GameMode mode;
    bool started;
    int flouz;
    int citizens;
    int housesNb;
    int water;
    int waterConsumed;
    int waterTowerNb;
    int electricity;
    int electricityConsumed;
    int powerStationNb;
    enum building selectedBuilding;
    struct BuildingNode buildings;
    int duration;
    int currentLevel;
    int hoverCase_x;
    int hoverCase_y;
    struct World world;
};

#endif