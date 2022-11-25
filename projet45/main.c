#include <stdio.h>
#include <allegro.h>
#include "fonction.h"
#define nblignes 35
#define nbcolonnes 45



void initialisation_allegro()
{
    allegro_init();
    install_keyboard();
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
    int matrice[nblignes][nbcolonnes] = {0};
    BITMAP *image = load_bitmap("image.bmp", NULL);
    BITMAP *ville = load_bitmap("ville.bmp", NULL);
    BITMAP *quitter = load_bitmap("quitter.bmp", NULL);
    BITMAP *nouvellepartie = load_bitmap("new.bmp", NULL);
    BITMAP *nouvellepartie2 = load_bitmap("new2.bmp", NULL);

    BITMAP *sauvegarder = load_bitmap("sauvegarder.bmp", NULL);
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //rectfill(buffer,0,0,20,20, makecol(255,0,0));//
    int b;
    int *a = &b;


    while (!key[KEY_ESC]) {

        if (*a != 1)
            affichage(image, ville, quitter, nouvellepartie, nouvellepartie2, sauvegarder, buffer, a);
        else if (*a == 1) {
            quadrillage(buffer);

            ///------------------------------------
            600(buffer,matrice);


        }

        blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);
    }







allegro_exit();
    return 0;
}END_OF_MAIN();
