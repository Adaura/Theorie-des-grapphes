#include <allegro.h>
#include "ecegame.h"

//initialistion allegro
void initialisation_allegro()
{
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)//message d erreur en cas de mauvaise ouverture
    {
        allegro_message("pb de gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}

//fonction eprmettant le bon fonctionnement du jeu
static void run_once(){
    ecegame_init();
    ecegame_run();
    ecegame_shutdown();

}

int main() {
    initialisation_allegro();
    run_once();
    allegro_exit();
    return 0;
}END_OF_MAIN();
