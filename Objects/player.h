#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "character.h"
#include "enemy.h"
#include "enum.h"
#include <string>

class Item;

class Potion;

class RH;

class BA;

class BD;

class PH;

class WA;

class WD;

class Treasure;

class BarrierSuit;

class Compass;

class Player: public Character {
	int gold = 0;
	bool barrierSuit = 0;
public:
	Player(int hp, int atk, int def);
	std::string attack(std::shared_ptr<Character> defender) override;
	ObjectType getObjectType();
	string getType();
	int getGold() override;
	void addGold(int addedGold);
	void wearSuit();
	bool checkSuit() override;
	virtual void reset() = 0;
	virtual int getPoint();
	virtual std::string useItem(RH * rh);
	virtual std::string useItem(BA * ba);
	virtual std::string useItem(BD * bd);
	virtual std::string useItem(PH * ph);
	virtual std::string useItem(WA * wa);
	virtual std::string useItem(WD * wd);
	std::string useItem(Treasure * treasure);
	std::string useItem(BarrierSuit * suit);
	std::string useItem(Compass * compass);
    char getOutputChar() override;
};


class Human: public Player {
public:
	Human(int hp = 140, int atk = 20, int def = 20);
	void reset() override;
	int getPoint() override;
};

class Dwarf: public Player {
public:
	Dwarf(int hp = 100, int atk = 20, int def = 30);
//	std::string useItem(Treasure * treasure) override;
	void reset() override;
};

class Elves: public Player {
public:
	Elves(int hp = 140, int atk = 30, int def = 10);
	std::string useItem(PH * ph) override;
	std::string useItem(WA * wa) override;
	std::string useItem(WD * wd) override;
	void reset() override;
};

class Orc: public Player {
public:
	Orc(int hp = 180, int atk = 30, int def = 25);
//	std::string useItem(Treasure * treasure) override;
	void reset() override;
};

class Jia: public Player {
public:
	Jia(int hp = 1000, int atk = 50, int def = 100);
	void reset() override;
};

#endif
