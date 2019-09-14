#include"../src/MapData.h"
MapData::MapData(int height, int width)
{
    for (int i = 0; i < height * width; ++i )
    {
        map.push_back(0);
        obstacleMap.push_back(0);
        healthMap.push_back(0);
        actHealthMap.push_back(0);

        this->width = width;

        this->height = height;
    }
}