#ifndef _COMPASS_
#define _COMPASS_
#include "item.h"
#include "object.h"
#include "stair.h"
#include "enum.h"
#include <memory>

class Compass : public Item {
	std::shared_ptr<Stair> s;
public:
	Compass(std::shared_ptr<Stair> s);
	void displayStairs();
	ObjectType getObjectType() override;
	std::string useOn(std::shared_ptr<Player> p);
    char getOutputChar() override;
};

#endif
