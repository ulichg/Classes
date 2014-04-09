#include "DirectController.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"

bool DirectController::init(){
	this->isStartTouch = false;
	this->startP = CCPointZero;
	this->iYSpeed = SPEED;

	/* 设置允许触屏 */
	this->setTouchEnabled(true);
	/* 设置运行加速传感器 */
	this->setAccelerometerEnabled(true);

	this->scheduleUpdate();
	return true;
}

void DirectController::update(float dt)
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
	FactoryScene* fs = dynamic_cast<FactoryScene*>(hero->getParent()->getParent());
	curPos.y += iYSpeed;
	hero->setSimplePosition(curPos);
}

void DirectController::setiXSpeed(float iSpeed)
{
	this->iXSpeed = iSpeed;
}

void DirectController::setiYSpeed(float iSpeed)
{
	this->iYSpeed = iSpeed;
}
bool DirectController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return false;
	}
	if (isStartTouch){
		return false;
	}
	isStartTouch = true;
	/* 获取点击的坐标 */
	CCPoint touchLocation = pTouch->getLocationInView();
	this->startP = CCDirector::sharedDirector()->convertToGL(touchLocation);
	return true;
}

void DirectController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

void DirectController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return;
	}
	if (!isStartTouch){
		return;
	}
	isStartTouch = false;
	CCPoint touchLocation = pTouch->getLocationInView();
	CCPoint endP = CCDirector::sharedDirector()->convertToGL(touchLocation);

	MaoChong* hero = dynamic_cast<MaoChong*>(mControllerListener);
	if (!hero){
		return;
	}
	if (startP.x - endP.x < -20){
		hero->statusChangeTo(HeroStatus::RIGHT_FLY);
	}
	else if(startP.x - endP.x > 20){
		hero->statusChangeTo(HeroStatus::LEFT_FLY);
	}
	//float maxLength = MAX(abs(startP.x - endP.x), abs(startP.y - endP.y));

	// 触发切换毛虫所在边
	if (fabs(startP.x - endP.x) <= 20){
		if (hero->getStatus() == HeroStatus::LEFT_PA){
			hero->statusChangeTo(HeroStatus::RIGHT_PA);
			hero->setCurLine(hero->getCurLine() + 1);
		}
		else if (hero->getStatus() == HeroStatus::RIGHT_PA){
			hero->statusChangeTo(HeroStatus::LEFT_PA);
			hero->setCurLine(hero->getCurLine() - 1);
		}
	}
}

void DirectController::registerWithTouchDispatcher()
{
	/* 注册触屏事件 */
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void DirectController::didAccelerate(CCAcceleration* mAccelerationValue){
	if (mControllerListener == NULL){
		return;
	}

	MaoChong* maoChong = dynamic_cast<MaoChong*>(mControllerListener);
	if (maoChong == NULL){
		return;
	}
	CCDirector* pDtr = CCDirector::sharedDirector();

	if (mAccelerationValue->x > 0.05)
	{
		// 向右偏
		if (maoChong->getCurLine() % 2 == 0){
			// 在左侧
			maoChong->statusChangeTo(HeroStatus::RIGHT_PA);
			maoChong->setCurLine(maoChong->getCurLine() + 1);
		}
	}
	else if (mAccelerationValue->x < -0.05){
		// 向左偏
		if (maoChong->getCurLine() % 2 == 1){
			// 在右侧
			maoChong->statusChangeTo(HeroStatus::LEFT_PA);
			maoChong->setCurLine(maoChong->getCurLine() - 1);
		}
	}
}