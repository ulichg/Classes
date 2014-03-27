#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"
#include "ControllerListener.h"

using namespace cocos2d;
class Controller : public CCLayer{
public:
	void setControllerListener(ControllerListener* mControllerListener);

protected:
	ControllerListener* mControllerListener;
};
#endif