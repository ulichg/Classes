#include "Rope.h"
#include "Data/GlobalVar.h"

Rope::Rope(){
	init();
}

bool Rope::init()
{
	this->setAnchorPoint(ccp(0.5, 1));
	// 随机方向
	isDown = rand() % 2;

	// 随机开始长度
	curLength = rand() % (int)(MAXLINE - MINLINE) + MINLINE;
	setShowLength();
	return true;
}

CCRect Rope::getCollideRect(){
	CCSize size = this->mSprite->getContentSize();
	if (this->getParent()){
		return CCRectMake(this->getPositionX() - PNG_WIDTH / 2, this->getPositionY(), PNG_WIDTH, this->curLength);
	}
	return CCRectZero;
}

void Rope::rollAction(){
	scheduleUpdate();
}

void Rope::update(float delta)
{
	this->removeChild(this->mSprite);
	if (isDown)
	{
		if (this->curLength >= MAXLINE){
			isDown = false;
		}
		else {
			this->curLength += SPEED;
		}
	}
	else
	{
		if (this->curLength <= MINLINE){
			isDown = true;
		}
		else {
			this->curLength -= SPEED;
		}
		
	}
	setShowLength();
	//CCLog("length: %f", this->curLength);
}

void Rope::setShowLength(){
	this->mSprite = CCSprite::create("map/rope.png", CCRectMake(0, PNG_HEIGHT - this->curLength, PNG_WIDTH, this->curLength));
	mSprite->setAnchorPoint(ccp(0.5, 1));
	mSprite->setPosition(CCPointZero);
	this->addChild(this->mSprite);
}

bool Rope::is_Down(){
	return isDown;
}

float Rope::getCurLength(){
	return this->curLength;
}