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