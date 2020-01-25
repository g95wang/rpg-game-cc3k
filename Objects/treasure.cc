#include "treasure.h"

std::string Treasure::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}

ObjectType Treasure::getObjectType(){
	return ObjectType::Treasure;
}

Treasure::Treasure(int gold): goldNum{gold} {}

int Treasure::getGoldNum() {return goldNum;}

char Treasure::getOutputChar(){return 'G';}

NormalHoard::NormalHoard(int gold): Treasure{gold} {}

SmallHoard::SmallHoard(int gold): Treasure{gold} {}

MerchantHoard::MerchantHoard(int gold): Treasure{gold} {}

DragonHoard::DragonHoard(int gold): Treasure{gold} {}
