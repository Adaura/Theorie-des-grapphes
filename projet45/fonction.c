#include <stdio.h>
#include <allegro.h>
#define nblignes 35
#define nbcolonnes 45
#include "fonction.h"
// Created by David on 05/11/2022.
//



int affichage(BITMAP* image,BITMAP* ville,BITMAP* quitter,BITMAP* nouvellepartie,BITMAP* nouvellepartie2,BITMAP* sauvegarder,BITMAP* buffer,int* a)///a pour charger la map
{

    rectfill(buffer,0,0,20,20, makecol(255,0,0));
    blit(ville,buffer,0,0,0,0,1024, 768);
    blit(nouvellepartie,buffer,0,0,260,193,nouvellepartie->w,nouvellepartie->h);
    blit(quitter,buffer,0,0,260,383,quitter->w,quitter->h);
    blit(sauvegarder,buffer,0,0,660,193,sauvegarder->w,sauvegarder->h);

    if(mouse_x>=260 && mouse_y>=193 && mouse_x<= 522 && mouse_y<=285)
    {
        blit(nouvellepartie2,buffer,0,0,260,193,nouvellepartie->w,nouvellepartie->h);
        if (mouse_b == 1)
        {
            while(mouse_b==1){}
            *a=1;
        }


        }
    if(*a==1)
    {
        blit(image, buffer, 0, 0, 0, 0, 1024, 768);


    }


    if(mouse_x>=260 && mouse_y>=383 && mouse_x<= 459 && mouse_y<=468)
    {

        if(mouse_b==1)
        {
            while(mouse_b==1)
            {}
            allegro_exit();
            exit(0);
        }

    }
    //printf("(%d %d)",mouse_x,mouse_y);//



}

void quadrillage(BITMAP* buffer)
{
        for (int i = 0; i < nblignes; i++)
        {
            for (int j = 0; j < nbcolonnes; j++)
            {
                rect(buffer, i*20, j*20, (i*20) + 20, (j*20) + 20, makecol(0, 0, 0));
            }
        }

}
/*void matricemap()
{

    int taille=0;
    int matrice[nbcolonnes][nblignes]={0};

    int n,m;

    for(int i=0;i<nbcolonnes;i++)
    {
        for(int j=0;j<nblignes;j++)
        {

        }
    }
}*/



void route(BITMAP* buffer,int matrice[nblignes][nbcolonnes])
{
    for (int i = 0; i < nblignes; ++i)
    {
        for (int j = 0; j < nbcolonnes; ++j)
        {
            int x = i*20;
            int y = j*20;
            if(mouse_x >= x && mouse_x <= x+20 && mouse_y > y && mouse_y < y+20)
            {
                rect(buffer,x,y,x+20,y+20, makecol(255,0,0));
                if(mouse_b == 1)
                {
                    matrice[i][j] = 1;
                }
            }

        }
    }
    ///------------------------
    for (int i = 0; i < nblignes; ++i)
    {
        for (int j = 0; j < nbcolonnes; ++j)
        {
            int x = i*20;
            int y = j*20;
            if(matrice[i][j] == 1)
                rectfill(buffer,x,y,x+20,y+20, makecol(0,255,0));
        }

    }
}
