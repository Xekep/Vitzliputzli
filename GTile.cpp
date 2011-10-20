#include "GTile.h"
#include "SDL/SDL.h"
#include "AdvancedGraphicFunctions.h"
//---------------------------------------------------------------------------
level::GTile::GTile(SDL_Surface *tileSheet, int xPos, int yPos)
{
    tileSet = tileSheet;
    tilePosition.x = xPos;
    tilePosition.y = yPos;
    tilePosition.w = 32;
    tilePosition.h = 32;
}
//---------------------------------------------------------------------------
void level::GTile::Draw(SDL_Surface *scr, SDL_Rect coord)
{
    SDL_Rect tempRect;
    tempRect.x = tileCoordinates.x - coord.x;
    tempRect.y = tileCoordinates.y - coord.y;
    SDL_BlitSurface( tileSet, &tilePosition, scr, &tempRect );
}
//---------------------------------------------------------------------------
