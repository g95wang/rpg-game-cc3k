#ifndef __GAME_H__
#define __GAME_H__

#include "floor.h"
#include <memory>
#include <iostream>
#include <fstream>

class Game{
  public:
    Game( int floorNum = 5 );
    void beginGame();
    void loadGame( std::string );
  private:
    void print();
    void getCommand();
    void getPlayer();
    void initFloor( std::ifstream & );
    void loop( std::ifstream & );
    void end();
    void initLoad();
    void loopLoad( std::ifstream & );
    void getNumbers();
    Floor floor;
    std::shared_ptr<Player> player;
    std::string msg;
    std::string race;
    int playerX, playerY; //coordinates of the player
    int floorNum; //how many floors in this game:
    int BSFloorNum; //which floor has BarrierSuit
    int PotionNum = 10;
    int TreasureNum = 10;
    int EnemyNum = 20;
};

#endif
