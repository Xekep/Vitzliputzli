#include "SuperHero.h"
#include "LevelSettings.h"
#include "AdvancedGraphicFunctions.h"
//---------------------------------------------------------------------------
int statesOfStepHero[4] = {0, 32, 0, 64};
int stateOfStepHero = 0;
//---------------------------------------------------------------------------
level::GHero::GHero(std::string fileWithSprites, SDL_Rect pos)
{
    spritesOfHeroe = fileWithSprites;

    heroCoordinates.x = pos.x;
    heroCoordinates.y = pos.y;

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
void level::GHero::MoveHero()
{
    int stayOldX = heroCoordinates.x;

    heroCoordinates.x += spdX;
    if(heroCoordinates.x <= 0)
        heroCoordinates.x = 0;
    else if(heroCoordinates.x > level::mapWidth*level::tileWidth-level::tileWidth)
        heroCoordinates.x = level::mapWidth*level::tileWidth-level::tileWidth; //широта карты - широта спрайта персонажа

    if(stayOldX != heroCoordinates.x)
    {
        if(stayOldX < heroCoordinates.x)
        {
            stateHero |= HERO_RIGHT;
            stateHero &= ~HERO_LEFT;
        }
        else if(stayOldX > heroCoordinates.x)
        {
            stateHero |= HERO_LEFT;
            stateHero &= ~HERO_RIGHT;
        }

    }

    if((stateHero&JUMP_HERO) && (spdY+jmp < 16))
        jmp++;
    else if ((stateHero&JUMP_HERO) && (spdY+jmp >= 16))
    {
        stateHero &= ~JUMP_HERO;
        jmp = 0;
    }
    int stayOldY = heroCoordinates.y;
    heroCoordinates.y += (spdY + jmp);
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
        switch( evnt.keysym.sym )
        {
            case SDLK_SPACE: if(!(stateHero&(HERO_DOWN|JUMP_HERO))) { stateHero |= JUMP_HERO; jmp = -32; } break;
            case SDLK_LEFT: spdX = -8; break;
            case SDLK_RIGHT: spdX = 8; break;
        }
    }
    //If a key was released
    else if( evnt.type == SDL_KEYUP )
    {
        switch( evnt.keysym.sym )
        {
            case SDLK_LEFT: spdX = 0; break;
            case SDLK_RIGHT: spdX = 0; break;
        }
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

