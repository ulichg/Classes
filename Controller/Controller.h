#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"
#include "Person/MaoChong.h"

using namespace cocos2d;
class Controller : public CCLayer{
public:
	void setControllerListener(Hero* mControllerListener);

protected:
	Hero* mControllerListener;
};
#endif