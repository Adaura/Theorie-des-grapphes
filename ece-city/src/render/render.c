#include <allegro.h>
#include "../simulation/simulation.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

int init = 0;
struct World game;
BITMAP *bufferMap;
BITMAP *buffer;

BITMAP *roadImage;
BITMAP *houseImage;
BITMAP *powerStationImage;
BITMAP *waterTowerImage;
BITMAP *fireStation;

void initWorld(){
    FILE *fp = fopen("../paris.txt", "r");
    char ch;
    if (fp == NULL)
    {
        allegro_message("pb fichier font inexistant");
        allegro_exit();
        exit(EXIT_FAILURE);

    }

    //while((ch=fgetc(fp))!=EOF){
    //    printf("%c", ch);
    //}
    char loadedMap[45][35];
    for(int i = 0;i<35;i++){
        for(int j = 0;j<45;j++){
            ch=fgetc(fp);
            //printf("%c", ch);
            if(ch == '\n'){
                ch=fgetc(fp);
            }
            loadedMap[j][i] = ch;
        }
    }
    for(int i = 0;i<35;i++){
        for(int j = 0;j<45;j++){
            printf("%c", loadedMap[j][i]);
        }
        printf("\n");
    }
    printf("########\n");
    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++)
        {

            //printf("%c", ch);
            game.level0[i][j].type = EMPTY;
            game.level_1[i][j].type = EMPTY;
            game.level_2[i][j].type = EMPTY;
            printf("%c", loadedMap[i][j]);
            int isRoad = loadedMap[i][j] == 'r';
            int isHouse = loadedMap[i][j] == 'h';
            int isWaterTower = loadedMap[i][j] == 'w';
            int isPowerStation = loadedMap[i][j] == 'e';
            if(isRoad == 1){
                game.level0[i][j].type = ROAD;
                game.level_1[i][j].type = WATER_PIPE;
                game.level_2[i][j].type = ELECTRICITY_CABLE;
            }else if(isHouse == 1){
                game.level0[i][j].type = HOUSE;
                game.level_1[i][j].type = EMPTY;
                game.level_2[i][j].type = EMPTY;
            }else if(isWaterTower == 1){
                game.level0[i][j].type = WATER_TOWER;
                game.level_1[i][j].type = EMPTY;
                game.level_2[i][j].type = EMPTY;
            }else if(isPowerStation == 1){
                game.level0[i][j].type = POWER_STATION;
                game.level_1[i][j].type = EMPTY;
                game.level_2[i][j].type = EMPTY;
            }
        }
    }
    fclose(fp); // close the file
}

void initSim(){
    initWorld();
}

void renderWorld(BITMAP* buffer){
    FONT *gfont = load_font("../assets/SansS.pcx",0, 0);
    if (!gfont)
    {
        allegro_message("pb font");
        allegro_exit();
        exit(EXIT_FAILURE);
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
            if(visited[i][j] == 0){
                if(game.level0[i][j].type == EMPTY){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    int x2 = (i*CASE_X) + CASE_X;
                    int y2 = (j*CASE_Y) + CASE_Y;
                    //printf("Case (%d, %d) -> (%d, %d, %d, %d)\n", i, j, x1, y1, x2, y2);
                    rectfill(buffer, x1, y1, x2, y2, makecol(0, 255, 0));
                    //textprintf_ex(buffer,gfont,i*CASE_X + CASE_X/2,j*CASE_Y + CASE_Y/2,makecol(255,0,50),0,"(%d)",i);
                    //textout_ex(buffer,gfont,"A",100,65,makecol(120,200,255),0);
                }else  if(game.level0[i][j].type == ROAD){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    int x2 = (i*CASE_X) + CASE_X;
                    int y2 = (j*CASE_Y) + CASE_Y;
                    masked_blit(roadImage,buffer,0, 0, i*CASE_X, j*CASE_Y,20, 20);
                    //rectfill(buffer, x1, y1, x2, y2, makecol(255, 0, 0));
                }else  if(game.level0[i][j].type == HOUSE){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    for(int k = 0;k<3;k++){
                        for(int d = 0;d<3;d++) {
                            if (game.level0[i + k][j + d].type != HOUSE) {
                                allegro_message("Maison invalide");
                                allegro_exit();
                                exit(EXIT_FAILURE);
                            }
                            visited[i + k][j + d] = 1;
                        }
                    }
                    masked_blit(houseImage,buffer,0, 0, x1, y1,60, 60);
                }else  if(game.level0[i][j].type == WATER_TOWER){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    for(int k = 0;k<4;k++){
                        for(int d = 0;d<6;d++) {
                            if (game.level0[i + k][j + d].type != WATER_TOWER) {
                                allegro_message("WATER_TOWER invalide");
                                allegro_exit();
                                exit(EXIT_FAILURE);
                            }
                            visited[i + k][j + d] = 1;
                        }
                    }
                    masked_blit(waterTowerImage,buffer,0, 0, x1, y1,80, 120);
                }else  if(game.level0[i][j].type == POWER_STATION){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    for(int k = 0;k<4;k++){
                        for(int d = 0;d<6;d++) {
                            if (game.level0[i + k][j + d].type != POWER_STATION) {
                                allegro_message("POWER_STATION invalide");
                                allegro_exit();
                                exit(EXIT_FAILURE);
                            }
                            visited[i + k][j + d] = 1;
                        }
                    }
                    masked_blit(powerStationImage,buffer,0, 0, x1, y1,80, 120);
                }

                visited[i][j] = 1;
            }
        }
    }
}

void renderGrid(BITMAP* buffer){
    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++)
        {
            rect(buffer, i*CASE_X, j*CASE_Y, (i*CASE_X) + CASE_X, (j*CASE_Y) + CASE_Y, makecol(255, 255, 255));
        }
    }
}

void highlightCase(BITMAP* buffer){
    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++)
        {
            int x1 = i*CASE_X;
            int y1 = j*CASE_Y;
            int x2 = (i*CASE_X) + CASE_X;
            int y2 = (j*CASE_Y) + CASE_Y;
            //printf("Case (%d, %d) -> (%d, %d, %d, %d)\n", i, j, x1, y1, x2, y2);
            if(mouse_x > x1 && mouse_x < x2 && mouse_y > y1 && mouse_y < y2){
                //printf("%d\n", mouse_x);
                rectfill(buffer, x1, y1, x2, y2, makecol(0, 200, 200));
            }
        }
    }
    if(mouse_x > 920 && mouse_x < 940 && mouse_y > 32 && mouse_y < 52){
        rect(buffer, 920, 30, 940, 50,makecol(255, 255, 0));
    }else if(mouse_x > 920 && mouse_x < 980 && mouse_y > 72 && mouse_y < 132){
        rect(buffer, 920, 70, 980, 130,makecol(255, 255, 0));
    }else if(mouse_x > 920 && mouse_x < 1000 && mouse_y > 162 && mouse_y < 282){
        rect(buffer, 920, 160, 1000, 280,makecol(255, 255, 0));
    }else if(mouse_x > 920 && mouse_x < 1000 && mouse_y > 312 && mouse_y < 432){
        rect(buffer, 920, 310, 1000, 430,makecol(255, 255, 0));
    }else if(mouse_x > 920 && mouse_x < 1000 && mouse_y > 462 && mouse_y < 582) {
        rect(buffer, 920, 460, 1000, 580, makecol(255, 255, 0));
    }
}

void renderActions(BITMAP* buffer){
    //Palette
    rect(buffer, 910, 20, 1020, 600, makecol(255, 255, 0));

    // Icône route
    masked_blit(roadImage,buffer,0, 0, 910 + 10, 20 + 10,20, 20);

    //Icône maison
    masked_blit(houseImage,buffer,0, 0, 920, 70,60, 60);

    //Icône central electrique
    masked_blit(powerStationImage,buffer,0, 0, 920, 160,80, 120);

    //Icône chateau eau
    masked_blit(waterTowerImage,buffer,0, 0, 920, 310,80, 120);

    //Icône pompier
    masked_blit(fireStation,buffer,0, 0, 920, 460,80, 120);


    //Scores
    rect(buffer, 20, 710, 800, 760, makecol(255, 255, 0));
}

void loadAssets(){
    roadImage = load_bitmap("../assets/route.bmp", NULL);
    houseImage = load_bitmap("../assets/cabane.bmp", NULL);
    powerStationImage = load_bitmap("../assets/centraleelectrique.bmp", NULL);
    waterTowerImage = load_bitmap("../assets/waterTower.bmp", NULL);
    fireStation= load_bitmap("../assets/caserne.bmp", NULL);

    if (!roadImage){
        allegro_message("pb route.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void initRender(){
    loadAssets();
    bufferMap = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    initSim();
    init = 1;
    rectfill(bufferMap,0,0,SCREEN_WIDTH,SCREEN_HEIGH, makecol(0,0,0));
    renderWorld(bufferMap);
    renderGrid(bufferMap);
    renderActions(bufferMap);
    //textout_ex(buffer,font,"A",100,65,makecol(120,200,255),0);
    blit(bufferMap, screen, 0, 0, 0, 0, screen->w, screen->h);
}

void render(){
    clear_bitmap(buffer);
    blit(bufferMap, buffer, 0, 0, 0, 0, screen->w, screen->h);
    highlightCase(buffer);
    blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);
}