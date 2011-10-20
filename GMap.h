#ifndef GMAP_H_INCLUDED
#define GMAP_H_INCLUDED
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
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

    GMap();
    GMap(int mW, int mH);
    ~GMap();

    void MoveCamera(int dx, int dy, SDL_Surface *scr);
};
//---------------------------------------------------------------------------
}
#endif // GMAP_H_INCLUDED
