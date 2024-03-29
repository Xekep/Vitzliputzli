#ifndef VITZLIPUTZLI_GMAP_H_
#define VITZLIPUTZLI_GMAP_H_
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include "SDL/SDL.h"
#include "GTile.h"
namespace level
{
typedef std::vector<std::vector<GTile *> > tilesArray;

//---------------------------------------------------------------------------
class GMap
{
    private:
    int mmapWidth;
    int mmapHeight;

    public:
    tilesArray map_w;
    SDL_Rect framePosition;

    std::vector<SDL_Surface *> tileSets;

    GMap(int mW, int mH);
    ~GMap();

    void MoveCamera(int dx, int dy, SDL_Surface *scr);
};
//---------------------------------------------------------------------------
}
#endif // VITZLIPUTZLI_GMAP_H_
