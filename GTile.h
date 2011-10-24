#ifndef GTILE_H_INCLUDED
#define GTILE_H_INCLUDED
#include <iostream>
#include "SDL/SDL.h"
namespace level
{
//---------------------------------------------------------------------------
class GTile
{
    public:
    int numTile;
    SDL_Rect tilePosition;    //позиция тайла на тайлшите
    SDL_Rect tileCoordinates; //позиция тайла на карте

    GTile(int nt, int xPos, int yPos);
    void SetCoordinates(int X, int Y) { tileCoordinates.x = X; tileCoordinates.y = Y; };
};
//---------------------------------------------------------------------------
}
#endif // GTILE_H_INCLUDED
