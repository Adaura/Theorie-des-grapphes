#include <stdio.h>
#include <allegro.h>
#include "src/render/render.c"

void initialisation_allegro()
{
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("pb de gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}


int main() {
    initialisation_allegro();

    FILE *fp = fopen("../assets/SansS.pcx", "r");
    if (fp == NULL)
    {
        allegro_message("pb fichier font inexistant");
        allegro_exit();
        exit(EXIT_FAILURE);

    }else{
        fclose(fp); // close the file
    }

    while (!key[KEY_ESC]) {
       render();
    }

    allegro_exit();
    return 0;
}END_OF_MAIN();
