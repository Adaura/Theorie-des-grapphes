/*----------------------------------------------------------------
 * building.h -- Interface de gestion des batiments
 *----------------------------------------------------------------
 */

#ifndef gf_included_building_h
#define gf_included_building_h

#include <allegro.h>

void ajouterBuilding(struct Game *game, int x, int y, enum building type);
void building_init();
void building_shutdown();
void building_update(struct Game *game);


#endif