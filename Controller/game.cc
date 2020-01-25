#include "enum.h"
#include "game.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>

Game::Game( int floorNum ):
    floorNum{floorNum} {
    floor.setFloorNum(1);
    srand( time(NULL) );
    BSFloorNum = rand() % ( floorNum - 1 ) + 1;
}

void Game::getPlayer(){
    
    while( true ){
        std::cout << "Choose your character: "
            << "h (Human), d (Dwarf), e (Elves), o (Orc), j (Jia)" << std::endl;
        std::string s;
        std::getline( std::cin, s );

        if( std::cin.eof() ) throw 0;

        if( s[0] == 'h' ){
            player = std::make_shared<Human>();
            race = "Human";
            break;
        }
        else if( s[0] == 'd' ){
            player = std::make_shared<Dwarf>();
            race = "Dwarf";
            break;
        }
        else if( s[0] == 'e' ){
            player = std::make_shared<Elves>();
            race = "Elves";
            break;
        }
        else if( s[0] == 'o' ){
            player = std::make_shared<Orc>();
            race = "Orc";
            break;
        }
        else if( s[0] == 'j' ){
            player = std::make_shared<Jia>();
            race = "Jia";
            break;
        }
    }
}

void Game::getNumbers(){
    std::cout << "Please enter the number of potions. Press enter to get the default value (10): ";
    std::string s;
    std::getline( std::cin, s );

    std::istringstream iss{s};
    iss >> PotionNum;

    std::cout << "Please enter the number of gold piles. Press enter to get the default value (10): ";
    std::getline( std::cin, s );

    std::istringstream iss2{s};
    iss2 >> TreasureNum;

    std::cout << "Please enter the number of enemies. Press enter to get the default value (20): ";
    std::getline( std::cin, s );

    std::istringstream iss3{s};
    iss3 >> EnemyNum;
}

void Game::beginGame(){
    std::ifstream f{"floor.txt"};
    initFloor(f);
    std::pair<int, int> p;
    getPlayer();
    getNumbers();
    p = floor.randomPlace( player );
    playerX = p.first;
    playerY = p.second;

    if( BSFloorNum == 1 ) floor.setHasBarrierSuit( true );
    else floor.setHasBarrierSuit( false );
    msg = floor.spawnFloor( PotionNum, TreasureNum, EnemyNum );
    print();
    loop(f);
}

void Game::loadGame( std::string file ){
    std::ifstream f{file};
    initFloor(f);
    std::pair<int, int> p;
    getPlayer();
    initLoad();
    msg = "Player has come to a new floor. ";
    print();
    loopLoad(f);    
}

void Game::loopLoad( std::ifstream & f ){
    
    while( true ){
        try{
            floor.setValidCommand( false );
            std::pair<int ,int> coor = std::make_pair( playerX, playerY );
            getCommand();
            if( floor.getValidCommand() ){
                floor.moveEnemy( playerX, playerY, coor.first, coor.second );
                msg += floor.neighbourAttack( player, playerX, playerY );
            }
            print();
            if( player -> isDead() ) end();
        }
        catch( Up ){
            floor.setFloorNum( floor.getFloorNum() + 1 );
            if( floor.getFloorNum() == floorNum ){
                end();
                return;
            }
            initFloor(f);
            std::pair<int, int> p;
            initLoad();
            msg = "Player has come to a new floor. ";
            player -> reset();
            print();
        }
        catch(...){
            break;
        }
    }
}

void Game::initLoad(){
    floor.initPlayer( player, playerX, playerY );
    floor.initProtector();    
}

void Game::loop( std::ifstream & f ){
    while( true ){
        try{
            floor.setValidCommand( false );
            std::pair<int ,int> coor = std::make_pair( playerX, playerY );
            getCommand();
            if( floor.getValidCommand() ){
                floor.moveEnemy( playerX, playerY, coor.first, coor.second  );
                msg += floor.neighbourAttack( player, playerX, playerY );
            }
            print();
            if( player -> isDead() ) end();
        }
        catch( Dragon * ){
            floor.setFloorNum( floor.getFloorNum() + 1 );
            if( floor.getFloorNum() == floorNum ){
                end();
                return;
            }
            initFloor(f);
            std::pair<int, int> p;
            p = floor.randomPlace( player );
            playerX = p.first;
            playerY = p.second;
        
            if( BSFloorNum == floor.getFloorNum() ) floor.setHasBarrierSuit( true );
            else floor.setHasBarrierSuit( false );
            msg = floor.spawnFloor( PotionNum, TreasureNum, EnemyNum );
            player -> reset();
            print();
        }
        catch(...){
            break;
        }
    }
}

void Game::end(){
    
    if( player -> isDead() ){
        std::cout << "Your character died!" << std::endl;
        throw 0;
    }
    else{
        std::cout << "You Won! Your score is: " << player -> getPoint() << std::endl;
    }
}

void Game::print(){
    floor.print();
    std::cout << "Race: " << race << "    Gold: " << player -> getGold()
        << "                                      Floor: " 
        << floor.getFloorNum() << std::endl;
    std::cout << "HP: " << player -> getHP() << std::endl;
    std::cout << "Atk: " << player -> getAtk() << std::endl;
    std::cout << "Def: " << player -> getDef() << std::endl;
    std::cout << "Action: " << msg << std::endl;
}

DirectionType getDirectionType( std::string command ){
    
    if( command == "no" ) return DirectionType::N;
    if( command == "so" ) return DirectionType::S;
    if( command == "we" ) return DirectionType::W;
    if( command == "ea" ) return DirectionType::E;
    if( command == "ne" ) return DirectionType::NE;
    if( command == "nw" ) return DirectionType::NW;
    if( command == "se" ) return DirectionType::SE;
    if( command == "sw" ) return DirectionType::SW;
    throw 0;
}

void Game::getCommand(){
    std::string command;
    std::getline( std::cin, command );
    if( std::cin.eof() ) throw "";
    
    try{
        if( command[0] == 'r' ){
            beginGame();
            return;
        }
        else if( command[0] == 'q' ){
            throw "";
        }
        else if( command[0] == 'u' ){
            std::istringstream iss{command};
            iss >> command;
            iss >> command;
            msg = floor.usePotion( player, playerX, playerY, getDirectionType( command ) );
        }
        else if( command[0] == 'a' ){
            std::istringstream iss{command};
            iss >> command;
            iss >> command;
            msg = floor.attackEnemy( player, playerX, playerY, getDirectionType( command ) );
        }
        else{
            std::istringstream iss{command};
            iss >> command;
            msg = floor.movePlayer( command, player, playerX, playerY, getDirectionType( command ) );
        }
    }
    catch( int ){
        msg = "Invalid Command. ";
    }
}

void Game::initFloor( std::ifstream & f ){
    f >> floor;
    floor.attach();
    floor.initChamber();
}
