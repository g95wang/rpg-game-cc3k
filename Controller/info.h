#ifndef __INFO_H__
#define __INFO_H__

#include "enum.h"
#include "object.h"
#include <memory>

struct Info{
    int x,y;
    ObjectType objectType = ObjectType::Nothing;
    std::shared_ptr<Object> object;
    FloorType floorType;
    bool hidden = 0;
    int chamberNum = 0; //chamber index
};

#endif
