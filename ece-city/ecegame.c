#include <allegro.h>
#include <stdio.h>
#include "ecegame.h"
#include "render.h"
#include "input.h"
#include "simulationvars.h"
#include "simulation.h"

/* gameEndFlag:
 * Indicateur de fin de jeu
 */
int gameEndFlag = 0;
int debugFlag = 0;
static struct Game game;

//Compteur de secondes pour le temps de jeu
volatile int counter = 0;
void game_timer_callback()
{
    counter++;
}
END_OF_FUNCTION (game_timer_callback);
LOCK_FUNCTION (game_timer_callback);
LOCK_VARIABLE (counter);
/* ecegame_init:
 *  This function sets everything up ready to play through the
 *  game once.
 */
void ecegame_init() {
    gameEndFlag = 0;
    install_int (game_timer_callback, 1000);
    input_init();
    simulation_init(&game);
    render_init();
    printf("### %d\n", game.flouz);
    //objects_init();
}

/* game_shutdown:
 *  Undo everything that game_init set up.
 */
void ecegame_shutdown() {
    //objects_shutdown();
    input_shutdown();
    render_shutdown();
}

/* game_run:
 *  This function actually plays the game.
 */
void ecegame_run() {
    while (!gameEndFlag) {
        game.duration = counter;
        input_update();
        //objects_update();
        simulation_update(&game);
        render_update(game);
        rest(40);
    }
}