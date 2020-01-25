#include "stair.h"

Stair::Stair( bool h ):
    hidden{h} {}

ObjectType Stair::getObjectType() { return ObjectType::Stair; }

void Stair::setHidden() { hidden = false; }

bool Stair::getHidden() { return hidden; }

char Stair::getOutputChar() { return hidden ? '.' : '/'; }
