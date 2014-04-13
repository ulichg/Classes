#include "Rope.h"
#include "Data/GlobalVar.h"

Rope::Rope(bool isDown, float minLength, float maxLength){
	this->setAnchorPoint(ccp(0.5, 1));
	this->isDown = isDown;
	this->minLength = minLength;
	this->maxLength = maxLength;
	// 随机开始长度
	curLength = (this->maxLength + this->minLength) / 2;
	setShowLength();
	return;
}

CCPoint Rope::getRealPosition(){
	return ccp(getParent()->getPositionX() + this->getPositionX(), getParent()->getPositionY() + this->getPositionY());
}

CCRect Rope::getCollideRect(){
	CCSize size = this->mSprite->getContentSize();
	CCRect c = CCRectZero;
	if (this->getParent()){
		c = CCRectMake(getRealPosition().x - PNG_WIDTH / 2,getRealPosition().y - this->curLength, PNG_WIDTH, this->curLength);
	}
	/*CCSprite* s = CCSprite::createWithSpriteFrameName("coin_front.png");
	s->setScale(0.8f);
	s->setPosition(ccp(c.getMaxX(), c.getMaxY()));
	this->getParent()->addChild(s, 100);*/
	return c;
}

void Rope::rollAction(){
	scheduleUpdate();
}

void Rope::update(float delta)
{
	this->removeChild(this->mSprite);
	if (isDown)
	{
		if (this->curLength >= this->maxLength){
			isDown = false;
		}
		else {
			this->curLength += SPEED;
		}
	}
	else
	{
		if (this->curLength <= this->minLength){
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