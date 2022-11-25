#include <stdio.h>
#include <allegro.h>
#include "src/render/render.c"
#define ATTENDRE(temps) Sleep(temps*1000)

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

/*void date(){
    time_t secondes;
    struct tm instant;//structure pres def dans time.h avec en elements l'année le mois le jour etc

    time(&secondes);
    instant=*localtime(&secondes);

    printf("%d/%d/%d ; %d:%d:%d\n", instant.tm_mday, instant.tm_mon+1,instant.tm_year+1900, instant.tm_hour, instant.tm_min, instant.tm_sec);
    printf("%s\n", ctime(&secondes));
    printf("%0.lf secondes\n",difftime(instant, t0));
}*/

int main() {
    //time_t t0;
    //time(&t0);
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

    initRender();

    while (!key[KEY_ESC]) {
       render();
       rest(40);
    }

    allegro_exit();
    return 0;
}END_OF_MAIN();
