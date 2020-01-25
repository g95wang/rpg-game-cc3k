#include "player.h"
#include "enemy.h"
#include "enum.h"
#include "item.h"
#include "potion.h"
#include "treasure.h"
#include "barrierSuit.h"
#include "compass.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
using std::string;


Player::Player(int hp, int atk, int def): Character{hp, atk, def}, barrierSuit{0} {}

char Player::getOutputChar(){return '@';}

std::string Player::attack(std::shared_ptr<Character> defender) {
	int damage = ceil(((100 * getAtk()) / (100 + defender->getDef())));

	defender->addHP((-1) * damage);

	string damageAmount = std::to_string(damage);

	string s = this->getType() + " deals " + damageAmount + " damage to " + defender->getType();

	string defenderHP = std::to_string(defender->getHP());

	s = s + " (" + defenderHP + " HP)";
	s += ". ";

	//if merchant is attacked, then make all the merchants hostile
	if(defender->getType() == "Merchant") defender->setHostile();

	if(defender->getType() != "Dragon" && defender->getType() != "Merchant") {
		if(defender->isDead()) addGold(1);
	}

	if(defender->isDead()) s += defender->getType() + " died. ";

	return s;
}

ObjectType Player::getObjectType() { return ObjectType::Player; }

std::string Player::getType() { return "PC"; }

int Player::getGold() { return gold; }

void Player::addGold(int addedGold) {
	gold += addedGold;
	if(gold < 0) gold = 0;
}

void Player::wearSuit() { barrierSuit = 1; }

bool Player::checkSuit() { return barrierSuit; };

int Player::getPoint() {
	return gold;
}

string Player::useItem(RH * rh) {
	srand((time (NULL)));
	int addedHP = (rand() % 10) + 1;
	addHP(addedHP);
	std::string HP = std::to_string(addedHP);
	return "PC uses RH. HP increased by " + HP + ". ";
}

string Player::useItem(BA * ba) {
	addAtk(5);
	return "PC uses BA. Atk increased by 5. ";
}

string Player::useItem(BD * bd) {
	addDef(5);
	return "PC uses BD. Def increased by 5. ";
}

string Player::useItem(PH * ph) {
	srand((time (NULL)));
	int decHP = (rand() % 10) + 1;
	addHP((-1) * decHP);
	std::string HP = std::to_string(decHP);
	return "PC uses PH.HP decreased by " + HP + ". ";
}

string Player::useItem(WA * wa) {
	addAtk(-5);
	return "PC uses WA. Atk decreased by 5. ";
}

string Player::useItem(WD * wd) {
	addDef(-5);
	return "PC uses WD. Def decreased by 5. ";
}

string Player::useItem(Treasure * treasure) {
	int addedGold = treasure->getGoldNum();
	addGold(addedGold);
	string gold = std::to_string(addedGold);
	return "PC gets " + gold + " gold. ";
}

string Player::useItem(BarrierSuit * suit) {
	wearSuit();
	return "PC gets the Barrier Suit. ";
}

string Player::useItem(Compass * compass) {
	compass->displayStairs();
	return "PC gets the Compass. ";
}


Human::Human(int hp, int atk, int def): Player{hp, atk, def} {}

void Human::reset() {
	addAtk(20 - getAtk());
	addDef(20 - getDef());
}

int Human::getPoint() {
	return (getGold() * 2);
}

Dwarf::Dwarf(int hp, int atk, int def): Player{hp, atk, def} {}

void Dwarf::reset() {
	addAtk(20 - getAtk());
	addDef(30 - getDef());
}

/*string Dwarf::useItem(Treasure * treasure) {
	int addedGold = 2 * treasure->getGold();
	addGold(addedGold);
	string gold = std::to_string(addedGold);
	return "PC gets " + gold + " gold.";
}*/

Elves::Elves(int hp, int atk, int def): Player{hp, atk, def} {}

void Elves::reset() {
	addAtk(30 - getAtk());
	addDef(10 - getDef());
}

string Elves::useItem(PH * ph) {
	srand((time (NULL)));
	int addedHP = (rand() % 10) + 1;
	addHP(addedHP);
	return "PC uses PH. ";
}

string Elves::useItem(WA * wa) {
	addAtk(5);
	return "PC uses WA. ";
}

string Elves::useItem(WD * wd) {
	addDef(5);
	return "PC uses WD. ";
}

Orc::Orc(int hp, int atk, int def): Player{hp, atk, def} {}

void Orc::reset() {
	addAtk(30 - getAtk());
	addDef(25 - getDef());
}

/*string Orc::useItem(Treasure * treasure) {
	int addedGold = treasure->getGold() / 2;
	addGold(addedGold);
	string gold = std::to_string(addedGold);
	return "PC gets " + gold + " gold.";
}*/

Jia::Jia(int hp, int atk, int def): Player{hp, atk, def} {}

void Jia::reset() {
	addAtk(50 - getAtk());
	addDef(100 - getDef());
}
