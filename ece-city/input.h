/*----------------------------------------------------------------
 * input.h -- Interface de gestion des inputs (souris et clavier)
 *----------------------------------------------------------------
 */

#ifndef gf_included_input_h
#define gf_included_input_h

#include "simulationvars.h"

extern struct Coord *mouseCoord;
extern int input_selectedLevel;
extern enum building input_selectedBuilding;

void input_init();
void input_shutdown();
void input_update();


#endif