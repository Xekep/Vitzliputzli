#ifndef ADVANCEDGRAPHICFUNCTIONS_H_INCLUDED
#define ADVANCEDGRAPHICFUNCTIONS_H_INCLUDED

#include "SDL/SDL.h"
#include <iostream>
//---------------------------------------------------------------------------
SDL_Surface *load_image( std::string filename );
//---------------------------------------------------------------------------
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
//---------------------------------------------------------------------------


#endif // ADVANCEDGRAPHICFUNCTIONS_H_INCLUDED
