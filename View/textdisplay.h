#ifndef __TEXT_DISPLAY_H__
#define __TEXT_DISPLAY_H__

#include "observer.h"
#include <vector>
#include <iostream>

class Subject;
class Floor;

class TextDisplay : public Observer{
  public:
    void print() const;
    void notify( Subject & whoFrom ) override;
    friend class Floor;
    friend std::istream & operator>>( std::istream &, TextDisplay & );
    friend std::istream & operator>>( std::istream &, Floor & );
  private:
    std::vector<std::vector<char>> map;
    std::vector<std::vector<char>> buff;
};

#endif
