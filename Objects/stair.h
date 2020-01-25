#ifndef _STAIR_
#define _STAIR_
#include "object.h"
#include "enum.h"

class Stair : public Object {
	bool hidden;
	public:
    Stair( bool h = true );
	ObjectType getObjectType() override;
	void setHidden();
	bool getHidden();
    char getOutputChar() override;
};
#endif
