#include "Rope.h"
#include "Data/GlobalVar.h"

Rope::Rope(){
	init();
}

bool Rope::init()
{
	this->setAnchorPoint(ccp(0.5, 1));
	// �������
	isDown = rand() % 2;

	// �����ʼ����
	curLength = rand() % (int)(MAXLINE - MINLINE) + MINLINE;
	setShowLength();
	return true;
}

CCRect Rope::getCollideRect(){
	CCSize size = this->mSprite->getContentSize();
	CCRect c = CCRectZero;
	if (this->getParent()){
		c = CCRectMake(this->getPositionX() - PNG_WIDTH / 2, this->getPositionY() - this->curLength, PNG_WIDTH, this->curLength);
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