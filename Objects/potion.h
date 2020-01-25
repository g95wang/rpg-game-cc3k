#ifndef _POTION_
#define _POTION_
#include "item.h"
#include "object.h"
#include <memory>
#include <string>

class Potion: public Item {
	ObjectType getObjectType() override;
    std::string useOn(std::shared_ptr<Player> p) = 0;
    char getOutputChar() override;
};

class RH: public Potion{
	std::string useOn(std::shared_ptr<Player> p);
};

class BA: public Potion{
	std::string useOn(std::shared_ptr<Player> p);
};

class BD: public Potion{
	std::string useOn(std::shared_ptr<Player> p);
};

class PH: public Potion{
	std::string useOn(std::shared_ptr<Player> p);
};

class WA: public Potion{
	std::string useOn(std::shared_ptr<Player> p);
};

class WD: public Potion{
	std::string useOn(std::shared_ptr<Player> p);
};

#endif
