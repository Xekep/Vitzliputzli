#include "GMap.h"
#include "LevelSettings.h"
#include "SDL/SDL.h"
//---------------------------------------------------------------------------
level::GMap::GMap(int mW, int mH)
{
    mmapWidth = mW;
    mmapHeight = mH;

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
level::GMap::~GMap()
{
	for(int i = 0; i < mmapHeight; ++i)
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
void level::GMap::MoveCamera(int dx, int dy, SDL_Surface *scr)
{
    framePosition.x = dx - level::screenWidth/2/*427*/;
    if(framePosition.x <= 0)
        framePosition.x = 0;
    else if(framePosition.x >= (level::screenWidth-level::mapWidth*level::tileWidth)/*1066*/)
        framePosition.x = (level::screenWidth-level::mapWidth*level::tileWidth)/*1066*/; //широта_карты - широта_размера_окна

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
