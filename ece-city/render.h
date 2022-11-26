/*----------------------------------------------------------------
 * render.h -- Moteur de rendu du jeu
 *----------------------------------------------------------------
 */

#ifndef gf_included_render_h
#define gf_included_render_h

#include "simulationvars.h"

void render_init();
void render_shutdown();
void render_update(struct Game game);


#endif