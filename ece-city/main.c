#include <allegro.h>
#include "ecegame.h"
#include "assets.h"

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

/*void menu(BITMAP* buffer){
    int verif;
    while(!key[KEY_ESC]) {
        while(verif==0) {
            blit(buffer,screen,0,0,0,0,screen->w,screen->h);
            blit(ville,buffer,0,0,0,0,1024, 768);
            masked_blit(NewG, buffer, 0, 0, 40, 40, NewG->w, NewG->h);
            masked_blit(reload, buffer, 0, 0, 40, 128, reload->w, reload->h);
            masked_blit(option, buffer, 0, 0, 40, 215, option->w, option->h);
            masked_blit(Exit, buffer, 0, 0, 40, 305, Exit->w, Exit->h);
            masked_blit(getAsset(ASSET_POWER_STATION),buffer,0,0,40,40,70,800);
            if(mouse_x>=40 && mouse_y>=40 && mouse_x<=40+NewG->w && mouse_y<=40+NewG->h){
                rect(buffer,40,40,40+NewG->w,40+NewG->h, makecol(255,0,0));
                if( mouse_b==1)
                    verif=1;
            }
            else if(mouse_x>=40 && mouse_y>=128 && mouse_x<=40+reload->w && mouse_y<=128+reload->h){
                rect(buffer,40,128,40+reload->w,128+reload->h, makecol(255,0,0));
                if( mouse_b==1)
                    verif=2;
            }
            else if(mouse_x>=40 && mouse_y>=215 && mouse_x<=40+option->w && mouse_y<=215+option->h){
                rect(buffer,40,215,40+option->w,215+option->h, makecol(255,0,0));
                if( mouse_b==1)
                    verif=3;
            }
            else if(mouse_x>=40 && mouse_y>=305 && mouse_x<=40+Exit->w && mouse_y<=305+Exit->h){
                rect(buffer,40,305,40+Exit->w,305+Exit->h, makecol(255,0,0));
                if( mouse_b==1)
                    verif=4;
            }
        }
        if(verif==1){
            run_once();
        }
        else if(verif==2){
            //recharcher une partie
        }
        else if(verif==3){
            blit(buffer,screen,0,0,0,0,screen->w,screen->w);
            blit(ville,buffer,0,0,0,0,1024, 768);
            textprintf_centre_ex(buffer,font,512,20, makecol(0,0,0),1,"Choisissez le mode de jeu que vous preferez");
            masked_blit(commu,buffer,0,0,40,80,commu->w,commu->h);
            masked_blit(capi,buffer,0,0,40,120,capi->w,capi->h);
        }
        else if(verif==4)
            allegro_exit();
        exit(EXIT_FAILURE);
    }
}*/

/*
int menu2(BITMAP* titre, BITMAP* image,BITMAP* ville,BITMAP* quitButton,BITMAP* quitButton2,BITMAP* playButton,BITMAP* playButton2,BITMAP* saveButton,BITMAP* saveButton2,BITMAP* buffer,int* a)///a pour charger la map
{
    rectfill(buffer,0,0,20,20, makecol(255,0,0));
    blit(ville,buffer,0,0,0,0,1024, 768);
    draw_sprite(buffer,playButton,400,330);
    draw_sprite(buffer,quitButton,400,630);
    draw_sprite(buffer,saveButton,400,480);
    draw_sprite(buffer,titre,40,80);
    ///Curseur sur bouton play
    if(mouse_x>=400 && mouse_y>=330 && mouse_x<= 622 && mouse_y<=438)
    {
        blit(ville,buffer,0,0,0,0,1024, 768);
        draw_sprite(buffer,titre,40,80);
        draw_sprite(buffer,playButton2,400,342);
        draw_sprite(buffer,quitButton,400,630);
        draw_sprite(buffer,saveButton,400,480);
        if (mouse_b == 1)
        {
            *a=1;
        }
    }

    ///Curseur sur bouton save
    if(mouse_x>=400 && mouse_y>=480 && mouse_x<= 622 && mouse_y<=588)
    {
        blit(ville,buffer,0,0,0,0,1024, 768);
        draw_sprite(buffer,titre,40,80);
        draw_sprite(buffer,playButton,400,330);
        draw_sprite(buffer,quitButton,400,630);
        draw_sprite(buffer,saveButton2,400,492);

        if (mouse_b == 1)
        {
            ///Lancer sauvegarde
        }
    }

    ///Curseur sur bouton quit
    if(mouse_x>=400 && mouse_y>=630 && mouse_x<= 622 && mouse_y<=738)
    {
        blit(ville,buffer,0,0,0,0,1024, 768);
        draw_sprite(buffer,titre,40,80);
        draw_sprite(buffer,playButton,400,330);
        draw_sprite(buffer,quitButton2,400,642);
        draw_sprite(buffer,saveButton,400,480);
        if(mouse_b==1)
        {
            allegro_exit();
            exit(0);
        }
    }
}
*/

int main() {
    initialisation_allegro();
    //BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //menu(buffer);
    
        /*
    BITMAP *image = load_bitmap("image.bmp", NULL);
    BITMAP *titre = load_bitmap("ECE CITY.bmp", NULL);
    BITMAP *ville = load_bitmap("backgroundfinal.bmp", NULL);
    BITMAP *quitButton = load_bitmap("quitButtonUnuse600.bmp", NULL);
    BITMAP *quitButton2 = load_bitmap("quitButtonUse600.bmp", NULL);
    BITMAP *playButton = load_bitmap("playButtonUnuse600.bmp", NULL);
    BITMAP *playButton2 = load_bitmap("playButtonUse600.bmp", NULL);
    BITMAP *saveButton = load_bitmap("saveButtonUnuse600.bmp", NULL);
    BITMAP *saveButton2 = load_bitmap("saveButtonUse600.bmp", NULL);
    BITMAP *capitalistButton = load_bitmap("capitalistButtonUnuse.bmp", NULL);
    BITMAP *capitalistButton2 = load_bitmap("capitalistButtonUse.bmp", NULL);
    BITMAP *communistButton = load_bitmap("communistButtonUnuse.bmp", NULL);
    BITMAP *communistButton2 = load_bitmap("communistButtonUse.bmp", NULL);
    BITMAP *modeDeJeu = load_bitmap("ModeDeJeu.bmp", NULL);
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //rectfill(buffer,0,0,20,20, makecol(255,0,0));//
    int b;
    int *a = &b;


    while (!key[KEY_ESC]) {

        if (*a != 1) {
            menu2(titre,image,ville, quitButton, quitButton2, playButton, playButton2, saveButton, saveButton2,buffer,a);
        }
        else if (*a == 1) {
            blit(ville,buffer,0,0,0,0,1024, 768);
            draw_sprite(buffer,modeDeJeu,20,80);
            draw_sprite(buffer,capitalistButton,90,280);
            draw_sprite(buffer,communistButton,90,530);
            if(mouse_x>=90 && mouse_y>=280 && mouse_x<= 622 && mouse_y<=460) {
                blit(ville,buffer,0,0,0,0,1024, 768);
                draw_sprite(buffer,modeDeJeu,20,80);
                draw_sprite(buffer,capitalistButton2,90,300);
                draw_sprite(buffer,communistButton,90,530);
                if (mouse_b == 1)
                {
                    ///Lancer mode capitaliste
                }
            }
            if(mouse_x>=90 && mouse_y>=530 && mouse_x<= 954 && mouse_y<=710) {
                blit(ville,buffer,0,0,0,0,1024, 768);
                draw_sprite(buffer,modeDeJeu,20,80);
                draw_sprite(buffer,capitalistButton,90,280);
                draw_sprite(buffer,communistButton2,90,550);
                if (mouse_b == 1)
                {
                    ///Lancer mode communiste
                }
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, screen->w, screen->h);
        */
    run_once();
    allegro_exit();
    return 0;
}END_OF_MAIN();
