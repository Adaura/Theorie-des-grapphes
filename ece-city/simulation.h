/*----------------------------------------------------------------
 * simulation.h -- Interface de simulation du jeu
 *----------------------------------------------------------------
 */

#ifndef gf_included_simulation_h
#define gf_included_simulation_h

#include "simulationvars.h"

void simulation_init(struct Game *game);
void simulation_update(struct Game *game);

#endif