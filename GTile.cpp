#include "GTile.h"
#include "SDL/SDL.h"
#include "AdvancedGraphicFunctions.h"
//---------------------------------------------------------------------------
level::GTile::GTile(int nt, int xPos, int yPos)
{
    numTile = nt;
    tilePosition.x = xPos;
    tilePosition.y = yPos;
    tilePosition.w = 32;
    tilePosition.h = 32;
}
//---------------------------------------------------------------------------

