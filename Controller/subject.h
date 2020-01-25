#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include "info.h"

class Observer;

class Subject{
  public:
    void attach( Observer * ob );
    void notifyObservers();
    virtual Info getInfo() = 0;
  private:
    std::vector<Observer *> observers;
};

#endif
