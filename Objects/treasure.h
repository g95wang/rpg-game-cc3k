#ifndef _TREASURE_
#define _TREASURE_
#include "item.h"
#include "object.h"
#include <string>
#include <memory>

class Treasure: public Item{
	int goldNum;
	public:
	Treasure(int gold);
	ObjectType getObjectType() override;
	virtual int getGoldNum();
	std::string useOn(std::shared_ptr<Player> p) override;
    char getOutputChar() override;
};

class NormalHoard: public Treasure{
	public:
	NormalHoard(int gold = 1);
};

class SmallHoard: public Treasure{
	public:
	SmallHoard(int gold = 2);
};

class MerchantHoard: public Treasure{
	public:
	MerchantHoard(int gold = 4);
};

class DragonHoard: public Treasure{
	public:
	DragonHoard(int gold = 6);
};

#endif
