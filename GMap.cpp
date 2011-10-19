#include "GMap.h"
#include "SDL/SDL.h"
//---------------------------------------------------------------------------
GMap::GMap(int mW, int mH)
{
    mapWidth = mW;
    mapHeight = mH;

    framePosition.x = 0;
    framePosition.y = 0;

    for(int i = 0; i < mH; ++i)
    {
        map_w.push_back(std::vector<GTile *>(0));
        for(int j = 0; j < mW; ++j)
        {
            map_w[i].push_back(NULL);
        }
    }
}
//---------------------------------------------------------------------------
GMap::~GMap()
{
	for(int i = 0; i < mapHeight; ++i)
	{
        for(std::vector<GTile *>::iterator j = map_w[i].begin(); j!= map_w[i].end(); ++j)
        {
            if(*j != NULL)
                delete (*j);
        }
        map_w[i].clear();
	}
    map_w.clear();
}
//---------------------------------------------------------------------------
void GMap::MoveCamera(int dx, int dy, SDL_Surface *scr)
{
    framePosition.x = dx - 427;
    if(framePosition.x <= 0) framePosition.x = 0;
    else if(framePosition.x >= 1066) framePosition.x = 1066; //широта_карты - широта_размера_окна

    framePosition.y = dy - 240;
    if(framePosition.y <= 0) framePosition.y = 0;
    else if(framePosition.y >= 480) framePosition.y = 480; //высота_карты - высота_размера_карты

    for(int i = framePosition.x/32; i < (framePosition.x+31)/32+27; ++i)
    {
        for(int j = framePosition.y/32; j < (framePosition.y+31)/32+15; ++j )
        {
            if(i >= map_w[j].size()) continue;
            if(map_w[j][i] != NULL)
            {
                map_w[j][i]->Draw(scr, framePosition);
            }
        }
    }
}
//---------------------------------------------------------------------------
