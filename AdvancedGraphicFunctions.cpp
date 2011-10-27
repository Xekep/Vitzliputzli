#include "AdvancedGraphicFunctions.h"
//---------------------------------------------------------------------------
SDL_Surface *load_image( std::string filename )
{
    SDL_Surface *loadedImage = SDL_LoadBMP( filename.c_str() );
    if( loadedImage != NULL )
    {
        loadedImage = SDL_DisplayFormat( loadedImage );

        Uint32 colorkey = SDL_MapRGB( loadedImage->format, 0xFF, 0, 0xFF );
        SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, colorkey );
    }
    return loadedImage;
}
//---------------------------------------------------------------------------
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}
//---------------------------------------------------------------------------
