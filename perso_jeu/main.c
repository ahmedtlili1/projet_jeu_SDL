#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <ctype.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Personne.h"


/** 
* @file main.c 
* @brief tache personne. 
* @author Zeineb Ben Khalifa 
* @version 0.3 
* @date Apr 01, 2021 
* 
* Testing program for perso * 
*/



int main()
{
  
Personne p,p1;
SDL_Surface *screen;
SDL_Surface *back;
int continuer=1,up=0, up1=0;
SDL_Event event;
int acceleration=0;
int deceleration=0;

int acceleration1=0;
int deceleration1=0;

Uint32 t_prev,t_fin , dt ;

SDL_Init(SDL_INIT_VIDEO);
screen=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
initPerso(&p);
initPerso(&p1);

back=IMG_Load("background.png");



while (continuer)
{
t_prev = SDL_GetTicks();

while(SDL_PollEvent(&event))
{
switch (event.type)
{
case SDL_QUIT:
    continuer=0;
    break;

case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case  SDLK_RIGHT:
        p.direction=0;
        p.vitesse=5;
        break;
    case  SDLK_LEFT:
        p.direction=1;
        p.vitesse=5;
        break; 
    case SDLK_UP:
        up=1;
        break;  
    case SDLK_p:
        acceleration=1;
    break;
    case SDLK_o:
        deceleration=1;
        break;

        
    case  SDLK_d:
        p1.direction=0;
        p1.vitesse=5;
        break;
    case  SDLK_q:
        p1.direction=1;
        p1.vitesse=5;
        break; 
    case SDLK_z:
        up1=1;
        break;  
    case SDLK_f:
        acceleration1=1;
    break;
    case SDLK_g:
        deceleration1=1;
        break;
    
    }
break;

case SDL_KEYUP:
switch (event.key.keysym.sym)//lbouton appuyé?
    {
    case  SDLK_RIGHT:
              p.vitesse=0;
        break;

    case  SDLK_LEFT:        
        p.vitesse=0;
        break; 

    case SDLK_UP:
        up=0;
        break; 

    case SDLK_p:
        acceleration=0;
    break;

    case SDLK_o:
        deceleration=0;
        break; 



        case  SDLK_d:
              p1.vitesse=0;
        break;

    case  SDLK_q:        
        p1.vitesse=0;
        break; 

    case SDLK_z:
        up1=0;
        break; 

    case SDLK_f:
        acceleration1=0;
    break;

    case SDLK_g:
        deceleration1=0;
        break;             
    
    }

break;
}
}
if (acceleration==1) p.acceleration = p.acceleration + 0.005 ;
if (deceleration==1) p.acceleration = p.acceleration - 0.01;

if (acceleration1==1) p1.acceleration = p1.acceleration + 0.005 ;
if (deceleration1==1) p1.acceleration = p1.acceleration - 0.01;

p.acceleration = p.acceleration - 0.001;
if (p.acceleration<0) p.acceleration =0;


p1.acceleration = p1.acceleration - 0.001;
if (p1.acceleration<0) p1.acceleration =0;


SDL_Delay(3);
t_fin=SDL_GetTicks();
dt=t_fin - t_prev ;

deplacerPerso(&p,dt);
animerPerso(&p);

deplacerPerso(&p1,dt);
animerPerso(&p1);

if (up==1) saut(&p);
p.position.y = p.position.y   + p.vitesse_saut ;
p.vitesse_saut = p.vitesse_saut + 10 ;
if (p.position.y>=300)
{   
    p.position.y=300;
    p.vitesse_saut=0;
}

if (up1==1) saut(&p1);
p1.position.y = p1.position.y   + p1.vitesse_saut ;
p1.vitesse_saut = p1.vitesse_saut + 10 ;
if (p1.position.y>=300)
{   
    p1.position.y=300;
    p1.vitesse_saut=0;
}


/*----------partie affichage---------*/
SDL_BlitSurface(back,NULL,screen,NULL);
afficherPerso(p,screen);
afficherPerso(p1,screen);
SDL_Flip(screen);

SDL_Delay(30);
}


    return 0;
}



