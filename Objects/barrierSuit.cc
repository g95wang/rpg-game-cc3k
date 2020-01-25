#include "barrierSuit.h"

std::string BarrierSuit::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}

ObjectType BarrierSuit::getObjectType(){return ObjectType::BarrierSuit;}

char BarrierSuit::getOutputChar(){return 'B';}

