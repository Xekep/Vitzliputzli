#ifndef VITZLIPUTZLI_ADVANCEDGRAPHICFUNCTIONS_H_
#define VITZLIPUTZLI_ADVANCEDGRAPHICFUNCTIONS_H_

#include "SDL/SDL.h"
#include <iostream>
//---------------------------------------------------------------------------
SDL_Surface *load_image( std::string filename );
//---------------------------------------------------------------------------
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
//---------------------------------------------------------------------------


#endif // VITZLIPUTZLI_ADVANCEDGRAPHICFUNCTIONS_H_
