#include <allegro.h>
#include "../simulation/simulation.h"
#include "../simulation/building.c"
#include "../utils/utils.c"
#include <stdlib.h>
#include <string.h>
#include "error.h"

int init = 0;
struct World world;
struct Game game;
BITMAP *bufferMap;
BITMAP *buffer;

BITMAP *roadImage;
BITMAP *boiteaOutilroadImage;
BITMAP *houseImage;
BITMAP *boiteaOutilhouseImage;
BITMAP *powerStationImage;
BITMAP *boiteaOutilpowerStationImage;
BITMAP *waterTowerImage;
BITMAP *boiteaOutilwaterTowerImage;
BITMAP *fireStation;
BITMAP *boiteaOutilfireStation;
BITMAP *palette;
BITMAP *chantierImage;
BITMAP *cabaneImage;
BITMAP *immeubleImage;
BITMAP *gratteImage;

//Gestion des batiments
void ajouterBuilding(enum building type, int x, int y, int w, int h){
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

void supprimerBatiment(){

}

void insertBuilding(BITMAP* buffer){

    int matrice[GRID_NB_X][GRID_NB_Y];

    if(mouse_x > 915 && mouse_x < 955 && mouse_y > 50 && mouse_y < 90){
        if(mouse_b==1){
            game.selectedItem=1;
        }
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 110 && mouse_y < 150){
        if(mouse_b==1){
            game.selectedItem=2;
        }
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 170 && mouse_y < 230){
        if(mouse_b==1){
            game.selectedItem=3;
        }
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 250 && mouse_y < 310){
        if(mouse_b==1){
            game.selectedItem=4;
        }
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 330 && mouse_y < 390) {
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
                        game.flouz -= 10;
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
                                if ((world.level0[i + k][j - 1].type == ROAD || world.level0[i + k][j + 3].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)){
                                    world.level0[i][j].type = HOUSE;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 1000;
                                    matrice[i][j] = 2;
                                }else if ((world.level0[i -1][j+d].type == ROAD || world.level0[i +3][j +d].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY) ) {
                                    world.level0[i][j].type = HOUSE;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 1000;
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
                        ajouterBuilding(world.level0[i][j].type, i, j, 3, 3);
                        masked_blit(chantierImage, buffer, 0, 0, i * CASE_X, j * CASE_Y, 60, 60);
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
                        for(int k = 0;k<4;k++){
                            for(int d = 0;d<6;d++) {
                                if ((world.level0[i + k][j - 1].type == ROAD || world.level0[i + k][j + 6].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)){
                                    world.level0[i][j].type = POWER_STATION;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 1000000;
                                    matrice[i][j] = 3;
                                }else if ((world.level0[i -1][j+d].type == ROAD || world.level0[i +4][j +d].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)) {
                                    world.level0[i][j].type = POWER_STATION;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 100000;
                                    matrice[i][j] = 3;
                                }
                            }
                        }

                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 3) {
                    if (world.level0[i][j].type == POWER_STATION) {
                        ajouterBuilding(world.level0[i][j].type,i, j, 4, 6);
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
                        for(int k = 0;k<4;k++){
                            for(int d = 0;d<6;d++) {
                                if ((world.level0[i + k][j - 1].type == ROAD || world.level0[i + k][j + 6].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)){
                                    world.level0[i][j].type = WATER_TOWER;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 1000000;
                                    matrice[i][j] = 4;
                                }else if ((world.level0[i -1][j+d].type == ROAD || world.level0[i +4][j +d].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)) {
                                    world.level0[i][j].type = WATER_TOWER;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 100000;
                                    matrice[i][j] = 4;
                                }
                            }
                        }
                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 4) {
                    if (world.level0[i][j].type == WATER_TOWER) {
                        ajouterBuilding(world.level0[i][j].type,i, j, 4, 6);
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
                        for(int k = 0;k<4;k++){
                            for(int d = 0;d<6;d++) {
                                if ((world.level0[i + k][j - 1].type == ROAD || world.level0[i + k][j + 6].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)){
                                    world.level0[i][j].type = FIRE_STATION;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 1000000;
                                    matrice[i][j] = 5;
                                }else if ((world.level0[i -1][j+d].type == ROAD || world.level0[i +4][j +d].type == ROAD) && (world.level0[i + k][j + d].type == EMPTY)) {
                                    world.level0[i][j].type = FIRE_STATION;
                                    world.level_1[i][j].type = EMPTY;
                                    world.level_2[i][j].type = EMPTY;
                                    game.flouz -= 100000;
                                    matrice[i][j] = 5;
                                }
                            }
                        }
                    }
                }

            }
        }
        for (int i = 0; i < GRID_NB_X; i++) {
            for (int j = 0; j < GRID_NB_Y; j++) {
                if (matrice[i][j] == 5) {
                    if (world.level0[i][j].type == FIRE_STATION) {
                        ajouterBuilding(world.level0[i][j].type,i, j, 4, 6);
                        masked_blit(fireStation, buffer, 0, 0, i * CASE_X, j * CASE_Y, 80, 120);
                    }
                }
            }
        }
    }
}

void initWorld(){
    //Init game params
    game.citizens = 0;
    game.duration = 0;
    game.water = 0;
    game.electricity = 0;
    game.flouz = 500000;
    game.buildings.next = NULL;

    FILE *fp = fopen("../paris.txt", "r");
    char ch;
    if (fp == NULL)
    {
        allegro_message("pb fichier font inexistant");
        allegro_exit();
        exit(EXIT_FAILURE);

    }

    char loadedMap[45][35];
    for(int i = 0;i<35;i++){
        for(int j = 0;j<45;j++){
            ch=fgetc(fp);
            if(ch == '\n'){
                ch=fgetc(fp);
            }
            loadedMap[j][i] = ch;
        }
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
            world.level0[i][j].type = EMPTY;
            world.level_1[i][j].type = EMPTY;
            world.level_2[i][j].type = EMPTY;
            int isRoad = loadedMap[i][j] == 'r';
            int isHouse = loadedMap[i][j] == 'h';
            int isWaterTower = loadedMap[i][j] == 'w';
            int isPowerStation = loadedMap[i][j] == 'e';

            if(isRoad == 1){
                world.level0[i][j].type = ROAD;
                world.level_1[i][j].type = WATER_PIPE;
                world.level_2[i][j].type = ELECTRICITY_CABLE;
                visited[i][j] = 1;

                game.flouz -= 10;
            }else if(isHouse == 1){
                world.level0[i][j].type = HOUSE;
                world.level_1[i][j].type = EMPTY;
                world.level_2[i][j].type = EMPTY;
                if(visited[i][j] == 0){
                    ajouterBuilding(world.level0[i][j].type, i, j, 3, 3);
                    game.flouz -= 1000;
                }
                for(int k = 0;k<3;k++){
                    for(int d = 0;d<3;d++) {
                        visited[i + k][j + d] = 1;
                    }
                }
            }else if(isWaterTower == 1){
                world.level0[i][j].type = WATER_TOWER;
                world.level_1[i][j].type = EMPTY;
                world.level_2[i][j].type = EMPTY;
                if(visited[i][j] == 0){
                    ajouterBuilding(world.level0[i][j].type,i, j, 4, 6);
                    game.flouz -= 100000;
                }
                for(int k = 0;k<4;k++){
                    for(int d = 0;d<6;d++) {
                        visited[i + k][j + d] = 1;
                    }
                }
            }else if(isPowerStation == 1){
                world.level0[i][j].type = POWER_STATION;
                world.level_1[i][j].type = EMPTY;
                world.level_2[i][j].type = EMPTY;
                if(visited[i][j] == 0){
                    ajouterBuilding(game, world.level0[i][j].type,i, j, 4, 6);
                    game.flouz -= 100000;
                }
                for(int k = 0;k<4;k++){
                    for(int d = 0;d<6;d++) {
                        visited[i + k][j + d] = 1;
                    }
                }
            }
        }
    }
    fclose(fp); // close the file
}

void initSim(){
    initWorld();
}

void renderHouse(){

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
                if(world.level0[i][j].type == EMPTY){
                    int x1 = i*CASE_X + 1;
                    int y1 = j*CASE_Y + 1;
                    int x2 = (i*CASE_X) + CASE_X - 1;
                    int y2 = (j*CASE_Y) + CASE_Y - 1;
                    //printf("Case (%d, %d) -> (%d, %d, %d, %d)\n", i, j, x1, y1, x2, y2);
                    rectfill(buffer, x1, y1, x2, y2, makecol(0, 255, 0));
                    //textprintf_ex(buffer,gfont,i*CASE_X + CASE_X/2,j*CASE_Y + CASE_Y/2,makecol(255,0,50),0,"(%d)",i);
                    //textout_ex(buffer,gfont,"A",100,65,makecol(120,200,255),0);
                }else  if(world.level0[i][j].type == ROAD){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    int x2 = (i*CASE_X) + CASE_X;
                    int y2 = (j*CASE_Y) + CASE_Y;
                    masked_blit(roadImage,buffer,0, 0, i*CASE_X, j*CASE_Y,20, 20);
                    //rectfill(buffer, x1, y1, x2, y2, makecol(255, 0, 0));
                }else  if(world.level0[i][j].type == HOUSE){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    for(int k = 0;k<3;k++){
                        for(int d = 0;d<3;d++) {
                            if (world.level0[i + k][j + d].type != HOUSE) {
                                allegro_message("Maison invalide");
                                allegro_exit();
                                exit(EXIT_FAILURE);
                            }
                            visited[i + k][j + d] = 1;
                        }
                    }
                    masked_blit(chantierImage,buffer,0, 0, x1, y1,60, 60);
                }else  if(world.level0[i][j].type == WATER_TOWER){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    for(int k = 0;k<4;k++){
                        for(int d = 0;d<6;d++) {
                            if (world.level0[i + k][j + d].type != WATER_TOWER) {
                                allegro_message("WATER_TOWER invalide");
                                allegro_exit();
                                exit(EXIT_FAILURE);
                            }
                            visited[i + k][j + d] = 1;
                        }
                    }
                    masked_blit(waterTowerImage,buffer,0, 0, x1, y1,80, 120);
                }else  if(world.level0[i][j].type == POWER_STATION){
                    int x1 = i*CASE_X;
                    int y1 = j*CASE_Y;
                    for(int k = 0;k<4;k++){
                        for(int d = 0;d<6;d++) {
                            if (world.level0[i + k][j + d].type != POWER_STATION) {
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
    if(mouse_x > 915 && mouse_x < 955 && mouse_y > 50 && mouse_y < 90){//contour route
        rect(buffer, 915, 50, 955, 90,makecol(255, 0, 0));
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 110 && mouse_y < 150){//contour maison
        rect(buffer, 915, 110, 955, 150,makecol(255, 0, 0));
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 170 && mouse_y < 230){//contour central electrique
        rect(buffer, 915, 170, 955, 230,makecol(255, 0, 0));
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 250 && mouse_y < 310) {//contour chateau d'eau
        rect(buffer, 915, 250, 955, 310, makecol(255, 0, 0));
    }else if(mouse_x > 915 && mouse_x < 955 && mouse_y > 330 && mouse_y < 390) {//contour caserne
        rect(buffer, 915, 330, 955, 390, makecol(255, 0, 0));
    }else if(mouse_x > 910 && mouse_x < 1019 && mouse_y > 470 && mouse_y < 500){
        rect(buffer, 910, 480, 1019, 500,makecol(255, 0, 0));
    }else if(mouse_x > 910 && mouse_x < 1019 && mouse_y > 520 && mouse_y < 550) {
        rect(buffer, 910, 520, 1019, 550, makecol(255, 0, 0));
    }else if(mouse_x > 910 && mouse_x < 1019 && mouse_y > 570 && mouse_y < 600) {
        rect(buffer, 910, 570, 1019, 600, makecol(255, 0, 0));
    }
}

void renderActions(BITMAP* buffer){
    //Palette
    //rect(buffer, 910, 20, 1020, 600, makecol(255, 255, 0));
    masked_blit(palette,buffer,0, 0, 910, 20,110, 580);

    // Icône route
    masked_blit(boiteaOutilroadImage,buffer,0, 0, 915, 50,40, 40);
    textprintf_ex(buffer,font,965,70, makecol(0,0,0),-1,"10EF");

    //Icône maison
    masked_blit(boiteaOutilhouseImage,buffer,0, 0, 915, 110,40, 40);
    textprintf_ex(buffer,font,965,130, makecol(0,0,0),-1,"1000EF");

    //Icône central electrique
    masked_blit(boiteaOutilpowerStationImage,buffer,0, 0, 915, 170,80, 120);
    textprintf_ex(buffer,font,965,210, makecol(0,0,0),-1,"100 000EF");

    //Icône chateau eau
    masked_blit(boiteaOutilwaterTowerImage,buffer,0, 0, 915, 250,80, 120);
    textprintf_ex(buffer,font,965,280, makecol(0,0,0),-1,"100 000EF");

    //Icône pompier
    masked_blit(boiteaOutilfireStation,buffer,0, 0, 915, 330,80, 120);
    textprintf_ex(buffer,font,965,360, makecol(0,0,0),-1,"10 000EF");

    //Scores
    rect(buffer, 20, 710, 800, 760, makecol(255, 255, 0));
}

void loadAssets(){
    roadImage = load_bitmap("../assets/route.bmp", NULL);
    chantierImage = load_bitmap("../assets/chantier.bmp", NULL);
    cabaneImage = load_bitmap("../assets/cabane.bmp", NULL);
    houseImage = load_bitmap("../assets/cabane.bmp", NULL);
    immeubleImage = load_bitmap("../assets/immeuble.bmp", NULL);
    gratteImage = load_bitmap("../assets/gratte.bmp", NULL);
    roadImage = load_bitmap("../assets/road.bmp", NULL);
    boiteaOutilroadImage=load_bitmap("../assets/roadboiteaoutil.bmp", NULL);
    boiteaOutilhouseImage = load_bitmap("../assets/cabanepalette.bmp", NULL);
    powerStationImage = load_bitmap("../assets/centraleelectrique.bmp", NULL);
    boiteaOutilpowerStationImage = load_bitmap("../assets/centraleelectriquepalette.bmp", NULL);
    waterTowerImage = load_bitmap("../assets/waterTower.bmp", NULL);
    boiteaOutilwaterTowerImage = load_bitmap("../assets/waterTowerpalette.bmp", NULL);
    fireStation= load_bitmap("../assets/caserne.bmp", NULL);
    boiteaOutilfireStation= load_bitmap("../assets/casernepalette.bmp", NULL);
    palette=load_bitmap("../assets/palette.bmp", NULL);

    if (!roadImage){
        allegro_message("pb route.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

volatile int counter = 0;      /* We'll increase this in the callback,
                                  so it must be volatile. */
void game_timer_callback()
{
    counter++;                 /* Nice and simple */
    int hours = counter/3600;
    int minutes = (counter - hours*3600)/60;
    int sec = counter - hours*3600 - minutes*60;

    //sprintf(gameTime, "%d:%d:%d", sec, minutes, hours);
}
END_OF_FUNCTION (game_timer_callback);   /* Note the syntax here */
LOCK_FUNCTION (game_timer_callback);    /* Lock the function */
LOCK_VARIABLE (counter);             /* It touches this variable,
                                        so we lock it too. */
void initRender(){
    loadAssets();
    bufferMap = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    initSim();
    init = 1;
    rectfill(bufferMap,0,0,SCREEN_WIDTH,SCREEN_HEIGH, makecol(0,0,0));
    renderGrid(bufferMap);
    renderWorld(bufferMap);
    install_int (game_timer_callback, 1000);
    renderActions(bufferMap);
    //textout_ex(buffer,font,"A",100,65,makecol(120,200,255),0);
    blit(bufferMap, screen, 0, 0, 0, 0, screen->w, screen->h);
}

void updateGame(BITMAP* buffer){
    game.electricity = 0;
    game.water = 0;
    game.citizens = 0;
    game.waterTowerNb = 0;
    game.powerStationNb = 0;
    game.housesNb = 0;
    struct BuildingNode *ptr = &game.buildings;
    while(ptr !=NULL){
        if(ptr->building.type == POWER_STATION){
            game.electricity += ptr->building.capacity;
            game.powerStationNb++;
        }
        if(ptr->building.type == WATER_TOWER){
            game.water += ptr->building.capacity;
            game.waterTowerNb++;
        }

        if(ptr->building.type == HOUSE){
            if(game.duration - ptr->building.createdAt>=15 && ptr->building.capacity == 0){
                game.flouz += ptr->building.capacity * 10;
                ptr->building.capacity = 10;
                ptr->building.updatedAt = game.duration;
                int x1 = ptr->building.x*CASE_X;
                int y1 = ptr->building.y*CASE_Y;
                masked_blit(cabaneImage,buffer,0, 0, x1, y1,60, 60);
            }else if(game.duration - ptr->building.updatedAt>=15 && ptr->building.capacity == 10){
                game.flouz += ptr->building.capacity * 10;
                ptr->building.capacity = 50;
                ptr->building.updatedAt = game.duration;
                int x1 = ptr->building.x*CASE_X;
                int y1 = ptr->building.y*CASE_Y;
                masked_blit(houseImage,buffer,0, 0, x1, y1,60, 60);
            }else if(game.duration - ptr->building.updatedAt>=15 && ptr->building.capacity == 50){
                game.flouz += ptr->building.capacity * 10;
                ptr->building.capacity = 100;
                ptr->building.updatedAt = game.duration;
                int x1 = ptr->building.x*CASE_X;
                int y1 = ptr->building.y*CASE_Y;
                masked_blit(immeubleImage,buffer,0, 0, x1, y1,60, 60);
            }else if(game.duration - ptr->building.updatedAt>=15 && ptr->building.capacity == 100){
                ptr->building.capacity = 1000;
                ptr->building.updatedAt = game.duration;
                int x1 = ptr->building.x*CASE_X;
                int y1 = ptr->building.y*CASE_Y;
                masked_blit(gratteImage,buffer,0, 0, x1, y1,60, 60);
            }
            game.citizens += ptr->building.capacity;
            game.housesNb++;
        }

        ptr = ptr->next;
    }
}

void renderBuilding(){

}

void render(){
    updateGame(bufferMap);
    clear_bitmap(buffer);
    blit(bufferMap, buffer, 0, 0, 0, 0, screen->w, screen->h);
    highlightCase(buffer);
    insertBuilding(bufferMap);

    //Affiche du temps de jeur
    int hours = counter/3600;
    int minutes = (counter - hours*3600)/60;
    int sec = counter - hours*3600 - minutes*60;
    char gameTime[128];
    sprintf(gameTime, "%02d:%02d:%02d", hours, minutes, sec);
    game.duration = counter;
    textprintf_ex(buffer,font,25,720,makecol(255,0,50),0,"Temps de jeu : %s", gameTime);

    //Affichage des Flouz
    textprintf_ex(buffer,font,400,720,makecol(255,0,50),0,"Flouz : %d", game.flouz);

    //Affichage du compteur habitants
    textprintf_ex(buffer,font,25,740,makecol(255,0,50),0,"Habitants : %d (%d)", game.citizens, game.housesNb);

    //Affichage du compteur eau
    textprintf_ex(buffer,font,260,740,makecol(255,0,50),0,"Eau : %d (%d)", game.water, game.waterTowerNb);

    //Affichage du compteur éléectricité
    textprintf_ex(buffer,font,400,740,makecol(255,0,50),0,"Electricité : %d (%d)", game.electricity, game.powerStationNb);

    blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);
}