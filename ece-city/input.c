/*----------------------------------------------------------------
 * input.c -- Implémentation
 *----------------------------------------------------------------
 */


#include <allegro.h>
#include "input.h"
#include "simulationvars.h"

struct Coord *mouseCoord;
struct Coord *mouseCoordSelected;
int input_selectedLevel;
enum building input_selectedBuilding;

void input_init() {
    mouseCoord = (struct Coord *) malloc(sizeof(struct Coord));
    mouseCoordSelected = (struct Coord *) malloc(sizeof(struct Coord));
    input_selectedLevel = 0;
    input_selectedBuilding = EMPTY;
}

void input_shutdown() {
}



struct Coord getMouseCoordOnMap() {
}


/* input_update:
 *
 */
void input_update() {
    /* end the game if the user presses Esc */
    if (key[KEY_ESC]) gameEndFlag = 1;
    if(key[KEY_D] && !debugFlag){
        debugFlag = 1;
    }else if(key[KEY_D] && debugFlag){
        debugFlag = 0;
    }

    mouseCoord->selected = false;

    //Highlight de la grille
    if (mouse_x < GRID_NB_X * CASE_X && mouse_y < GRID_NB_Y * CASE_Y) {
        mouseCoord->selectionMode = GRID;
        mouseCoord->x = mouse_x / CASE_X;
        //printf("###mouse ### %d, %d\n", mouseCoord->x, mouse_x);
        mouseCoord->y = mouse_y / CASE_Y;
    } else if (mouse_x > 915 && mouse_x < 955 && mouse_y > 50 && mouse_y < 90) { // Road
        mouseCoord->x = 0;
        mouseCoord->y = 0;
        mouseCoord->selectionMode = BUILDING;
    } else if (mouse_x > 975 && mouse_x < 1015 && mouse_y > 50 && mouse_y < 90) { //House
        mouseCoord->x = 1;
        mouseCoord->y = 0;
        mouseCoord->selectionMode = BUILDING;
    } else if (mouse_x > 915 && mouse_x < 955 && mouse_y > 130 && mouse_y < 190) { //Power station
        mouseCoord->x = 0;
        mouseCoord->y = 1;
        mouseCoord->selectionMode = BUILDING;
    } else if (mouse_x > 975 && mouse_x < 1015 && mouse_y > 130 && mouse_y < 190) { //Water
        mouseCoord->x = 1;
        mouseCoord->y = 1;
        mouseCoord->selectionMode = BUILDING;
    } else if (mouse_x > 940 && mouse_x < 980 && mouse_y > 210 && mouse_y < 270) { //
        mouseCoord->x = 0;
        mouseCoord->y = 2;
        mouseCoord->selectionMode = BUILDING;
    } else if (mouse_x > 910 && mouse_x < 1019 && mouse_y > 480 && mouse_y < 510) { // Levels
        mouseCoord->x = 0;
        mouseCoord->y = 3;
        mouseCoord->selectionMode = LEVELS;
    } else if (mouse_x > 910 && mouse_x < 1019 && mouse_y > 520 && mouse_y < 550) {
        mouseCoord->x = 0;
        mouseCoord->y = 4;
        mouseCoord->selectionMode = LEVELS;
    } else if (mouse_x > 910 && mouse_x < 1019 && mouse_y > 570 && mouse_y < 600) {
        mouseCoord->x = 0;
        mouseCoord->y = 5;
        mouseCoord->selectionMode = LEVELS;
    }
    mouseCoord->px = mouse_x;
    mouseCoord->py = mouse_y;

    if (mouse_b & 1) {
        if(mouseCoord->selectionMode == BUILDING && mouseCoord->x == 0 && mouseCoord->y == 0){
            input_selectedBuilding = ROAD;
        }else if(mouseCoord->selectionMode == BUILDING &&mouseCoord->x == 1 && mouseCoord->y == 0){
            input_selectedBuilding = HOUSE;
        }else if(mouseCoord->selectionMode == BUILDING &&mouseCoord->x == 0 && mouseCoord->y == 1){
            input_selectedBuilding = POWER_STATION;
        }else if(mouseCoord->selectionMode == BUILDING &&mouseCoord->x == 1 && mouseCoord->y == 1){
            input_selectedBuilding = WATER_TOWER;
        }else if(mouseCoord->selectionMode == BUILDING &&mouseCoord->x == 0 && mouseCoord->y == 2) {
            input_selectedBuilding = FIRE_STATION;
        }

        if (mouseCoord->selectionMode == LEVELS && mouseCoord->y == 3) {
            input_selectedLevel = 0;
        } else if (mouseCoord->selectionMode == LEVELS && mouseCoord->y == 4) {
            input_selectedLevel = 1;
        } else if (mouseCoord->selectionMode == LEVELS && mouseCoord->y == 5) {
            input_selectedLevel = 2;
        }

        if(mouseCoord->selected == true){
            input_selectedBuilding = EMPTY;
            mouseCoord->selected = false;
        }else{
            mouseCoord->selected = true;
        }
    }
}
