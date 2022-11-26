#include <stdlib.h>
#include "../simulation/simulation.h"
#include <allegro.h>

void insertBuilding(BITMAP* buffer, struct Game game){

    int matrice[GRID_NB_X][GRID_NB_Y];

    if(mouse_x > 915 && mouse_x < 955 && mouse_y > 50 && mouse_y < 90){
        if(mouse_b==1){
            game.selectedItem=1;
        }
    }else if(mouse_x > 975 && mouse_x < 1015 && mouse_y > 50 && mouse_y < 90){
        if(mouse_b==1){
            game.selectedItem=2;
        }
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 130 && mouse_y < 190){
        if(mouse_b==1){
            game.selectedItem=3;
        }
    }else if(mouse_x > 975 && mouse_x < 1015 && mouse_y > 130 && mouse_y < 190){
        if(mouse_b==1){
            game.selectedItem=4;
        }
    }else if(mouse_x > 940 && mouse_x < 980 && mouse_y > 210 && mouse_y < 270) {
        if(mouse_b==1){
            game.selectedItem=5;
        }
    }
    if(game.selectedItem==1) {
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                int x1 = i * CASE_X;
                int y1 = j * CASE_Y;
                int x2 = (i * CASE_X) + CASE_X;
                int y2 = (j * CASE_Y) + CASE_Y;
                if (mouse_x >= x1 && mouse_x <= x2 && mouse_y > y1 && mouse_y < y2) {
                    if (mouse_b == 1) {
                        world.level0[i][j].type = ROAD;
                        world.level_1[i][j].type = WATER_PIPE;
                        world.level_2[i][j].type = ELECTRICITY_CABLE;
                        matrice[i][j] = 1;
                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 1) {
                    if (world.level0[i][j].type == ROAD) {
                        masked_blit(roadImage, buffer, 0, 0, i * CASE_X, j * CASE_Y, 40, 40);
                    }

                }
            }
        }
    }else  if(game.selectedItem==2) {
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                int x1 = i * CASE_X;
                int y1 = j * CASE_Y;
                int x2 = (i * CASE_X) + CASE_X;
                int y2 = (j * CASE_Y) + CASE_Y;
                if (mouse_x >= x1 && mouse_x <= x2 && mouse_y > y1 && mouse_y < y2) {
                    if (mouse_b == 1) {
                        for(int k = 0;k<3;k++){
                            for(int d = 0;d<3;d++) {
                                if ((world.level0[i + k][j - 1].type == ROAD || world.level0[i + k][j + 3].type == ROAD) && world.level0[i + k][j + d].type == EMPTY){
                                    world.level0[i][j].type = HOUSE;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    matrice[i][j] = 2;
                                }else if ((world.level0[i -1][j+d].type == ROAD || world.level0[i +3][j +d].type == ROAD) && world.level0[i+k][j+d].type == EMPTY ) {
                                    world.level0[i][j].type = HOUSE;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    matrice[i][j] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 2) {
                    if (world.level0[i][j].type == HOUSE) {
                        masked_blit(houseImage, buffer, 0, 0, i * CASE_X, j * CASE_Y, 60, 60);
                    }

                }
            }
        }
    }else  if(game.selectedItem==3) {
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                int x1 = i * CASE_X;
                int y1 = j * CASE_Y;
                int x2 = (i * CASE_X) + CASE_X;
                int y2 = (j * CASE_Y) + CASE_Y;
                if (mouse_x >= x1 && mouse_x <= x2 && mouse_y > y1 && mouse_y < y2) {
                    if (mouse_b == 1) {
                        world.level0[i][j].type = POWER_STATION;
                        world.level_1[i][j].type = EMPTY;
                        world.level_2[i][j].type = EMPTY;
                        matrice[i][j] = 3;
                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 3) {
                    if (world.level0[i][j].type == POWER_STATION) {
                        //rect(buffer,x1,y1,x2,y2, makecol(255,0,0));
                        masked_blit(powerStationImage, buffer, 0, 0, i * CASE_X, j * CASE_Y, 80, 120);
                    }
                }
            }
        }
    }else  if(game.selectedItem==4) {
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                int x1 = i * CASE_X;
                int y1 = j * CASE_Y;
                int x2 = (i * CASE_X) + CASE_X;
                int y2 = (j * CASE_Y) + CASE_Y;
                if (mouse_x >= x1 && mouse_x <= x2 && mouse_y > y1 && mouse_y < y2) {
                    if (mouse_b == 1) {
                        world.level0[i][j].type = WATER_TOWER;
                        world.level_1[i][j].type = EMPTY;
                        world.level_2[i][j].type = EMPTY;
                        matrice[i][j] = 4;
                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 4) {
                    if (world.level0[i][j].type == WATER_TOWER) {
                        //rect(buffer,x1,y1,x2,y2, makecol(255,0,0));
                        masked_blit(waterTowerImage, buffer, 0, 0, i * CASE_X, j * CASE_Y, 80, 120);
                    }
                }
            }
        }
    }else  if(game.selectedItem==5) {
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                int x1 = i * CASE_X;
                int y1 = j * CASE_Y;
                int x2 = (i * CASE_X) + CASE_X;
                int y2 = (j * CASE_Y) + CASE_Y;
                if (mouse_x >= x1 && mouse_x <= x2 && mouse_y > y1 && mouse_y < y2) {
                    if (mouse_b == 1) {
                        world.level0[i][j].type =FIRE_STATION ;
                        world.level_1[i][j].type = EMPTY;
                        world.level_2[i][j].type = EMPTY;
                        matrice[i][j] = 5;
                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 5) {
                    if (world.level0[i][j].type == FIRE_STATION) {
                        //rect(buffer,x1,y1,x2,y2, makecol(255,0,0));
                        masked_blit(fireStation, buffer, 0, 0, i * CASE_X, j * CASE_Y, 80, 120);
                    }
                }
            }
        }
    }
}