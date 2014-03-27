#ifndef __CONTROLLER_LISTENER_H__
#define __CONTROLLER_LISTENER_H__

#include "cocos2d.h"

using namespace cocos2d;

class ControllerListener {
public:
	virtual void setSimplePosition(int x, int y) = 0;
	virtual CCPoint getCurPosition() = 0;
};

#endif