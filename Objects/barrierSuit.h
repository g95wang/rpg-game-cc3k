#ifndef _BARRIER_SUIT_
#define _BARRIER_SUIT_
#include "item.h"
#include "object.h"
#include <memory>

//the methods extends and need to implement:
//1, getObjectType() from object class
//2, setProtector (Enemy *) and protectorDead() from item class
//3, useOn(Play *) from item class
class BarrierSuit : public Item {
	ObjectType getObjectType();
	std::string useOn(std::shared_ptr<Player> p);
    char getOutputChar();
};
#endif
