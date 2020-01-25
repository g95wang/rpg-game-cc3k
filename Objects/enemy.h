#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include "character.h"
using std::string;

class Enemy: public Character {
	bool compassHolder;
public:
	Enemy(bool compass, int hp, int atk, int def);
	void setCompassHolder();
	bool isCompassHolder();
	std::string attack(std::shared_ptr<Character> defender) override;
	ObjectType getObjectType() override;
	string getType() override;
	virtual void setHostile();
};

class Vampire: public Enemy {
public:
	Vampire(bool compass = 0, int hp = 50, int atk = 25, int def = 25);
	string attack(std::shared_ptr<Character> defender) override;
	string getType() override;
	char getOutputChar() override;
};

class Troll: public Enemy {
public:
	Troll(bool compass = 0, int hp = 120, int atk = 25, int def = 15);
	string attack(std::shared_ptr<Character> defender) override;
	string getType() override;
	char getOutputChar() override;
};

class Goblin: public Enemy {
public:
	Goblin(bool compass = 0, int hp = 70, int atk = 5, int def = 10);
	string attack(std::shared_ptr<Character> defender) override;
	string getType() override;
       	char getOutputChar() override;
};

class Merchant: public Enemy {
    static bool isHostile;
  public:
	Merchant(bool compass = 0, int hp = 30, int atk = 70, int def = 5);
	string getType() override;
	bool getHostile();
	void setHostile();
	std::string attack(std::shared_ptr<Character> defender) override;
       	char getOutputChar() override;
};

class Dragon: public Enemy {
public:
	Dragon(bool compass = 0, int hp = 150, int atk = 20, int def = 20);
	string getType() override;
	ObjectType getObjectType() override;
	char getOutputChar() override;
};

class Phoenix: public Enemy {
public:
	Phoenix(bool compass = 0, int hp = 50, int atk = 35, int def = 20);
	string getType();
	char getOutputChar() override;
};

class Werewolf: public Enemy {
public:
	Werewolf(bool compass = 0, int hp = 120, int atk = 30, int def = 5);
	string getType();
     	char getOutputChar() override;
};

#endif
