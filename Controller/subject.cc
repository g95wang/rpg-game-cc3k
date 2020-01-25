#include "subject.h"
#include "observer.h"

void Subject::attach( Observer * ob ){
    observers.emplace_back( ob );
}

void Subject::notifyObservers(){

    for( auto p : observers ){
        p -> notify( * this );
    }
}
