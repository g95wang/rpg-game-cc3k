#include "compass.h"

Compass::Compass(std::shared_ptr<Stair> s):s{s}{}

ObjectType Compass::getObjectType() { return ObjectType::Compass; }

std::string Compass::useOn(std::shared_ptr<Player> p){
	return p->useItem(this);
}

void Compass::displayStairs(){
	s->setHidden();
}

char Compass::getOutputChar(){
    return 'C';
}
