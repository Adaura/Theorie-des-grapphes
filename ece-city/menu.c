#include <allegro.h>
#include "simulationvars.h"

BITMAP *image;
BITMAP *titre;
BITMAP *quitButton;
BITMAP *quitButton2;
BITMAP *playButton;
BITMAP *playButton2;
BITMAP *saveButton;
BITMAP *saveButton2;
BITMAP *capitalistButton;
BITMAP *capitalistButton2;
BITMAP *communistButton;
BITMAP *communistButton2;
BITMAP *modeDeJeu;
BITMAP *ville;

int menu2(BITMAP *buffer, int *a)///a pour charger la map
{
    image = load_bitmap("../assets/image.bmp", NULL);
    titre = load_bitmap("../assets/ECE_CITY.bmp", NULL);
    quitButton = load_bitmap("../assets/quitButtonUnuse600.bmp", NULL);
    quitButton2 = load_bitmap("../assets/quitButtonUse600.bmp", NULL);
    playButton = load_bitmap("../assets/playButtonUnuse600.bmp", NULL);
    playButton2 = load_bitmap("../assets/playButtonUse600.bmp", NULL);
    saveButton = load_bitmap("../assets/saveButtonUnuse600.bmp", NULL);
    saveButton2 = load_bitmap("../assets/saveButtonUse600.bmp", NULL);
    capitalistButton = load_bitmap("../assets/capitalistButtonUnuse.bmp", NULL);
    capitalistButton2 = load_bitmap("../assets/capitalistButtonUse.bmp", NULL);
    communistButton = load_bitmap("../assets/communistButtonUnuse.bmp", NULL);
    communistButton2 = load_bitmap("../assets/communistButtonUse.bmp", NULL);
    modeDeJeu = load_bitmap("../assets/ModeDeJeu.bmp", NULL);
    ville= load_bitmap("../assets/backgroundfinal.bmp",NULL);

    rectfill(buffer, 0, 0, 20, 20, makecol(255, 0, 0));
    blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
    draw_sprite(buffer, playButton, 400, 330);
    draw_sprite(buffer, quitButton, 400, 630);
    draw_sprite(buffer, saveButton, 400, 480);
    draw_sprite(buffer, titre, 40, 80);
    ///Curseur sur bouton play
    if (mouse_x >= 400 && mouse_y >= 330 && mouse_x <= 622 && mouse_y <= 438) {
        blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
        draw_sprite(buffer, titre, 40, 80);
        draw_sprite(buffer, playButton2, 400, 342);
        draw_sprite(buffer, quitButton, 400, 630);
        draw_sprite(buffer, saveButton, 400, 480);
        if (mouse_b == 1) {
            *a = 1;
            rest(250);
        }
    }

    ///Curseur sur bouton save
    if (mouse_x >= 400 && mouse_y >= 480 && mouse_x <= 622 && mouse_y <= 588) {
        blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
        draw_sprite(buffer, titre, 40, 80);
        draw_sprite(buffer, playButton, 400, 330);
        draw_sprite(buffer, quitButton, 400, 630);
        draw_sprite(buffer, saveButton2, 400, 492);

        if (mouse_b == 1) {
            rest(250);
            ///Lancer sauvegarde
        }
    }

    ///Curseur sur bouton quit
    if (mouse_x >= 400 && mouse_y >= 630 && mouse_x <= 622 && mouse_y <= 738) {
        blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
        draw_sprite(buffer, titre, 40, 80);
        draw_sprite(buffer, playButton, 400, 330);
        draw_sprite(buffer, quitButton2, 400, 642);
        draw_sprite(buffer, saveButton, 400, 480);
        if (mouse_b == 1) {
            allegro_exit();
            exit(0);
        }
    }
}

void menu_update(struct Game *game){
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //rectfill(buffer,0,0,20,20, makecol(255,0,0));//
    int b;
    int *a = &b;


    while (!key[KEY_ESC] && !game->started) {
        if (*a != 1) {
            menu2(buffer, a);
        } else if (*a == 1) {
            //Temporser pour ne pas capturer le clic souris précédent
            blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
            draw_sprite(buffer, modeDeJeu, 20, 80);
            draw_sprite(buffer, capitalistButton, 90, 280);
            draw_sprite(buffer, communistButton, 90, 530);
            if (mouse_x >= 90 && mouse_y >= 280 && mouse_x <= 622 && mouse_y <= 460) {
                blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
                draw_sprite(buffer, modeDeJeu, 20, 80);
                draw_sprite(buffer, capitalistButton2, 90, 300);
                draw_sprite(buffer, communistButton, 90, 530);
                if (mouse_b & 1) {
                    ///Lancer mode capitaliste
                    game->started = true;
                    game->mode = CAPITALISME;
                }
            }
            if (mouse_x >= 90 && mouse_y >= 530 && mouse_x <= 954 && mouse_y <= 710) {
                blit(ville, buffer, 0, 0, 0, 0, 1024, 768);
                draw_sprite(buffer, modeDeJeu, 20, 80);
                draw_sprite(buffer, capitalistButton, 90, 280);
                draw_sprite(buffer, communistButton2, 90, 550);
                if (mouse_b & 1) {
                    ///Lancer mode communiste
                    game->started = true;
                    game->mode = CAPITALISME;
                }
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);
        rest(40);
    }
}