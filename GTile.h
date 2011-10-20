#ifndef GTILE_H_INCLUDED
#define GTILE_H_INCLUDED
#include <iostream>
#include "SDL/SDL.h"
namespace level
{
//---------------------------------------------------------------------------
class GTile
{
    private:

    int type;
    SDL_Surface *tileSet;
    public:

    SDL_Rect tilePosition;    //позиция тайла на тайлшите
    SDL_Rect tileCoordinates; //позиция тайла на карте

    GTile() {};
    GTile(SDL_Surface *tileSheet, int xPos, int yPos);
    void SetCoordinates(int X, int Y) { tileCoordinates.x = X; tileCoordinates.y = Y; };
    void Draw(SDL_Surface *scr, SDL_Rect coord);
};
//---------------------------------------------------------------------------
}
#endif // GTILE_H_INCLUDED
