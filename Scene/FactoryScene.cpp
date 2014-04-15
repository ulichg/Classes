#include "FactoryScene.h"
#include "Person/MaoChong.h"
#include "Data/GlobalVar.h"

bool FactoryScene::init(){
	siNum = SI_START_NUM;
	coinNum = 0;
	distance = 0;
	this->hero = NULL;
	this->targetRope = NULL;
	this->ropeArray = CCArray::create();
	ropeArray->retain();
	this->roundArray = CCArray::create();
	roundArray->retain();
	this->coinArray = CCArray::create();
	coinArray->retain();
	this->mapArray = CCArray::create();
	mapArray->retain();
	curMap = 0;
	this->thingLayer = CCLayer::create();
	this->addChild(thingLayer, 10);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map/mapThing.plist", "map/mapThing.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map/coin0.plist", "map/coin0.png");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("map/coin.ExportJson");
	
	initMap();
	refreshSiNumLabel();
	refreshCoinNumLabel();
	scheduleUpdate();
	schedule(schedule_selector(FactoryScene::updateDistance), 0.1f);
	return true;
}

void FactoryScene::initMap(){
	CCTMXTiledMap* map = CCTMXTiledMap::create("map/testMap_0.tmx");
	initHero(map);
	addMap(map);
	
	map = CCTMXTiledMap::create("map/testMap_1.tmx");
	addMap(map);
}

void FactoryScene::addMap(CCTMXTiledMap* map){
	if (mapArray->count() > MAP_CACHE){
		this->removeMap((CCTMXTiledMap*)mapArray->objectAtIndex(curMap - MAP_CACHE));
	}
	mapArray->addObject(map);
	setMapThings(map);
	if (curMap == 0){
		
	}
	map->setPosition(ccp(-WIDTH, -HEIGHT));
	this->addChild(map, 0);
}

void FactoryScene::initHero(CCTMXTiledMap* map){
	MaoChong* maoChong = MaoChong::createWithTiledMap(map);
	thingLayer->addChild(maoChong, 10);
	maoChong->statusChangeTo(HeroStatus::LEFT_PA);
	hero = maoChong;
}

CCScene* FactoryScene::scene(){
	CCScene* mScene = CCScene::create();
	FactoryScene* mLayer = FactoryScene::create();
	mScene->addChild(mLayer);

	return mScene;
}

void FactoryScene::setMapThings(CCTMXTiledMap* map){
	if ( !map ){
		return;
	}
	
	// 设置转动的轴以及绳子
	setRoundAndRope(map);
	// 设置灯光
	setLight(map);
	// 设置金币
	setCoin(map);
}


void FactoryScene::setRoundAndRope(CCTMXTiledMap* map){
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("roundObjects");
	int length = objGroup->getObjects()->count();
	CCObject* o = NULL;
	CCARRAY_FOREACH(objGroup->getObjects(), o){
		CCDictionary* roundDic = dynamic_cast<CCDictionary*>(o);
		if (!o){
			CCLog("wrong FactoryScene::setCoin");
			return;
		}
		float x = roundDic->valueForKey("x")->floatValue();
		float y = roundDic->valueForKey("y")->floatValue();

		/*CCSprite* roundSprite = CCSprite::createWithSpriteFrameName("round.png");*/
		CCSprite* roundSprite = CCSprite::create("map/round.png");
		roundArray->addObject(roundSprite);
		CCSize size = roundSprite->getContentSize();
		//roundSprite->setPosition(ccp(x + size.width / 2, y + size.height / 2));
		roundSprite->setPosition(ccp(x, y));

		CCActionInterval* rotate = CCRotateBy::create(2, 360.0f);

		// 第一个轴不转
		/*if (i != 0){
			roundSprite->runAction(CCRepeatForever::create(rotate));
		}*/
		float minLength = roundDic->valueForKey("minLength")->floatValue();
		float maxLength = roundDic->valueForKey("maxLength")->floatValue();
		bool isDown = roundDic->valueForKey("isDown")->boolValue();
		roundSprite->runAction(CCRepeatForever::create(rotate));
		map->addChild(roundSprite, 1);

		Rope* rope = new Rope(isDown,minLength,maxLength);
		ropeArray->addObject(rope);
		rope->setPosition(ccp(x, y));

		rope->rollAction();
		//// 第一个绳子不动
		//if (i != 0)
		//{
		//	rope->rollAction();
		//}
		//else
		//{
		//	bindHeroToRope(rope);
		//}

		map->addChild(rope, 0);
		if (ropeArray->count() == 1)
		{
			bindHeroToRope(rope);
		}
	}
}

void FactoryScene::setLight(CCTMXTiledMap* map){
	CCTMXObjectGroup* objGroup1 = map->objectGroupNamed("lightObjects");
	int length1 = objGroup1->getObjects()->count();
	CCObject* o = NULL;
	CCARRAY_FOREACH(objGroup1->getObjects(), o){
		CCDictionary* lightDic = dynamic_cast<CCDictionary*>(o);
		if (!o){
			CCLog("wrong FactoryScene::setCoin");
			return;
		}
		float x = lightDic->valueForKey("x")->floatValue();
		float y = lightDic->valueForKey("y")->floatValue();

		CCSprite* light = CCSprite::create("map/light.png");
		CCSprite* led = CCSprite::create("map/LED.png");

		// 调整灯方向
		const CCString* prop = CCString::create("");
		prop = lightDic->valueForKey("loc");
		led->setAnchorPoint(ccp(1, 0.5));
		light->setAnchorPoint(ccp(1, 0.5));
		if (prop->m_sString.compare("left") == 0){
			led->setScaleX(-1);
		}
		else {
			led->setScaleX(1);
		}
		led->setPosition(ccp(x, y));
		light->setPosition(ccp(0, led->getContentSize().height / 2));
		led->addChild(light, 1);

		map->addChild(led, 20);

		/*CCActionInterval* blink = CCBlink::create(rand() % 3 + 1, 1);
		light->runAction(CCRepeatForever::create(blink));*/

		CCActionInterval* ac1 = CCFadeOut::create(rand() % 10 / float(10) + 1);
		CCSequence* se = CCSequence::create(ac1, ac1->reverse(), NULL);
		light->runAction(CCRepeatForever::create(se));
	}
	//for (int i = 0; i < length1; i++)
	//{
	//	sprintf(str1, "light_%i", i);
	//	CCDictionary* lightDic = objGroup1->objectNamed(str1);
	//	float x = lightDic->valueForKey("x")->floatValue();
	//	float y = lightDic->valueForKey("y")->floatValue();

	//	CCSprite* light = CCSprite::create("map/light.png");
	//	CCSprite* led = CCSprite::create("map/LED.png");

	//	// 调整灯方向
	//	const CCString* prop = CCString::create("");
	//	prop = lightDic->valueForKey("loc");
	//	led->setAnchorPoint(ccp(1, 0.5));
	//	light->setAnchorPoint(ccp(1, 0.5));
	//	if (prop->m_sString.compare("left") == 0){
	//		led->setScaleX(-1);
	//	}
	//	else {
	//		led->setScaleX(1);
	//	}
	//	led->setPosition(ccp(x, y));
	//	light->setPosition(ccp(0, led->getContentSize().height / 2));
	//	led->addChild(light, 1);

	//	map->addChild(led, 20);

	//	/*CCActionInterval* blink = CCBlink::create(rand() % 3 + 1, 1);
	//	light->runAction(CCRepeatForever::create(blink));*/

	//	CCActionInterval* ac1 = CCFadeOut::create(rand() % 10 / float(10) + 1);
	//	CCSequence* se = CCSequence::create(ac1, ac1->reverse(), NULL);
	//	light->runAction(CCRepeatForever::create(se));
	//}
}

void FactoryScene::setCoin(CCTMXTiledMap* map){
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("coinObjects");
	int length = objGroup->getObjects()->count();
	CCObject* o = NULL;
	CCARRAY_FOREACH(objGroup->getObjects(), o){
		CCDictionary* lightDic = dynamic_cast<CCDictionary*>(o);
		if (!o){
			CCLog("wrong FactoryScene::setCoin");
			return;
		}
		float x = lightDic->valueForKey("x")->floatValue();
		float y = lightDic->valueForKey("y")->floatValue();

		CCArmature* coin = CCArmature::create("coin");
		coin->getAnimation()->play("coin_rotate");
		/*CCSprite* coin = CCSprite::createWithSpriteFrameName("coin_front.png");*/
		coin->setPosition(ccp(x, y));
		coinArray->addObject(coin);

		map->addChild(coin, 19);
	}
	//for (int i = 0; i < length; i++)
	//{
	//	sprintf(str, "coin_%i", i);
	//	CCDictionary* lightDic = objGroup->objectNamed(str);
	//	float x = lightDic->valueForKey("x")->floatValue();
	//	float y = lightDic->valueForKey("y")->floatValue();

	//	CCArmature* coin = CCArmature::create("coin");
	//	coin->getAnimation()->play("coin_rotate");
	//	/*CCSprite* coin = CCSprite::createWithSpriteFrameName("coin_front.png");*/
	//	coin->setPosition(ccp(x, y));
	//	coinArray->addObject(coin);
	//	
	//	map->addChild(coin, 19);
	//}
}

void FactoryScene::update(float dt){
	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (!maoChong)
	{
		return;
	}
	if (maoChong->getStatus() == HeroStatus::LEFT_FALL_DOWN ||
		maoChong->getStatus() == HeroStatus::RIGHT_FALL_DOWN)
	{
		return;
	}
	//// 飞行过程中不检测齿轮
	//if (maoChong->getStatus() != HeroStatus::LEFT_FLY &&
	//	maoChong->getStatus() != HeroStatus::RIGHT_FLY){
	//	// 齿轮检测
	//	for (unsigned int i = 0; i < roundArray->count(); i++){
	//		CCSprite* r = (CCSprite*)roundArray->objectAtIndex(i);
	//		/*CCLog("r: %f %f", r->getTextureRect().getMinX(), r->getTextureRect().getMinY());*/
	//		CCRect rect = CCRectMake(r->getPositionX() - 20 + r->getParent()->getPositionX(),
	//			r->getParent()->getPositionY() + r->getPositionY() - 20, 40, 40);

	//		if (rect.intersectsRect(maoChong->getCollideRect())){
	//			if (maoChong->getCurLine() % 2 == 0){
	//				maoChong->statusChangeTo(HeroStatus::LEFT_FALL_DOWN);
	//				return;
	//			}
	//			else {
	//				maoChong->statusChangeTo(HeroStatus::RIGHT_FALL_DOWN);
	//				return;
	//			}
	//		}
	//	}
	//}
	
	// 金币检测
	for (unsigned int i = 0; i < coinArray->count(); i++){
		CCArmature* coin = (CCArmature*)coinArray->objectAtIndex(i);
		// 
		CCRect coinRect = CCRectMake(-16 + coin->getPositionX() + coin->getParent()->getPositionX(), 
			-16 + coin->getPositionY() + coin->getParent()->getPositionY(),
			32, 32);
		
		if (coinRect.intersectsRect(maoChong->getCollideRect())){
			coinArray->removeObject(coin);
			coin->removeFromParent();
			coinNum++;
			refreshCoinNumLabel();
		}
	}
	//y是所处map编号
	int y = int(hero->getPositionY()) / int(2 * HEIGHT);
	if ( y > curMap){
		addRandomMap();
	}
}


bool FactoryScene::bindHeroToRope(Rope* rope){
	if (!rope || !this->hero)
	{
		return false;
	}
	CCPoint ropeP = rope->getPosition() + rope->getParent()->getPosition();
	CCPoint heroP = this->hero->getPosition();

	//CCLog("Hero loc: %f %f", ropeP.x, heroP.y);
	this->hero->setSimplePosition(ccp(ropeP.x, heroP.y));
	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (!maoChong)
	{
		return false;
	} 
	maoChong->setCurRope(rope);
	return true;
}

void FactoryScene::findRope(){
	MaoChong* maoChong = (MaoChong*)hero;
	CCLog("find rope");
	Rope* targetRope = NULL;
	// 检测碰到哪根绳子
	for (unsigned int i = 0; i < ropeArray->count(); i++){
		Rope* r = (Rope*)ropeArray->objectAtIndex(i);
		if (r->getCollideRect().intersectsRect(maoChong->getCollideRect()) && 
			r->getCollideRect().getMaxY() > maoChong->getCollideRect().getMaxY()){
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
	float minLength = 10000;
	// 检测应该回到最近的绳子
	for (unsigned int i = 0; i < ropeArray->count(); i++){
		Rope* r = (Rope*)ropeArray->objectAtIndex(i);
		if ( r->getCollideRect().getMaxY() < maoChong->getCollideRect().getMaxY()){
			continue;
		}
		float l = ccpDistance(r->getCollideRect().origin, maoChong->getCollideRect().origin);
		if (l < minLength){
			minLength = l;
			targetRope = r;
		}
	}
	return maoChong->getCurRope();
}

void FactoryScene::doSiPa()
{
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
			float x = targetRope->getPositionX();
			if (x == THREELINES[0])
			{
				((MaoChong*)hero)->setCurLine(1);
			}
			else if (x == THREELINES[1]){
				((MaoChong*)hero)->setCurLine(2);
			}
			else {
				((MaoChong*)hero)->setCurLine(4);
			}
			siNum--;
			this->refreshSiNumLabel();
			hero->statusChangeTo(HeroStatus::DISAPPEAR);
			scheduleOnce(schedule_selector(FactoryScene::backToRope), BACK_TIME);
		}
	}
}

void FactoryScene::backToRope(float dt){
	CCLog("back to rope");
	if (!this->targetRope){
		return;
	}
	
	float x = targetRope->getPositionX() + targetRope->getParent()->getPositionX();
	float y = targetRope->getPositionY() + targetRope->getParent()->getPositionY() - targetRope->getCurLength() / 2 - hero->getParent()->getPositionY();
	this->hero->setSimplePosition(ccp(x, y));
	this->hero->statusChangeTo(HeroStatus::APPEAR);
	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (!maoChong)
	{
		return;
	}
	maoChong->setCurRope(targetRope);

	scheduleOnce(schedule_selector(FactoryScene::setPa), BACK_TIME);
}

void FactoryScene::setPa(float dt){
	hero->statusChangeTo(HeroStatus::WAIT);
}

Rope* FactoryScene::getTargetRope(){
	return targetRope;
}

FactoryScene::~FactoryScene(){
	CCObject* o = NULL;
	CCARRAY_FOREACH(ropeArray, o){
		Rope* r = dynamic_cast<Rope*>(o);
		r->release();
	}
	CC_SAFE_DELETE(ropeArray);

	CC_SAFE_DELETE(roundArray);

	CC_SAFE_DELETE(coinArray);

	CC_SAFE_DELETE(mapArray);
}