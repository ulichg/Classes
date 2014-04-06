#include "FactoryScene.h"
#include "Person/MaoChong.h"
#include "Data/GlobalVar.h"

bool FactoryScene::init(){
	this->ropeArray = CCArray::create();
	ropeArray->retain();
	CCTMXTiledMap* map = CCTMXTiledMap::create("map/testMap.tmx");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map/mapThing.plist", "map/mapThing.png");
	setMap(map);
	initHero();
	setMapThings();
	return true;
}

void FactoryScene::initHero(){
	MaoChong* maoChong = MaoChong::createWithTiledMap(map);
	hero = maoChong;
}

CCScene* FactoryScene::scene(){
	CCScene* mScene = CCScene::create();
	FactoryScene* mLayer = FactoryScene::create();
	mScene->addChild(mLayer);

	return mScene;
}

void FactoryScene::setMapThings(){
	if (!this->map){
		return;
	}

	// 设置转动的轴以及绳子
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("roundObjects");
	int length = objGroup->getObjects()->count();
	char str[100];
	for (int i = 0; i < length; i++)
	{
		sprintf(str, "round_%i", i);
		CCDictionary* roundDic = objGroup->objectNamed(str);
		float x = roundDic->valueForKey("x")->floatValue();
		float y = roundDic->valueForKey("y")->floatValue();
		
		CCSprite* roundSprite = CCSprite::createWithSpriteFrameName("round.png");
		CCSize size = roundSprite->getContentSize();
		//roundSprite->setPosition(ccp(x + size.width / 2, y + size.height / 2));
		roundSprite->setPosition(ccp(x, y));

		CCActionInterval* rotate = CCRotateBy::create(2, 360.0f);

		// 第一个轴不转
		if (i != 0){
			roundSprite->runAction(CCRepeatForever::create(rotate));
		}
		map->addChild(roundSprite, 1);

		Rope* rope = new Rope();
		ropeArray->addObject(rope);
		rope->setPosition(ccp(x, y));
		// 第一个绳子不动
		if (i != 0)
		{
			rope->rollAction();
		}
		else 
		{
			bindHeroToRope(rope);
		}
		
		map->addChild(rope, 0);
	}

	refreshSiNumLabel();
}

bool FactoryScene::bindHeroToRope(Rope* rope){
	if (!rope || !this->hero)
	{
		return false;
	}
	CCPoint ropeP = rope->getPosition();
	CCPoint heroP = this->hero->getPosition();

	CCLog("Hero loc: %f %f", ropeP.x, heroP.y);
	this->hero->setPosition(ropeP.x, heroP.y);
	return true;
}

void FactoryScene::findRope(){
	MaoChong* maoChong = (MaoChong*)hero;
	CCLog("find rope");
	Rope* targetRope = NULL;
	// 检测碰到哪根绳子
	for (unsigned int i = 0; i < ropeArray->count(); i++){
		Rope* r = (Rope*)ropeArray->objectAtIndex(i);
		if (r->getPositionX() == maoChong->getPositionX()){
			if (r->getCollideRect().intersectsRect(maoChong->getCollideRect())){
				targetRope = r;
			}
		}
	}

	if (targetRope){
		// 找到绳子，绑定，并设置设置毛虫爬方向
		bindHeroToRope(targetRope);
		if (maoChong->getCurLine() % 2 == 1)
		{
			maoChong->statusChangeTo(HeroStatus::RIGHT_PA);
		}
		else
		{
			maoChong->statusChangeTo(HeroStatus::LEFT_PA);
		}
	}
	else {
		// 没碰到绳子，设置掉落方向
		if (maoChong->getCurLine() % 2 == 1)
		{
			maoChong->statusChangeTo(HeroStatus::RIGHT_FALL_DOWN);
		}
		else
		{
			maoChong->statusChangeTo(HeroStatus::LEFT_FALL_DOWN);
		}
	}
}

Rope* FactoryScene::getSiTouchRope(){
	Rope* targetRope = NULL;

	if (!hero){
		return NULL;
	}

	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (!maoChong)
	{
		return NULL;
	}
	// 检测碰到哪根绳子
	for (unsigned int i = 0; i < ropeArray->count(); i++){
		Rope* r = (Rope*)ropeArray->objectAtIndex(i);
		if (r->getPositionY() - hero->getPositionY() > 0 && r->getPositionY() - hero->getPositionY() < SI_LENGTH){
			// 绳子垂直距离毛虫在丝的长度内
			if (r->getPositionX() == THREELINES[maoChong->getCurLine() / 2]){
				// 绳子位于对应列上
				if (targetRope){
					// 已存在，取近的
					if (r->getPositionY() < targetRope->getPositionY()){
						targetRope = r;
					}
				}
				else {
					targetRope = r;
				}
			}
		}
	}
	return targetRope;
}

void FactoryScene::doSiPa()
{
	int siNum = hero->getSiNum();
	if (siNum > 0)
	{
		this->targetRope = getSiTouchRope();
		if (!targetRope)
		{
			hero->statusChangeTo(HeroStatus::DIE);
			return;
		}
		else
		{
			hero->setSiNum(siNum - 1);
			this->refreshSiNumLabel();
			hero->statusChangeTo(HeroStatus::SI_PA);
			scheduleOnce(schedule_selector(FactoryScene::backToRope), BACK_TIME);
		}
	}
}

void FactoryScene::backToRope(float dt){
	CCLog("back to rope");
	if (!this->targetRope){
		return;
	}
	
	float x = targetRope->getPositionX();
	float y = targetRope->getPositionY() - targetRope->getCurLength() / 2;
	CCMoveTo* move = CCMoveTo::create(0.3f, ccp(x, y));

	CCActionInterval* siPa = CCSequence::create(move, CCCallFunc::create(this, callfunc_selector(FactoryScene::setPa)), NULL);
	hero->runAction(siPa);
}

void FactoryScene::setPa(){
	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (maoChong->getCurLine() % 2 == 0)
	{
		hero->statusChangeTo(HeroStatus::LEFT_PA);
	}
	else
	{
		hero->statusChangeTo(HeroStatus::RIGHT_PA);
	}
}

FactoryScene::~FactoryScene(){
	CCObject* o = NULL;
	CCARRAY_FOREACH(ropeArray, o){
		Rope* r = dynamic_cast<Rope*>(o);
		r->release();
	}
	CC_SAFE_DELETE(ropeArray);
}