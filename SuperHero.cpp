#include "SuperHero.h"
#include "GMap.h"
#include "LevelSettings.h"
#include "AdvancedGraphicFunctions.h"
//---------------------------------------------------------------------------
int statesOfStepHero[4] = {0, 32, 0, 64};
int stateOfStepHero = 0;
//---------------------------------------------------------------------------
#define dx 9
#define dy 1
#define dw 14
#define dh 31
//---------------------------------------------------------------------------
CollisionDetectWays MegaCollisionDetecter(int dX, int dY, const level::tilesArray &map);
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

    stateHero |= HERO_RIGHT;
    stateOfStepHero = 0;
}
//---------------------------------------------------------------------------
void level::GHero::MoveHero(const tilesArray &map)
{
    CollisionDetectWays fPos;

/******************/
    fPos = MegaCollisionDetecter(heroCoordinates.x+spdX, heroCoordinates.y,  map);

    if(spdX < 0)
    {
        if(!fPos.cLeftBottom && !fPos.cLeftTop)
        {
            heroCoordinates.x += spdX;
            stateOfStepHero++;
            if(stateOfStepHero >= 4)
                stateOfStepHero = 0;
        }
        else
        {
            heroCoordinates.x = map[0][heroCoordinates.x/32]->tileCoordinates.x;
            stateOfStepHero = 0;
        }
    }
    else if(spdX > 0)
    {
        if(!fPos.cRightBottom && !fPos.cRightTop)
        {
            heroCoordinates.x += spdX;
            stateOfStepHero++;
            if(stateOfStepHero >= 4)
                stateOfStepHero = 0;
        }
        else
        {
            heroCoordinates.x = map[0][(heroCoordinates.x+heroCoordinates.w-1)/32]->tileCoordinates.x;
            stateOfStepHero = 0;
        }
    }
/***  TODO: в дальнейшем, когда карт будет много входы за пределы карты надо будет сделать переходом на другую карту  ***/

/********************/
    if(jmp < 0)
        jmp++;
    else if ((!stateHero&JUMP_HERO) || (jmp >= 0))
    {
        jmp = 0;
    }

    fPos = MegaCollisionDetecter(heroCoordinates.x, heroCoordinates.y+(spdY+jmp),  map);

    if((spdY+jmp) < 0)
    {
        if(!fPos.cRightTop && !fPos.cLeftTop)
        {
            heroCoordinates.y += (spdY+jmp);
            stateHero &= ~HERO_DOWN;
            stateHero |= JUMP_HERO;
        }
        else
        {
            heroCoordinates.y = map[heroCoordinates.y/32][0]->tileCoordinates.y;
            jmp = -spdY;
            stateHero &= ~JUMP_HERO;
            stateHero |= HERO_DOWN;
        }
    }
    else if((spdY+jmp) > 0)
    {
        if(!fPos.cRightBottom && !fPos.cLeftBottom)
        {
            heroCoordinates.y += (spdY+jmp);
            stateHero |= HERO_DOWN;
            stateHero &= ~JUMP_HERO;
        }
        else
        {
            heroCoordinates.y = map[(heroCoordinates.y+heroCoordinates.h-1)/32][0]->tileCoordinates.y;
            stateHero &= ~HERO_DOWN;
            stateHero &= ~JUMP_HERO;
        }
    }

/***  TODO: в дальнейшем, когда карт будет много входы за пределы карты надо будет сделать переходом на другую карту  ***/
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
                jmp = -33;
            }
        }
        if(evnt.keysym.sym == SDLK_LEFT)
        {
            spdX = -8;
            stateHero |= HERO_LEFT;
            stateHero &= ~HERO_RIGHT;
        }
        else if(evnt.keysym.sym == SDLK_RIGHT)
        {
            spdX = 8;
            stateHero |= HERO_RIGHT;
            stateHero &= ~HERO_LEFT;
        }
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
CollisionDetectWays MegaCollisionDetecter(int dX, int dY, const level::tilesArray &map)
{
    CollisionDetectWays cN = {false, false, false, false};

    if(map[dY/32][dX/32] != NULL)
        cN.cLeftTop = true;
    if(map[dY/32][(dX+31)/32] != NULL)
        cN.cRightTop = true;
    if(map[(dY+31)/32][dX/32] != NULL)
        cN.cLeftBottom = true;
    if(map[(dY+31)/32][(dX+31)/32] != NULL)
        cN.cRightBottom = true;

    return cN;
}
//---------------------------------------------------------------------------
