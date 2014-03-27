#pragma once
#include "cocos2d.h"
#include "BaseScene.h"
#include "Rope.h"
class FactoryScene :
	public BaseScene
{
public:
	CREATE_FUNC(FactoryScene);

	virtual bool init();
	static CCScene* scene();

	void setMapThings();
};

