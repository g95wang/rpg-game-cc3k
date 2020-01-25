#include "potion.h"

ObjectType Potion::getObjectType(){return ObjectType::Potion;}

char Potion::getOutputChar(){return 'P';}

std::string RH::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}


std::string BA::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}


std::string BD::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}


std::string PH::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}


std::string WA::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}


std::string WD::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}


