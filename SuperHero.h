#ifndef VITZLIPUTZLI_SUPERHERO_H_
#define VITZLIPUTZLI_SUPERHERO_H_
#include <iostream>
#include "SDL/SDL.h"
#include "GTile.h"
#include "GMap.h"

namespace level
{
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
    SDL_Rect vrtlHeroPosition;      //Координаты героя на большом спрайте
    int stateHero;                  //состояние героя
    public:
    SDL_Rect heroCoordinates;       //Координаты героя
    void MoveHero(const tilesArray &map);
    void RePlace(SDL_KeyboardEvent evnt);
    GHero(std::string fileWithSprites, SDL_Rect pos);
    void DrawHero(SDL_Surface *scr, SDL_Rect coord);
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
typedef struct
{
    bool cLeftTop;
    bool cLeftBottom;
    bool cRightTop;
    bool cRightBottom;

} CollisionDetectWays;
//---------------------------------------------------------------------------
#endif // VITZLIPUTZLI_SUPERHERO_H_
