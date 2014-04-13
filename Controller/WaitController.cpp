#include "WaitController.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"

bool WaitController::init(){
	/* ÉèÖÃÔÊÐí´¥ÆÁ */
	this->setTouchEnabled(true);
	return true;
}

bool WaitController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return true;
	}

	MaoChong* maoChong = dynamic_cast<MaoChong*>(mControllerListener);
	if (!maoChong){
		return true;
	}
	if (maoChong->getCurLine() % 2 == 0){
		maoChong->statusChangeTo(HeroStatus::LEFT_PA);
	}
	else {
		maoChong->statusChangeTo(HeroStatus::RIGHT_PA);
	}
	
	return true;
}

void WaitController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void WaitController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void WaitController::registerWithTouchDispatcher()
{
	/* ×¢²á´¥ÆÁÊÂ¼þ */
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}