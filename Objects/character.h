#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include "object.h"
#include "enum.h"

class Character: public Object {
	int HP;
	int Atk;
	int Def;
public:
	Character(int hp, int atk, int def);
	bool isDead() override;
	int getHP();
	int getAtk();
	int getDef();
	virtual int getGold();
	void addHP(int addedHP);
	void addDef(int addedDef);
	void addAtk(int addedAtk);
	virtual void addGold(int addedGold);
	virtual bool checkSuit();
	virtual void setHostile();
	virtual std::string getType() = 0;
	virtual std::string attack(std::shared_ptr<Character> defender) = 0;
	virtual ObjectType getObjectType() = 0;
};

#endif
