#ifndef SUPERHERO_H_INCLUDED
#define SUPERHERO_H_INCLUDED
#include <iostream>
#include "SDL/SDL.h"
#include "GTile.h"

const int HERO_LEFT  = (1 << 0); //Герой мордой влево
const int HERO_RIGHT = (1 << 1); //Герой мордой вправо
const int JUMP_HERO  = (1 << 2); //Герой в прыжке
const int HERO_DOWN  = (1 << 3); //Герой падает

//---------------------------------------------------------------------------
class GHero
{
    private:
    int spdX;
    int spdY;
    int jmp;
    std::string spritesOfHeroe;     //файл со спрайтами героя
    SDL_Surface *heroSurface;
    SDL_Rect realHeroCoordinates;   //Координаты прямоугольника, описанного вокруг героя, нужно для просчёта коллизий.
    SDL_Rect vrtlHeroPosition;
    int stateHero;                  //состояние героя
    public:
    SDL_Rect heroCoordinates;       //Координаты героя
    void MoveHero();
    void RePlace(SDL_KeyboardEvent evnt);
    GHero(std::string fileWithSprites, SDL_Rect pos);
    void DrawHero(SDL_Surface *scr, SDL_Rect coord);
};
//---------------------------------------------------------------------------
#endif // SUPERHERO_H_INCLUDED
