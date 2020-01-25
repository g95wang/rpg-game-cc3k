#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "stair.h"
#include "cell.h"
#include "textdisplay.h"
#include "player.h"
#include <vector>

class Up{};

class Floor{
  public:
    void attach();
    void initChamber();
    std::string spawnFloor( int, int, int );
    std::pair<int, int> randomPlace( std::shared_ptr<Object> );
    std::string usePotion( std::shared_ptr<Player>, int, int, DirectionType );
    std::string attackEnemy( std::shared_ptr<Player>, int, int, DirectionType );
    std::string movePlayer( std::string, std::shared_ptr<Player>, int &, int &, DirectionType );
    void moveEnemy( int, int, int, int );
    int getFloorNum();
    void setFloorNum( int );
    void print();
    void setValidCommand( bool );
    bool getValidCommand();
    void setHasBarrierSuit( bool );
    void initPlayer( std::shared_ptr<Player> &, int &, int & );
    void initProtector();
    std::string neighbourAttack( std::shared_ptr<Player>, int, int );
    friend std::istream & operator>>( std::istream &, Floor & );
  private:
    std::pair<int, int> decode( int, int, DirectionType );
    std::pair<int, int> randomSelectNeighbour( int, int );
    void moveObject( Cell & src, Cell & dst );
    void attach( Cell & );
    void spawnTreasure();
    void spawnPotion();
    void spawnEnemy( bool );
    std::shared_ptr<Stair> spawnStair();
    void spawnBarrierSuit();
    std::vector<std::vector<Cell>> cells;
    std::vector<Cell *> chamber[20];
    TextDisplay td;
    int chamberNum; //total number of chambers
    int floorNum;
    bool floorHasBarrierSuit;
    std::shared_ptr<Stair> s;
    int sX, sY;
    bool validCommand;
};

#endif
