#ifndef _ITEM_
#define _ITEM_
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "enum.h"

class Item: public Object {
	protected:
	std::shared_ptr<Enemy> e;

	public:
    Item(std::shared_ptr<Enemy> e = nullptr);
	void setProtector(std::shared_ptr<Enemy> e);
	std::shared_ptr<Enemy> getProtector();
	bool protectorDead();
};

#endif
