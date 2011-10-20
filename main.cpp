#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "SDL/SDL.h"
#include "LevelSettings.h"
#include "GTimer.h"
#include "GTile.h"
#include "GMap.h"
#include "AdvancedGraphicFunctions.h"
#include "SuperHero.h"
#include <string>
#include <stdio.h>
//---------------------------------------------------------------------------
#define FPS 25
//---------------------------------------------------------------------------
const int SCREEN_WIDTH = 854;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 24;
//---------------------------------------------------------------------------
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet[4] = {NULL, NULL, NULL, NULL};

extern int trX[300];
extern int trY[300];

int sX = 0;
int sY = 0;
int speedX = 0;
int speedY = 0;
//---------------------------------------------------------------------------
int level::screenWidth = SCREEN_WIDTH;
int level::screenHeight = SCREEN_HEIGHT;
int level::tileWidth = 32;
int level::tileHeight = 32;
int level::mapWidth = 60;
int level::mapHeight = 30;
int level::tilesOnScreenWidth = 27;
int level::tilesOnScreenHeight = 15;
//---------------------------------------------------------------------------
level::GMap *levelMap;
level::GHero *fooHero;
//---------------------------------------------------------------------------
#if defined( __WIN32__ ) || defined( _WIN32 )
#include <windows.h>
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#elif defined( __linux__)
int main( int argc, char* args[] )
#else
#error "i don't know your Operating System! Abort! Abort! More aborts!"
#endif
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if( screen == NULL )
    {
        return 1;
    }

    SDL_WM_SetCaption( "Vitzliputzli", NULL );

    background = load_image( "Data/backgrounds/_background_003.bmp" );

    fooHero = new level::GHero("Data/hero/hero.bmp", (SDL_Rect){32, 640, 32, 32} );
    #include "lvl1_map.cpp" //карта уровня

    tileSheet[0] = load_image( "Data/tilesets/_tileset_001.bmp" );
    tileSheet[1] = load_image( "Data/tilesets/_tileset_002.bmp" );
    tileSheet[2] = load_image( "Data/tilesets/_tileset_003.bmp" );
    tileSheet[3] = load_image( "Data/tilesets/_tileset_004.bmp" );

    levelMap = new level::GMap(60, 30);

    for(int y = 0; y < 30; ++y)
    {
        for(int x = 0; x < 60; ++x )
        {
            if(tileMap[y][x] != -1)
            {
                level::GTile *tempTile = new level::GTile(tileSheet[tileSetsMap[y][x]], trX[tileMap[y][x]], trY[tileMap[y][x]]);
                tempTile->SetCoordinates(x*32, y*32);
                levelMap->map_w[y][x] = tempTile;
            }
        }
    }

    Timer fps;
    SDL_Event event;
    bool quit = false;
    while( quit == false )
    {
        fps.start();
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
                quit = true;
            fooHero->RePlace(event.key);

            if(event.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
        }
        apply_surface( 0, 0, background, screen );
        fooHero->MoveHero();
        levelMap->MoveCamera(fooHero->heroCoordinates.x, fooHero->heroCoordinates.y, screen);
        fooHero->DrawHero(screen, levelMap->framePosition);

        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        if( fps.get_ticks() < 1000 / FPS )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );
        }

    }
    delete levelMap;
    return 0;
}
//---------------------------------------------------------------------------
