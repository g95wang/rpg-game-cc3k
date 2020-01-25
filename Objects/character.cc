#include "character.h"
#include <iostream>
#include <string>

Character::Character(int hp, int atk, int def): HP{hp}, Atk{atk}, Def{def} {}

bool Character::isDead() {
	return (!HP);
}

bool Character::checkSuit() { 
	return false; 
}

void Character::addGold(int addedGold) {
	return;
}

void Character::setHostile() {
	return;
}

int Character::getHP() {
	return HP;
}

int Character::getDef() {
	return Def;
}

int Character::getAtk() {
	return Atk;
}

int Character::getGold() {
	return 0;
}

void Character::addHP(int addedHP) {
	HP += addedHP;
	if(HP < 0) HP = 0;
}

void Character::addDef(int addedDef) {
	Def += addedDef;
	if(Def < 0) Def = 0;
}

void Character::addAtk(int addedAtk) {
	Atk += addedAtk;
	if(Atk < 0) Atk = 0;
}

