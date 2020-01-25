#include <cstdlib>
#include <ctime>
#include <random>
#include "game.h"
#include <fstream>
int main( int argc, char * argv[] ){
    Game g;
    try{
        if( argc <= 1 ) g.beginGame();    
        else{
            std::string s = argv[1];
            g.loadGame( s );
        }
    }
    catch(...){}
}
