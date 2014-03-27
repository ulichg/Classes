#ifndef __CONTROLLER_LISTENER_H__
#define __CONTROLLER_LISTENER_H__

#include "cocos2d.h"

using namespace cocos2d;

class ControllerListener {
public:
	virtual void setSimplePosition(CCPoint c) = 0;
	virtual CCPoint getCurPosition() = 0;
};

#endif