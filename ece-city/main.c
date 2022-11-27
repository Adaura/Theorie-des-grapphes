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

int main() {
    initialisation_allegro();
    //BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //menu(buffer);
    run_once();
    allegro_exit();
    return 0;
}END_OF_MAIN();
