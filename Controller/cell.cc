#include "cell.h"

Cell::Cell( int x, int y, FloorType ft ):
    x{x}, y{y}, objectType{ObjectType::Nothing}, 
    floorType{ft}, hidden{false}, ob{nullptr},
    chamberNum{0} {
    
    for( int i = 0; i < 9; i++ ) empty[i] = 0;    
}

ObjectType getObjectType( std::shared_ptr<Object> ob ){
    if( ob.get() ) return ob -> getObjectType();
    else return ObjectType::Nothing;
}

Info Cell::getInfo(){
    return Info{x,y,objectType,ob,floorType,hidden,chamberNum};
}

void Cell::setObject( std::shared_ptr<Object> object ){
    ob = object;
    objectType = getObjectType( object );
    notifyObservers();
    moved = true;
}

std::shared_ptr<Object> Cell::getObject(){
    return ob;
}

int Cell::getChamberNum(){
    return chamberNum;
}

void Cell::setChamberNum( int n ){
    chamberNum = n;
}

//direction of (x2,y2) relative to (x1,y1)
//used for "empty" field in Cell
int getDirection( int x1, int y1, int x2, int y2 ){
    return 3 * (x2 - x1 + 1) + (y2 - y1 + 1);
}

bool Cell::isTile(){
    return floorType == FloorType::Tile ? true : false;
}

bool Cell::isWalkable(){
    return floorType == FloorType::NoAccess ? false : true;
}

void Cell::notify( Subject & whoFrom ){
    
    //used to initialize chamberNum
    if( chamberNum != whoFrom.getInfo().chamberNum ){
        chamberNum = whoFrom.getInfo().chamberNum;
        notifyObservers();
    }

    int x1 = x;
    int y1 = y;
    int x2 = whoFrom.getInfo().x;
    int y2 = whoFrom.getInfo().y;

    if( whoFrom.getInfo().objectType != ObjectType::Nothing ){
        empty[ getDirection( x1, y1, x2, y2 ) ] = false;
    }
    else{
        empty[ getDirection( x1, y1, x2, y2 ) ] = true;
    }
}

void Cell::setMoved( bool m ){
    moved = m;
}

bool Cell::getMoved(){
    return moved;
}
