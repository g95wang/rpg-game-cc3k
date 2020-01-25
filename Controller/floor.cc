#include "compass.h"
#include "floor.h"
#include "enum.h"
#include "stair.h"
#include "treasure.h"
#include "enemy.h"
#include "potion.h"
#include "barrierSuit.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <utility>

void Floor::setFloorNum( int num ){
    floorNum = num;
}

void Floor::setValidCommand( bool v ){
    validCommand = v;
}

bool Floor::getValidCommand(){
    return validCommand;
}

void Floor::setHasBarrierSuit( bool b ){
    floorHasBarrierSuit = b;
}

std::pair<int, int> Floor::decode( int x, int y, DirectionType dt ){
    
    switch( dt ){
        case DirectionType::N:
            return std::make_pair( x-1, y );
        case DirectionType::NW:
            return std::make_pair( x-1, y-1 );
        case DirectionType::NE:
            return std::make_pair( x-1, y+1 );
        case DirectionType::W:
            return std::make_pair( x, y-1 );
        case DirectionType::E:
            return std::make_pair( x, y+1 );
        case DirectionType::SW:
            return std::make_pair( x+1, y-1 );
        case DirectionType::SE:
            return std::make_pair( x+1, y+1 );
        case DirectionType::S:
            return std::make_pair( x+1, y );
    }
    return std::make_pair( x, y );
}

void Floor::initPlayer( std::shared_ptr<Player> & p, int & x, int & y ){
    int c1 = cells.size();

    for( int i = 0; i < c1; i++ ){
        int c2 = cells[i].size();

        for( int j = 0; j < c2; j++ ){
            if( cells[i][j].getInfo().objectType == ObjectType::Player ){
                cells[i][j].setObject( p );
                x = i;
                y = j;
                return;
            }
        }
    }
}

void Floor::initProtector(){
    int c1 = cells.size();

    for( int i = 0; i < c1; i++ ){
        int c2 = cells[i].size();

        for( int j = 0; j < c2; j++ ){
            if( dynamic_cast<BarrierSuit *>(cells[i][j].getObject().get()) ){
                for( int k = 0; k < 8; k++ ){
                    std::pair<int, int> p = decode( i, j, static_cast<DirectionType>(k) );
                    if( cells[p.first][p.second].getInfo().objectType == ObjectType::Dragon ){
                        std::dynamic_pointer_cast<Item>(cells[i][j].getObject()) -> setProtector( std::dynamic_pointer_cast<Enemy>(cells[p.first][p.second].getObject()) );
                    }
                }    
            }
            if( dynamic_cast<DragonHoard *>(cells[i][j].getObject().get()) ){
                for( int k = 0; k < 8; k++ ){
                    std::pair<int, int> p = decode( i, j, static_cast<DirectionType>(k) );
                    if( cells[p.first][p.second].getInfo().objectType == ObjectType::Dragon ){
                        std::dynamic_pointer_cast<Item>(cells[i][j].getObject()) -> setProtector( std::dynamic_pointer_cast<Enemy>(cells[p.first][p.second].getObject()) );
                    }
                }
            }
        }
    }
}

std::string Floor::usePotion( std::shared_ptr<Player> p, int x, int y, DirectionType dt ){
    std::string errorMsg = "No potion detected.";
    std::pair<int, int> coordinate = decode( x, y, dt );
    int i = coordinate.first, j = coordinate.second;
    int c1 = cells.size();

    if( i < 0 || i >= c1 ){
        return errorMsg;
    }

    int c2 = cells[i].size();

    if( j < 0 || j >= c2 ){
        return errorMsg;
    }

    if( cells[i][j].getInfo().objectType != ObjectType::Potion ){
        return errorMsg;
    }

    std::string msg = cells[i][j].getObject() -> useOn( p ); 
    cells[i][j].setObject( nullptr );
    validCommand = true;
    return msg;
}

std::string Floor::attackEnemy( std::shared_ptr<Player> p, int x, int y, DirectionType dt ){
    std::string errorMsg = "No enemy detected.";
    std::pair<int, int> coordinate = decode( x, y, dt );
    int i = coordinate.first, j = coordinate.second;
    int c1 = cells.size();

    if( i < 0 || i >= c1 ){
        return errorMsg;
    }

    int c2 = cells[i].size();

    if( j < 0 || j >= c2 ){
        return errorMsg;
    }

    if( cells[i][j].getInfo().objectType != ObjectType::Enemy && cells[i][j].getInfo().objectType != ObjectType::Dragon ){
        return errorMsg;
    }

    std::string msg =  p -> attack( std::dynamic_pointer_cast<Character>( cells[i][j].getObject() ) );
    
    if( cells[i][j].getObject() -> isDead() ){
        if( std::dynamic_pointer_cast<Enemy>(cells[i][j].getObject()) -> isCompassHolder() ){
            cells[i][j].setObject( std::make_shared<Compass>(s) );
        }
        else if ( std::dynamic_pointer_cast<Enemy>(cells[i][j].getObject()) -> getType() == "Merchant" ){
            cells[i][j].setObject( std::make_shared<MerchantHoard>() );
        }
        else cells[i][j].setObject( nullptr );
    }
    validCommand = true;
    return msg;
}

std::string Floor::movePlayer( std::string command, std::shared_ptr<Player> p, int & x, int & y, DirectionType dt ){
    std::string errorMsg = "The cell has something on it.";
    std::pair<int, int> coordinate = decode( x, y, dt );
    int i = coordinate.first, j = coordinate.second;
    int c1 = cells.size();
    if( i < 0 || i >= c1 ){
        return errorMsg;
    }

    int c2 = cells[i].size();

    if( j < 0 || j >= c2 ){
        return errorMsg;
    }

    if( cells[i][j].getInfo().objectType == ObjectType::Potion
     || cells[i][j].getInfo().objectType == ObjectType::Enemy
     || cells[i][j].getInfo().objectType == ObjectType::Dragon){
        return errorMsg;
    }

    if( cells[i][j].getInfo().floorType == FloorType::NoAccess ){
        return errorMsg;
    }
    
    if( cells[i][j].getInfo().objectType == ObjectType::Stair ){
        throw Up{};
    }

    std::string msg = "Player moved to " + command + ". ";

    if( cells[i][j].getObject() ){
       if(  std::dynamic_pointer_cast<Item>(cells[i][j].getObject()) -> protectorDead() ){
            msg += cells[i][j].getObject() -> useOn( p );
       }
       else return errorMsg;
    }
    cells[i][j].setObject( p );
    cells[x][y].setObject( nullptr );
    x = i;
    y = j;
    validCommand = true;
    return msg;
}

void Floor::attach( Cell & c ){
    int x = c.getInfo().x;
    int y = c.getInfo().y;

    for( int i = x - 1; i <= x + 1; i++ ){
        for( int j = y - 1; j <= y + 1; j++ ){
            int c1 = cells.size(), c2 = cells[i].size();

            if( i >= 0 && j >= 0 && i < c1 && j < c2 ){
                c.attach( & cells[i][j] );
            }
        }
    }
    c.attach( & td );
}

void Floor::attach(){
    int c1 = cells.size();

    for( int i = 0; i < c1; i++ ){
        int c2 = cells[i].size();

        for( int j = 0; j < c2; j++ ){
            if( cells[i][j].getInfo().floorType == FloorType::Tile ){
                attach( cells[i][j] );
            }
            else cells[i][j].attach( & td );
        }
    }
}

void Floor::initChamber(){
    int index = 0;
    
    for(int i = 0; i < 20; i++ ){
        chamber[i].clear();
    }    

    for( auto &p : cells ){
        for( auto &q : p ){
            if( q.getInfo().floorType != FloorType::Tile ) continue;

            if( ! q.getChamberNum() ){
                q.setChamberNum( ++index );
                q.notifyObservers();
                chamber[index].emplace_back( &q );
            }
            else{
                q.notifyObservers();
                chamber[q.getChamberNum()].emplace_back( &q );
            }
        }
    }
    chamberNum = index;
}

std::pair<int, int> Floor::randomSelectNeighbour( int x, int y ){
    int num = 0;
    
    for( int i = 0; i < 8; i++ ){
        std::pair<int, int> coor = decode( x, y, static_cast<DirectionType>(i) );
        int newX = coor.first, newY = coor.second;
        if( cells[newX][newY].isTile() && ! cells[newX][newY].getObject() ){
            num++;
        }
    }

    if( num == 0 ) return std::make_pair( x, y );

    srand( time(NULL) );
    int index = rand() % num;
    
    for( int i = 0; i < 8; i++ ){
        std::pair<int, int> coor = decode( x, y, static_cast<DirectionType>(i) );       
        int newX = coor.first, newY = coor.second;
        
        if( cells[newX][newY].isTile() && ! cells[newX][newY].getObject() ){
            
            if( index == 0 ){return coor;}
            index--;
        }
    }

    return std::make_pair( x, y );
}

void Floor::moveEnemy( int x, int y, int x0, int y0 ){
    
    for( auto & p : cells ){
        for( auto & q : p ){
            q.setMoved( false );
        }
    }
    
    int c1 = cells.size();

    for( int i = 0; i < c1; i++ ){
        int c2 = cells[i].size();
        
        for( int j = 0; j < c2; j++ ){
            if( abs( i - x ) <= 1 && abs( j - y ) <= 1 ) continue;
            if( cells[i][j].getInfo().objectType != ObjectType::Enemy ) continue;
            if( cells[i][j].getMoved() ) continue;
            
            std::pair<int, int> p;
            if( abs( i - x0 ) <= 1 && abs( j - y0 ) <= 1 
                    && cells[x0][y0].getInfo().objectType == ObjectType::Nothing
                    && cells[x0][y0].getInfo().floorType == FloorType::Tile ){
                p = std::make_pair( x0, y0 );
            }
            else p = randomSelectNeighbour( i, j );
            cells[p.first][p.second].setObject( cells[i][j].getObject() );
            cells[i][j].setObject( nullptr );
        }
    }
}

std::string Floor::neighbourAttack( std::shared_ptr<Player> p, int x, int y ){
    std::string msg = "";

    for( int i = 0; i < 8; i++ ){
        std::pair<int, int> coor = decode( x, y, static_cast<DirectionType>(i) );
        int newX = coor.first, newY = coor.second;

        if( cells[newX][newY].getInfo().objectType == ObjectType::Enemy ){
            msg += std::dynamic_pointer_cast<Character>(cells[newX][newY].getObject()) -> attack( p );
        }

        else if( cells[newX][newY].getInfo().objectType == ObjectType::Treasure || cells[newX][newY].getInfo().objectType == ObjectType::BarrierSuit ){
            std::shared_ptr<Enemy> protector = std::dynamic_pointer_cast<Item>(cells[newX][newY].getObject()) -> getProtector();
            if( protector ) msg += protector -> attack( p );
        }
    }
    return msg;
}

std::pair<int, int> Floor::randomPlace( std::shared_ptr<Object> ob ){
    srand( time(NULL) );
    int chamberTarget, cellTarget;

    while( true ){
        chamberTarget = rand() % chamberNum + 1;
        cellTarget = rand() % chamber[chamberTarget].size();
        if( ! chamber[chamberTarget][cellTarget] -> getObject() ) break;
    }
    Cell * cell = chamber[chamberTarget][cellTarget];
    cell -> setObject( ob );
    return std::make_pair( cell -> getInfo().x, cell -> getInfo().y );
}

std::string Floor::spawnFloor( int PotionNum, int TreasureNum, int EnemyNum ){
    for( int i = 0; i < TreasureNum; i++ ) spawnTreasure();
    for( int i = 0; i < PotionNum; i++ ) spawnPotion();
    for( int i = 0; i < EnemyNum - 1; i++ ) spawnEnemy( false );
    spawnEnemy( true );
    spawnStair();
    if( floorHasBarrierSuit ) spawnBarrierSuit();    
    return "A new floor is generated. ";
}

int Floor::getFloorNum(){
    return floorNum;
}

std::shared_ptr<Object> parse( char c ){
    using std::make_shared;

    switch( c ){
        case '0':
            return make_shared<RH>();
        case '1':
            return make_shared<BA>();
        case '2':
            return make_shared<BD>();
        case '3':
            return make_shared<PH>();
        case '4':
            return make_shared<WA>();
        case '5':
            return make_shared<WD>();
        case '6':
            return make_shared<NormalHoard>();
        case '7':
            return make_shared<SmallHoard>();
        case '8':
            return make_shared<MerchantHoard>();
        case '9':
            return make_shared<DragonHoard>();   
        case 'B':
            return make_shared<BarrierSuit>();
        case '/':
            return make_shared<Stair>( false );
        case 'V':
            return make_shared<Vampire>();
        case 'W':
            return make_shared<Werewolf>();
        case 'N':
            return make_shared<Goblin>();
        case 'D':
            return make_shared<Dragon>();
        case 'T':
            return make_shared<Troll>();
        case 'M':   
            return make_shared<Merchant>();
    }
    return nullptr;
}

std::istream & operator>>( std::istream & in, Floor & floor ){
    in >> floor.td;

    floor.cells.clear();

    int c1 = floor.td.map.size();

    for( int i = 0; i < c1; i++ ){
        std::vector<Cell> vec;
        floor.cells.emplace_back( vec );
        int c2 = floor.td.map[i].size();

        for( int j = 0 ;j < c2; j++ ){

            if( floor.td.map[i][j] == '.'){
                Cell tmp{ i, j, FloorType::Tile };
                floor.cells[i].emplace_back( tmp );
            }
            else if( floor.td.map[i][j] == '@'){
                Cell tmp{ i, j, FloorType::Tile };
                floor.cells[i].emplace_back( tmp );
                floor.cells[i][j].setObject( std::make_shared<Human>() );
            }
            else if( floor.td.map[i][j] >= '0' && floor.td.map[i][j] <= '9' ){
                Cell tmp{ i, j, FloorType::Tile };
                floor.cells[i].emplace_back( tmp );
                floor.cells[i][j].setObject( parse( floor.td.map[i][j] )  );
            }
            else if( floor.td.map[i][j] >= 'A' && floor.td.map[i][j] <= 'Z' ){
                Cell tmp{ i, j, FloorType::Tile };
                floor.cells[i].emplace_back( tmp );
                floor.cells[i][j].setObject( parse( floor.td.map[i][j] )  );
            }
            else if( floor.td.map[i][j] == '/' ){
                Cell tmp{ i, j, FloorType::Tile };
                floor.cells[i].emplace_back( tmp );
                floor.s = std::make_shared<Stair>( false );
                floor.cells[i][j].setObject( floor.s );
                floor.sX = i;
                floor.sY = j;
            }
            else if ( floor.td.map[i][j] == '+' || floor.td.map[i][j] == '#' ){
                Cell tmp{ i, j, FloorType::Special };
                floor.cells[i].emplace_back( tmp );
            }
            else{
                Cell tmp{ i, j, FloorType::NoAccess, };
                floor.cells[i].emplace_back( tmp );
            }
        }
    }
    return in;
}

void Floor::spawnTreasure(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({5,1,2});
    int tmp = d(gen);

    if( tmp == 0 ){
        randomPlace( std::make_shared<NormalHoard>() );
    }
    if( tmp == 1 ){
        randomPlace( std::make_shared<SmallHoard>() );
    }
    if( tmp == 2 ){
        std::shared_ptr<DragonHoard> dh = std::make_shared<DragonHoard>();
        std::shared_ptr<Dragon> d = std::make_shared<Dragon>();
        std::pair<int, int> p = randomPlace( dh );
        std::pair<int, int> q = randomSelectNeighbour( p.first, p.second );
        if( p != q ) cells[q.first][q.second].setObject( d );
        dh -> setProtector( d );
    }
}

void Floor::spawnBarrierSuit(){
    std::shared_ptr<BarrierSuit> bh = std::make_shared<BarrierSuit>();
    std::shared_ptr<Dragon> d = std::make_shared<Dragon>();
    std::pair<int, int> p = randomPlace( bh );
    std::pair<int, int> q = randomSelectNeighbour( p.first, p.second );
    if( p != q ) cells[q.first][q.second].setObject( d );
    bh -> setProtector( d );
}

void Floor::spawnPotion(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({1,1,1,1,1,1});
    int tmp = d(gen);

    if( tmp == 0 ){
        randomPlace( std::make_shared<RH>() );
    }
    if( tmp == 1 ){
        randomPlace( std::make_shared<BA>() );
    }
    if( tmp == 2 ){
        randomPlace( std::make_shared<BD>() );
    }
    if( tmp == 3 ){
        randomPlace( std::make_shared<PH>() );
    }
    if( tmp == 4 ){
        randomPlace( std::make_shared<WA>() );
    }
    if( tmp == 5 ){
        randomPlace( std::make_shared<WD>() );
    }
}

void Floor::spawnEnemy( bool hasCompass ){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({4,3,5,2,2,2});
    int tmp = d(gen);
    std::pair<int,int> p;
    if( tmp == 0 ){
        p=randomPlace( std::make_shared<Werewolf>( hasCompass ) );
    }
    if( tmp == 1 ){
        p=randomPlace( std::make_shared<Vampire>( hasCompass ) );
    }
    if( tmp == 2 ){
        p=randomPlace( std::make_shared<Goblin>( hasCompass ) );
    }
    if( tmp == 3 ){
        p=randomPlace( std::make_shared<Troll>( hasCompass ) );
    }
    if( tmp == 4 ){
        p=randomPlace( std::make_shared<Phoenix>( hasCompass ) );
    }
    if( tmp == 5 ){
        p=randomPlace( std::make_shared<Merchant>( hasCompass ) );
    }
}

std::shared_ptr<Stair> Floor::spawnStair(){
    s = std::make_shared<Stair>();
    std::pair<int, int> p = randomPlace( s );
    sX = p.first, sY = p.second;
    return s;
}

void Floor::print(){
    cells[sX][sY].notifyObservers();
    td.print();
}
