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
    framePosition.x = dx - level::screenWidth/2;
    if(framePosition.x <= 0)
        framePosition.x = 0;
    else if(framePosition.x >= level::mapWidth*level::tileWidth-level::screenWidth)
        framePosition.x = level::mapWidth*level::tileWidth-level::screenWidth; //широта_карты - широта_размера_окна

    framePosition.y = dy - level::screenHeight/2;
    if(framePosition.y <= 0)
        framePosition.y = 0;
    else if(framePosition.y >= level::mapHeight*level::tileHeight-level::screenHeight)
        framePosition.y = level::mapHeight*level::tileHeight-level::screenHeight; //высота_карты - высота_размера_карты

    for(int i = framePosition.x/level::tileWidth; i < (framePosition.x+level::tileWidth-1)/level::tileWidth+level::tilesOnScreenWidth; ++i)
    {
        for(int j = framePosition.y/level::tileHeight; j < (framePosition.y+level::tileHeight-1)/level::tileHeight+level::tilesOnScreenHeight; ++j )
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
