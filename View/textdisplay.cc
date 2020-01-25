#include "subject.h"
#include "observer.h"
#include "textdisplay.h"
#include "enum.h"
#include <iostream>

class Treasure;

void TextDisplay::print() const{
    
    for( auto p1 : map ){
        for( auto p2 : p1 ){
            std::cout << p2;
        }
        std::cout << std::endl;
    }
}

void TextDisplay::notify( Subject & whoFrom ){
    int x = whoFrom.getInfo().x;
    int y = whoFrom.getInfo().y;
    std::shared_ptr<Object> ob = whoFrom.getInfo().object;
    
    if( ob.get() ) map[x][y] = whoFrom.getInfo().object -> getOutputChar();
    else map[x][y] = buff[x][y];
}

std::istream & operator>>( std::istream & in, TextDisplay & td ){
    td.map.clear();
    td.buff.clear();
    int i = 0;
    std::vector<char> e;
    td.map.emplace_back( e );
    td.buff.emplace_back( e );

    while( i < 25 ){
        char c;
        in.get( c );
        
        if( c == '\n' ){
            i++;
            td.map.emplace_back( e );
            td.buff.emplace_back( e );
        }
        else{
            td.map[i].emplace_back(c);
            
            if( c <= '9' && c >= '0' ) td.buff[i].emplace_back('.');
            else if( c <= 'Z' && c >= 'A' ) td.buff[i].emplace_back('.');
            else if( c == '@') td.buff[i].emplace_back('.');
            else td.buff[i].emplace_back(c);
        }
    }
    return in;
}
