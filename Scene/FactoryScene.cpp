#include "FactoryScene.h"

bool FactoryScene::init(){
	this->ropeArray = CCArray::create();

	CCTMXTiledMap* map = CCTMXTiledMap::create("map/testMap.tmx");
	setMap(map);
	initHero();
	setMapThings();
	return true;
}

void FactoryScene::initHero(){
	MaoChong* maoChong = MaoChong::createWithTiledMap(map);
	maoChong->statusChangeTo(HeroStatus::PA);
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
		
		CCSprite* roundSprite = CCSprite::create("map/round.png");
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
}

bool FactoryScene::bindHeroToRope(Rope* rope){
	if (!rope || !this->hero)
	{
		return false;
	}
	CCPoint ropeP = rope->getPosition();
	CCPoint heroP = hero->getPosition();

	CCLog("Hero loc: %f %f", ropeP.x, heroP.y);
	hero->setPosition(ropeP.x, heroP.y);
	return true;
}