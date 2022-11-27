#include <allegro.h>
#include "assets.h"
#include "simulationvars.h"

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
BITMAP *ville;
BITMAP *Exit;
BITMAP *option;
BITMAP *commu;
BITMAP *capi;
BITMAP *reload;
BITMAP *play;
BITMAP *stop;
BITMAP *NewG;
BITMAP *fonddujeu;

//recuperation des bitmaps dans les fichiers
void assets_load(){
    roadImage = load_bitmap("../assets/road.bmp", NULL);
    chantierImage = load_bitmap("../assets/chantier.bmp", NULL);
    cabaneImage = load_bitmap("../assets/cabane.bmp", NULL);
    houseImage = load_bitmap("../assets/maison.bmp", NULL);
    immeubleImage = load_bitmap("../assets/immeuble.bmp", NULL);
    gratteImage = load_bitmap("../assets/gratte.bmp", NULL);
    boiteaOutilroadImage=load_bitmap("../assets/roadboiteaoutil.bmp", NULL);
    boiteaOutilhouseImage = load_bitmap("../assets/cabanepalette.bmp", NULL);
    powerStationImage = load_bitmap("../assets/centraleelectrique.bmp", NULL);
    boiteaOutilpowerStationImage = load_bitmap("../assets/centraleelectriquepalette.bmp", NULL);
    waterTowerImage = load_bitmap("../assets/waterTower.bmp", NULL);
    boiteaOutilwaterTowerImage = load_bitmap("../assets/waterTowerpalette.bmp", NULL);
    fireStation= load_bitmap("../assets/caserne.bmp", NULL);
    boiteaOutilfireStation= load_bitmap("../assets/casernepalette.bmp", NULL);
    palette=load_bitmap("../assets/palette.bmp", NULL);
    Exit= load_bitmap("../assets/exit.bmp", NULL);
    stop=load_bitmap("../assets/stop.bmp", NULL);
    option=load_bitmap("../assets/option.bmp", NULL);
    commu=load_bitmap("../assets/CommuMode.bmp", NULL);
    capi=load_bitmap("../assets/capMode.bmp", NULL);
    reload=load_bitmap("../assets/Reload.bmp", NULL);
    play=load_bitmap("../assets/play.bmp", NULL);
    NewG=load_bitmap("../assets/newG.bmp", NULL);
    ville= load_bitmap("../assets/backgroundfinal.bmp",NULL);
    fonddujeu=load_bitmap("../assets/fonddujeu.bmp",NULL);
    if (ville == NULL) {
        allegro_message("pb bmp");
        allegro_exit();
        exit(0);
    }
}

//en fonction de la bitampp on renvoi son equivalent
BITMAP *getAsset(enum ASSETS asset){
    if(asset == ASSET_ROAD) return roadImage;

    // Résidences
    if(asset == ASSET_YARD) return chantierImage;
    if(asset == ASSET_CABANE) return cabaneImage;
    if(asset == ASSET_HOUSE) return houseImage;
    if(asset == ASSET_BUILDING) return immeubleImage;
    if(asset == ASSET_SKYCRAPPER) return gratteImage;

    // Batiments techniques
    if(asset == ASSET_WATER_TOWER) return waterTowerImage;
    if(asset == ASSET_POWER_STATION) return powerStationImage;
    if(asset == ASSET_FIRE_STATION) return fireStation;

    //Palette
    if(asset == ASSET_PALETTE_BACKGROUND) return palette;
    if(asset == ASSET_PALETTE_ROAD) return boiteaOutilroadImage;
    if(asset == ASSET_PALETTE_HOUSE) return boiteaOutilhouseImage;
    if(asset == ASSET_PALETTE_WATER_TOWER) return boiteaOutilwaterTowerImage;
    if(asset == ASSET_PALETTE_POWER_STATION) return boiteaOutilpowerStationImage;
    if(asset == ASSET_PALETTE_FIRE_STATION) return boiteaOutilfireStation;

    //Menu
    if(asset == ASSET_MENU_CAPMODE) return capi;
    if(asset == ASSET_MENU_COMMMODE) return commu;
    if(asset == ASSET_MENU_EXIT) return Exit;
    if(asset == ASSET_MENU_NEWG) return NewG;
    if(asset == ASSET_MENU_OPTION) return option;
    if(asset == ASSET_MENU_PLAY) return play;
    if(asset == ASSET_MENU_RELOAD) return reload;
    if(asset == ASSET_MENU_STOP) return stop;
    if(asset == ASSET_MENU_VILLE) return ville;


    if(asset == ASSET_MENU_FONDDUJEU) return fonddujeu;

}

BITMAP *getAssetFromBuildingType(enum building type){
    if(type == ROAD) return getAsset(ASSET_ROAD);

    // Résidences
    if(type == HOUSE) return getAsset(ASSET_YARD);

    // Batiments techniques
    if(type == WATER_TOWER) return getAsset(ASSET_WATER_TOWER);
    if(type == POWER_STATION) return getAsset(ASSET_POWER_STATION);
    if(type == FIRE_STATION) return getAsset(ASSET_FIRE_STATION);
}