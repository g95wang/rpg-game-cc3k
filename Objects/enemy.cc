#include "enemy.h"
#include <cstdlib>
#include <ctime>
#include <cmath>


Enemy::Enemy(bool compass, int hp, int atk, int def): Character{hp, atk, def}, compassHolder{compass} {}

ObjectType Enemy::getObjectType() {
	return ObjectType::Enemy;
}

void Enemy::setHostile() { return; }

void Enemy::setCompassHolder() { compassHolder = 1; }

bool Enemy::isCompassHolder() { return compassHolder; }

std::string Enemy::getType() { return ""; }

std::string Enemy::attack(std::shared_ptr<Character> defender) {
    int damage = std::ceil(((100.0 * getAtk()) / (100.0 + defender->getDef())));
    
    if(defender->checkSuit()) damage /= 2;
    
    srand((time (NULL))); 

    int miss = (rand() % 2);

    if(miss) {
        return this->getType() + " attacked PC but missed. ";
    } else {
	std::string damageAmount = std::to_string(damage);

        defender->addHP((-1) * damage);

        std::string s = this->getType() + " deals " + damageAmount + " damage to " + defender->getType() + ". ";
        
        return s;
    }
}


Vampire::Vampire(bool compass, int hp, int atk, int def): Enemy{compass, hp, atk, def} {}

std::string Vampire::attack(std::shared_ptr<Character> defender) {
    int damage = std::ceil(((100.0 * getAtk()) / (100.0 + defender->getDef())));
    
    if(defender->checkSuit()) damage /= 2;
    
    srand((time (NULL))); 

    int miss = (rand() % 2);

    srand((time (NULL)));

    int healthStolen = (rand() % 5) + 1;

    if(miss) {
        return this->getType() + " attacked PC but missed. ";
    } else {
	    std::string damageAmount = std::to_string(damage);
	    
	    defender->addHP((-1) * damage);

	    std::string s = this->getType() + " deals " + damageAmount + " damage to " + defender->getType() + ". ";
	    
	    if((getHP() + healthStolen) > 50) {
		    this->addHP(50 - getHP());
		    if((50 - getHP())) {
			this->addHP(50 - getHP());
		    	defender->addHP((-1) * (50 - getHP()));
		    	std::string stolen = std::to_string(50 - getHP());
			std::string HP = std::to_string(getHP());
		    	s += this->getType() + " stole " + stolen + " health points from PC (" + HP + " HP).";
		    }
	    } else {
		    this->addHP(healthStolen);
		    defender->addHP((-1) * healthStolen);
		    std::string stolen = std::to_string(healthStolen);
		    std::string HP = std::to_string(getHP());
		    s += this->getType() + " stole " + stolen + " health points from PC (" + HP + " HP).";
	    }

	    return s;
    }


}

std::string Vampire::getType() { return "Vampire"; }

char Vampire::getOutputChar() { return 'V'; }


Troll::Troll(bool compass, int hp, int atk, int def): Enemy{compass, hp, atk, def} {}

std::string Troll::attack(std::shared_ptr<Character> defender) {
    int damage = std::ceil(((100.0 * getAtk()) / (100.0 + defender->getDef())));
    
    if(defender->checkSuit()) damage /= 2;
    
    srand((time (NULL))); 

    int miss = (rand() % 2);

    srand((time (NULL)));

    int health = ((rand() % 5) + 1);

    if(miss) {
        return this->getType() + " attacked PC but missed. ";
    } else {
	    std::string damageAmount = std::to_string(damage);

	    defender->addHP((-1) * damage);
	    
	    std::string s = this->getType() + " deals " + damageAmount + " damage to " + defender->getType() + ". ";	   
	    
	    if((health + getHP()) > 120) health = 120 - getHP();
	    
	    if(health) {
		    addHP(health);
		    std::string HP = std::to_string(getHP());
		    std::string healthAdded = std::to_string(health);
		    s += this->getType() + " regenerates " + healthAdded + " health points (" +  HP + " HP).";
	    }
	    return s;
    }
}

std::string Troll::getType() { return "Troll"; }

char Troll::getOutputChar() { return 'T'; }


Goblin::Goblin(bool compass, int hp, int atk, int def): Enemy{compass, hp,atk, def} {}

std::string Goblin::attack(std::shared_ptr<Character> defender) {
    int damage = std::ceil(((100.0 * getAtk()) / (100.0 + defender->getDef())));
    
    if(defender->checkSuit()) damage /= 2;
    
    srand((time (NULL))); 

    int miss = (rand() % 2);

    srand((time (NULL)));

    int goldStolen = (rand() % 3) + 1;

    if(miss) {
        return this->getType() + " attacked PC but missed. ";
    } else {
	    std::string damageAmount = std::to_string(damage);

	    defender->addHP((-1) * damage);
	    
	    std::string s = this->getType() + " deals " + damageAmount + " damage to " + defender->getType() + ". ";

	    if(defender->getGold() < goldStolen) goldStolen = defender->getGold();
	    
	    if(defender->getGold()) { 
	    	defender->addGold((-1) * goldStolen);
		std::string gold = std::to_string(goldStolen);
		s += this->getType() + " stole " + gold + " gold from PC. ";
	    }
	    return s;
    }
}

std::string Goblin::getType() { return "Goblin"; }

char Goblin::getOutputChar() { return 'N'; }


bool Merchant::isHostile;

Merchant::Merchant(bool compass, int hp, int atk, int def): Enemy{compass, hp, atk, def} {}

std::string Merchant::getType() { return "Merchant"; }

bool Merchant::getHostile() { return isHostile; }

void Merchant::setHostile() { isHostile = 1; }

std::string Merchant::attack(std::shared_ptr<Character> defender) {
	if(getHostile()) {
        int damage = std::ceil(((100.0 * getAtk()) / (100.0 + defender->getDef())));
		
        if(defender->checkSuit()) damage /= 2;

		std::string damageAmount = std::to_string(damage);

        srand((time (NULL)));

        int miss = (rand() % 2);

        if(miss) {
            return this->getType() + "attacked PC but missed. ";
        } else {
        	defender->addHP((-1) * damage);

        	std::string s = this->getType() + " deals " + damageAmount + " damage to " + defender->getType() + ". ";
        
        	return s;
        }
	} else {
		return "";
	}
}

char Merchant::getOutputChar() { return 'M'; }


Dragon::Dragon(bool compass, int hp, int atk, int def): Enemy{compass, hp, atk, def} {}

std::string Dragon::getType() { return "Dragon"; }

ObjectType Dragon::getObjectType() { return ObjectType::Dragon; }

char Dragon::getOutputChar() { return 'D'; }



Phoenix::Phoenix(bool compass, int hp, int atk, int def): Enemy{compass, hp, atk, def} {}

std::string Phoenix::getType() { return "Phoenix"; }

char Phoenix::getOutputChar() { return 'X'; }



Werewolf::Werewolf(bool compass, int hp, int atk, int def): Enemy{compass, hp, atk, def} {}

std::string Werewolf::getType() { return "Werewolf";}

char Werewolf::getOutputChar() { return 'W'; }
