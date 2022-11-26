/*----------------------------------------------------------------
 * render.c -- Implémentation du moteur de rendu du jeu
 *----------------------------------------------------------------
 */
#include <stdio.h>
#include <allegro.h>
#include "render.h"
#include "assets.h"
#include "simulationvars.h"
#include "map.h"
#include "input.h"
#include "building.h"

static BITMAP *current, *background, *level0, *level1, *level2;

static void render_layout(BITMAP* buffer){
        //Palette
        //rect(buffer, 910, 20, 1020, 600, makecol(255, 255, 0));
        masked_blit(getAsset(ASSET_PALETTE_BACKGROUND),buffer,0, 0, 910, 20,110, 580);

        // Icône route
        masked_blit(getAsset(ASSET_PALETTE_ROAD),buffer,0, 0, 915, 50,40, 40);

        //Icône maison
        masked_blit(getAsset(ASSET_PALETTE_HOUSE),buffer,0, 0, 975, 50,40, 40);

        //Icône central electrique
        masked_blit(getAsset(ASSET_PALETTE_POWER_STATION),buffer,0, 0, 915, 130,80, 120);

        //Icône chateau eau
        masked_blit(getAsset(ASSET_PALETTE_WATER_TOWER),buffer,0, 0, 975, 130,80, 120);

        //Icône pompier
        masked_blit(getAsset(ASSET_PALETTE_FIRE_STATION),buffer,0, 0, 940, 210,80, 120);

        //Scores
        rect(buffer, 20, 710, 800, 760, makecol(255, 255, 0));
}

void render_grid(BITMAP* buffer){
    for (int i = 0; i < GRID_NB_X; i++)
    {
        for (int j = 0; j < GRID_NB_Y; j++)
        {
            rect(buffer, i*CASE_X, j*CASE_Y, (i*CASE_X) + CASE_X, (j*CASE_Y) + CASE_Y, makecol(255, 255, 255));
        }
    }
}

/* display_init:
 *  Called once, at the start of the game.
 */
void render_init() {
    assets_load();
    current = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    background = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    level0 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGH);
    render_layout(background);
    render_grid(background);
    map_init(current);

    blit(background, screen, 0, 0, 0, 0, screen->w, screen->h);
}

/* display_shutdown:
 *
 */
void render_shutdown() {
    destroy_bitmap (background);
    destroy_bitmap (level0);
    destroy_bitmap (level1);
    destroy_bitmap (level2);
}

//affichage des differents infomation comme le nombre d habitant ou l argent
void render_indicators(BITMAP *buffer, struct Game game){
    //Affiche du temps de jeur
    int hours = game.duration/3600;
    int minutes = (game.duration - hours*3600)/60;
    int sec = game.duration - hours*3600 - minutes*60;
    char gameTime[128];
    sprintf(gameTime, "%02d:%02d:%02d", hours, minutes, sec);
    textprintf_ex(buffer,font,25,720,makecol(255,0,50),0,"Temps de jeu : %s", gameTime);

    textprintf_ex(buffer,font,260,720,makecol(255,0,50),0,"Case (%02d, %02d)", mouseCoord->x+1, mouseCoord->y+1);

    //Affichage des Flouz
    textprintf_ex(buffer,font,400,720,makecol(255,0,50),0,"Flouz : %d", game.flouz);

    //Affichage du compteur habitants
    textprintf_ex(buffer,font,25,740,makecol(255,0,50),0,"Habitants : %d (%d)", game.citizens, game.housesNb);

    //Affichage du compteur eau
    textprintf_ex(buffer,font,260,740,makecol(255,0,50),0,"Eau : %d (%d)", game.water, game.waterTowerNb);

    //Affichage du compteur éléectricité
    textprintf_ex(buffer,font,400,740,makecol(255,0,50),0,"Electricité : %d (%d)", game.electricity, game.powerStationNb);

}

//mise en evidence du batiments selectionner dans la palette
void highlightCase(BITMAP* buffer, struct Game game){
    if(game.selectedBuilding != EMPTY && mouseCoord->selectionMode == GRID && game.currentLevel == 0){
        int x1 = mouseCoord->x*CASE_X;
        int y1 = mouseCoord->y*CASE_Y;
        int w = CASE_X;
        int h = CASE_Y;
        if(game.selectedBuilding == HOUSE){
            w = 3 * CASE_X;
            h = 3 * CASE_Y;
        }else if(game.selectedBuilding == WATER_TOWER || game.selectedBuilding == POWER_STATION|| game.selectedBuilding == FIRE_STATION){
            w = 4 * CASE_X;
            h = 6 * CASE_Y;
        }
        masked_blit(getAssetFromBuildingType(game.selectedBuilding),buffer,0, 0, x1, y1,w, h);
    }else if(mouseCoord->selectionMode == GRID){
            rectfill(buffer, mouseCoord->x*CASE_X, mouseCoord->y*CASE_Y, mouseCoord->x*CASE_X+CASE_X, mouseCoord->y*CASE_Y+CASE_Y, makecol(0, 200, 200));
    }

     if(game.selectedBuilding == ROAD){
        rect(buffer, 915, 50, 955, 90,makecol(255, 0, 0));
    }else if(game.selectedBuilding == HOUSE){
        rect(buffer, 975, 50, 1015, 90,makecol(255, 0, 0));
    }else if(game.selectedBuilding == POWER_STATION){
        rect(buffer, 915, 130, 955, 190,makecol(255, 0, 0));
    }else if(game.selectedBuilding == WATER_TOWER){
        rect(buffer, 975, 130, 1015, 190,makecol(255, 0, 0));
    }else if(game.selectedBuilding == FIRE_STATION) {
        rect(buffer, 940, 210, 980, 270, makecol(255, 0, 0));
    }

    if(game.currentLevel == 0) {
        rect(buffer, 910, 480, 1019, 510, makecol(255, 0, 0));}
    else if(game.currentLevel == 1) {
        rect(buffer, 910, 520, 1019, 550, makecol(255, 0, 0));
    }else if(game.currentLevel == 2) {
        rect(buffer, 910, 570, 1019, 600, makecol(255, 0, 0));
    }
}

//affichage des batiments
void draw_buildings(struct Game game, BITMAP* buffer){
    struct BuildingNode *ptr = &game.buildings;
    while (ptr != NULL) {
        //printf("###building ### %d, %d\n", ptr->building.type, ptr->building.x);
        int x1 = ptr->building.x*CASE_X;
        int y1 = ptr->building.y*CASE_Y;
        if (ptr->building.type == HOUSE) {
            if (ptr->building.capacity <= 9) {
                masked_blit(getAsset(ASSET_YARD),buffer,0, 0, x1, y1,60, 60);
            } else if (ptr->building.capacity <= 49) {
                masked_blit(getAsset(ASSET_CABANE),buffer,0, 0, x1, y1,60, 60);
            } else if (ptr->building.capacity <= 99) {
                masked_blit(getAsset(ASSET_HOUSE),buffer,0, 0, x1, y1,60, 60);
            } else if (ptr->building.capacity <= 999) {
                masked_blit(getAsset(ASSET_BUILDING),buffer,0, 0, x1, y1,60, 60);
            } else if (ptr->building.capacity > 10000) {
                masked_blit(getAsset(ASSET_SKYCRAPPER),buffer,0, 0, x1, y1,60, 60);
            }
        }else if (ptr->building.type == WATER_TOWER) {
            masked_blit(getAsset(ASSET_WATER_TOWER),buffer,0, 0, x1, y1,80, 120);
        }else if (ptr->building.type == POWER_STATION) {
            masked_blit(getAsset(ASSET_POWER_STATION),buffer,0, 0, x1, y1,80, 120);
        }else if (ptr->building.type == FIRE_STATION) {
            masked_blit(getAsset(ASSET_FIRE_STATION),buffer,0, 0, x1, y1,80, 120);
        }else if (ptr->building.type == ROAD) {
            masked_blit(getAsset(ASSET_ROAD),buffer,0, 0, x1, y1,20, 20);
        }

        if(ptr->building.type != EMPTY && !ptr->building.valid){
            rect(buffer, x1, y1, x1 + ptr->building.w*CASE_X, y1 + ptr->building.h*CASE_Y, makecol(255, 0, 0));
        }

        ptr = ptr->next;
    }
}

//debuf, utile en developpement
void debug(struct Game game, BITMAP* buffer){
    for (int i = 0; i < GRID_NB_X; i++) {
        for (int j = 0; j < GRID_NB_Y; j++) {
            textprintf_ex(buffer,font,i*CASE_X + 5,j*CASE_Y + 5,makecol(255,0,50),0,"%d", game.world.level0[i][j]);
        }
    }
}

/* display_update:
 *  This is called every cycle, to update the screen display.
 */
void render_update(struct Game game) {
    vsync();
    clear_bitmap(current);
    blit(background, current, 0, 0, 0, 0, screen->w, screen->h);
    //blit(level0, current, 0, 0, 0, 0, screen->w, screen->h);
    //objects_erase (arena, arena_bkgnd);
    //objects_draw (arena);
    render_indicators(background, game);
    map_update(current);
    highlightCase(current, game);
    draw_buildings(game, current);

    if(debugFlag == 0) debug(game, current);
    blit(current, screen, 0, 0, 0, 0, screen->w, screen->h);
}

