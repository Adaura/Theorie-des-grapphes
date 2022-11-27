/*----------------------------------------------------------------
 * map.h -- Interface de gestion de la carte de jeu
 *----------------------------------------------------------------
 */

#ifndef gf_included_map_h
#define gf_included_map_h

#include <allegro.h>
#include "simulationvars.h"

void map_init(struct Game *game);
void map_shutdown();
void map_update(struct Game *game);


#endif