#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject;

class Observer{
  public:
    virtual void notify( Subject & whoFrom ) = 0;
};

#endif
