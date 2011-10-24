#ifndef GMAP_H_INCLUDED
#define GMAP_H_INCLUDED
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
#endif // GMAP_H_INCLUDED
