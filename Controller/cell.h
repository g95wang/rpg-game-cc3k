#ifndef __CELL_H__
#define __CELL_H__

#include "observer.h"
#include "subject.h"
#include "object.h"
#include <memory>

class Cell : public Observer, public Subject{
  public:
    Cell( int x, int y, FloorType ft );
    void setObject( std::shared_ptr<Object> );
    std::shared_ptr<Object> getObject();
    int getChamberNum();
    void setChamberNum( int );
    bool isTile();
    bool isWalkable();
    Info getInfo() override;
    void notify( Subject & ) override;
    void setMoved( bool );
    bool getMoved();
  private:
    int x,y;
    ObjectType objectType;
    FloorType floorType;
    bool hidden;
    std::shared_ptr<Object> ob; //what is in the cell
    int chamberNum; //chamber index
    bool empty[9];
    bool moved;    
};

#endif
