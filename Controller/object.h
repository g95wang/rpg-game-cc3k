#ifndef _OBJECT_
#define _OBJECT_

#include "enum.h"
#include <memory>

class Player;

class Object{
	public:
	virtual std::string useOn(std::shared_ptr<Player> p);
	virtual bool isDead();
	virtual ObjectType getObjectType() = 0;
    virtual char getOutputChar() = 0;
};
#endif
