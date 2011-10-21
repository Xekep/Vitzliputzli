#include "SuperHero.h"
#include "GMap.h"
#include "LevelSettings.h"
#include "AdvancedGraphicFunctions.h"
//---------------------------------------------------------------------------
int statesOfStepHero[4] = {0, 32, 0, 64};
int stateOfStepHero = 0;
//---------------------------------------------------------------------------
CollisionDetectWays MegaCollisionDetecter(SDL_Rect pos, int dX, int dY, level::tilesArray map);
//---------------------------------------------------------------------------
level::GHero::GHero(std::string fileWithSprites, SDL_Rect pos)
{
    spritesOfHeroe = fileWithSprites;

    heroCoordinates.x = pos.x;
    heroCoordinates.y = pos.y;

    heroCoordinates.w = pos.w;
    heroCoordinates.h = pos.h;

    heroSurface = load_image(spritesOfHeroe);

    spdX = 0;
    spdY = 16; //всегда падает
    jmp = 0;

    vrtlHeroPosition.x = 0;
    vrtlHeroPosition.y = 0;
    vrtlHeroPosition.h = 32;
    vrtlHeroPosition.w = 32;

    stateHero = HERO_RIGHT;
    stateOfStepHero = 0;
}
//---------------------------------------------------------------------------
void level::GHero::MoveHero(tilesArray map)
{
    CollisionDetectWays fPos = MegaCollisionDetecter(heroCoordinates, spdX, (spdY+jmp),  map);



    if(!fPos.LeftRight)
        heroCoordinates.x += spdX;
    else
    {
        if(heroCoordinates.x%32 != 0)
        {
            if(spdX < 0)
                heroCoordinates.x = map[0][heroCoordinates.x/32]->tileCoordinates.x;
            else if(spdX > 0)
                heroCoordinates.x = map[0][(heroCoordinates.x+heroCoordinates.w-1)/32]->tileCoordinates.x;
        }
    }

    if(heroCoordinates.x <= 0)
        heroCoordinates.x = 0;
    else if(heroCoordinates.x > level::mapWidth*level::tileWidth-level::tileWidth)
        heroCoordinates.x = level::mapWidth*level::tileWidth-level::tileWidth; //широта карты - широта спрайта персонажа

    if(spdX > 0)
    {
        stateHero |= HERO_RIGHT;
        stateHero &= ~HERO_LEFT;
    }
    else if(spdX < 0)
    {
        stateHero |= HERO_LEFT;
        stateHero &= ~HERO_RIGHT;
    }

    if((stateHero&JUMP_HERO) && (spdY+jmp < 16))
        jmp++;
    else if ((stateHero&JUMP_HERO) && ((spdY+jmp >= 16) || fPos.TopBottom))
    {
        stateHero &= ~JUMP_HERO;
        jmp = 0;
    }

    int stayOldY = heroCoordinates.y;

    if(!fPos.TopBottom)
        heroCoordinates.y += (spdY+jmp);
    else
    {
        if(heroCoordinates.y%32 != 0)
        {
            if((spdY+jmp) < 0)
                heroCoordinates.y = map[heroCoordinates.y/32][0]->tileCoordinates.y;
            else if((spdY+jmp) > 0)
                heroCoordinates.y = map[(heroCoordinates.y+heroCoordinates.h-1)/32][0]->tileCoordinates.y;
        }
    }

    if(heroCoordinates.y <= 0)
        heroCoordinates.y = 0;
    else if(heroCoordinates.y > level::mapHeight*level::tileHeight-level::tileHeight)
        heroCoordinates.y = level::mapHeight*level::tileHeight-level::tileHeight;

    if(stayOldY != heroCoordinates.y)
        stateHero |= HERO_DOWN;
    else
        stateHero &= ~HERO_DOWN;


    if(spdX)
    {
        stateOfStepHero++;
        if(stateOfStepHero >= 4) stateOfStepHero = 0;
    }
    else
        stateOfStepHero = 0;

}
//---------------------------------------------------------------------------
void level::GHero::RePlace(SDL_KeyboardEvent evnt)
{
    if( evnt.type == SDL_KEYDOWN )
    {
        if(evnt.keysym.sym == SDLK_SPACE)
        {
            if(!(stateHero&(HERO_DOWN|JUMP_HERO)))
            {
                stateHero |= JUMP_HERO;
                jmp = -32;
            }
        }
        if(evnt.keysym.sym == SDLK_LEFT)
            spdX = -8;
        else if(evnt.keysym.sym == SDLK_RIGHT)
            spdX = 8;
    }
    else if( evnt.type == SDL_KEYUP )
    {
        if((evnt.keysym.sym == SDLK_LEFT) || (evnt.keysym.sym == SDLK_RIGHT))
            spdX = 0;
    }
}
//---------------------------------------------------------------------------
void level::GHero::DrawHero(SDL_Surface *scr, SDL_Rect coord)
{

    if(stateHero&HERO_LEFT)
        vrtlHeroPosition.y = 32;
    else if(stateHero&HERO_RIGHT)
        vrtlHeroPosition.y = 0;

    vrtlHeroPosition.x = statesOfStepHero[stateOfStepHero];

    SDL_Rect tempRect;
    tempRect.x = heroCoordinates.x - coord.x;
    tempRect.y = heroCoordinates.y - coord.y;
    SDL_BlitSurface( heroSurface, &vrtlHeroPosition, scr, &tempRect );
}
//---------------------------------------------------------------------------
CollisionDetectWays MegaCollisionDetecter(SDL_Rect pos, int dX, int dY, level::tilesArray map)
{
    CollisionDetectWays cN = {false, false};

    if(map[pos.y/32][(pos.x+dX)/32] != NULL)
        cN.LeftRight = true;
    if(map[pos.y/32][(pos.x+pos.w+dX-1)/32] != NULL)
        cN.LeftRight = true;
    if(map[(pos.y+pos.h-1)/32][(pos.x+dX)/32] != NULL)
        cN.LeftRight = true;
    if(map[(pos.y+pos.h-1)/32][(pos.x+pos.w+dX-1)/32] != NULL)
        cN.LeftRight = true;


    if(map[(pos.y+dY)/32][pos.x/32] != NULL)
        cN.TopBottom = true;
    if(map[(pos.y+dY)/32][(pos.x+pos.w-1)/32] != NULL)
        cN.TopBottom = true;
    if(map[(pos.y+pos.h+dY-1)/32][pos.x/32] != NULL)
        cN.TopBottom = true;
    if(map[(pos.y+pos.h+dY-1)/32][(pos.x+pos.w-1)/32] != NULL)
        cN.TopBottom = true;


    return cN;
}
//---------------------------------------------------------------------------
