#include "item.h"

Item::Item(std::shared_ptr<Enemy> e):e{e} {}

void Item::setProtector(std::shared_ptr<Enemy> other){
	e = other;
}

std::shared_ptr<Enemy> Item::getProtector() {
	if( protectorDead() ) return nullptr;
    return e;
}

bool Item::protectorDead(){
	
    if(!e) return true;

    if (e->isDead()){
                e = nullptr;
                return true;
        } else {
                return false;
        }
}

