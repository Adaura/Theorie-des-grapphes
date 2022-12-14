/*----------------------------------------------------------------
 * assets.h -- Interface de gestion des assets
 *----------------------------------------------------------------
 */

#ifndef gf_included_assets_h
#define gf_included_assets_h

#include <allegro.h>
#include "simulationvars.h"

//enum des differents batiments possible dans le jeu
enum ASSETS {
    ASSET_ROAD,
    //Les maisons
    ASSET_YARD,
    ASSET_CABANE,
    ASSET_HOUSE,
    ASSET_BUILDING,
    ASSET_SKYCRAPPER,
    //Batiments techniques
    ASSET_WATER_TOWER,
    ASSET_POWER_STATION,
    ASSET_FIRE_STATION,
    //Palette
    ASSET_PALETTE_BACKGROUND,
    ASSET_PALETTE_ROAD,
    ASSET_PALETTE_HOUSE,
    ASSET_PALETTE_WATER_TOWER,
    ASSET_PALETTE_POWER_STATION,
    ASSET_PALETTE_FIRE_STATION,
        };

void assets_load();
BITMAP *getAsset(enum ASSETS asset);
BITMAP *getAssetFromBuildingType(enum building type);
BITMAP *ville;
BITMAP *Exit;
BITMAP *option;
BITMAP *commu;
BITMAP *capi;
BITMAP *reload;
BITMAP *play;
BITMAP *stop;
BITMAP *NewG;
#endif