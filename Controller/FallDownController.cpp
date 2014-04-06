#include "FallDownController.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"

bool FallDownController::init(){
	this->iYSpeed = FALL_DOWN_SPEED;

	/* 设置允许触屏 */
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}

void FallDownController::update(float dt)
{
	if (mControllerListener == NULL) {
		return;
	}

	
	MaoChong* hero = dynamic_cast<MaoChong*>(mControllerListener);
	if (!hero){
		CCLog("wrong 1");
		return;
	}
	CCPoint curPos = hero->getCurPosition();
	curPos.y -= iYSpeed;
	hero->setSimplePosition(curPos);
}

void FallDownController::setiYSpeed(int iSpeed)
{
	this->iYSpeed = iSpeed;
}


bool FallDownController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return true;
	}

	FactoryScene* fs = dynamic_cast<FactoryScene*>(this->getParent()->getParent());
	if (!fs){
		return true;
	}
	fs->doSiPa();
	
	return true;
}

void FallDownController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	///* 获取点击的坐标 */
	//CCPoint touchLocation = pTouch->getLocationInView();
	//touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

	///* 被控制对象的坐标 */
	//CCPoint pos = mControllerListener->getCurPosition();

	///* 判断是向左移动还是向右移动 */
	//int iSpeed = 0;
	//if (touchLocation.x > pos.x) {
	//	iSpeed = 1;
	//}
	//else {
	//	iSpeed = -1;
	//}

	//setiXSpeed(iSpeed);
}

void FallDownController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void FallDownController::registerWithTouchDispatcher()
{
	/* 注册触屏事件 */
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}