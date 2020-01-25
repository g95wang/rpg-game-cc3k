#ifndef __ENUM_H__
#define __ENUM_H__

//This file is used mainly for generating output and spawning floor
//The enum classes does not span all the objects
//But only the ones that need to be spawned

#include <map>

enum class FloorType{
    Tile, //everyone can walk on
    Special, //only player can walk on
    NoAccess //no one can walk on
};

enum class ObjectType{
    Potion, Treasure, Enemy, //main type
    Dragon,
    Compass, Stair,          
    Player, BarrierSuit,  
    Nothing                  
};

enum class DirectionType{
    NW, N, NE, W, E, SW, S, SE
};

#endif
