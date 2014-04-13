#include "BaseScene.h"
#include "Data/GlobalVar.h"
#include "Person/MaoChong.h"
#include "CodeConvert.h"

bool BaseScene::init(){
	return true;
}

void BaseScene::setViewPoint(CCPoint c){
	CCObject* o = NULL;
	thingLayer->setPosition(c);
	for (unsigned int i = 0; i < mapArray->count(); i++)
	{
		CCTMXTiledMap* m = dynamic_cast<CCTMXTiledMap*>( mapArray->objectAtIndex(i));
		if (!m){
			CCLog("map NULL");
			return;
		}
		m->setPosition(ccp(c.x, c.y + i * HEIGHT * 2));
	}
}

void BaseScene::addMap(CCTMXTiledMap* map){

}

void BaseScene::setMap(CCTMXTiledMap* map){
	if (!map){
		return;
	}
	if (this->getChildByTag(MAP_TAG)){
		this->removeChildByTag(MAP_TAG);
	}
	this->map = map;
	this->addChild(this->map, -1, MAP_TAG);
}

void BaseScene::removeMap(CCTMXTiledMap* map){
	if (!map){
		return;
	}
	map->removeFromParent();
	CCObject* o = NULL;
	CCARRAY_FOREACH(map->getChildren(), o){
		ropeArray->removeObject(o);
		roundArray->removeObject(o);
	}
}

void BaseScene::addRandomMap(){
	curMap++;
	CCLog("add a new map");
	int x = rand() % MAP_TYPE_NUM;
	char str[100];
	sprintf(str, "map/testMap_%i.tmx", x);
	CCTMXTiledMap* map = CCTMXTiledMap::create(str);
	addMap(map);
}

void BaseScene::refreshSiNumLabel(){
	CCLabelTTF* Label = (CCLabelTTF*)(this->getChildByTag(SINUM_TAG));
	char str[100];
	sprintf(str, "丝数：%i", siNum);
	
	if (!Label){
		Label = CCLabelTTF::create(UTEXT(str), "Arial", 50);
		this->addChild(Label, 20, SINUM_TAG);
	}
	else {
		Label->setString(UTEXT(str));
	}

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSize lSize = Label->getContentSize();
	float x = lSize.width / 3 * 2;
	float y = winsize.height - lSize.height / 3 * 2;
	Label->setPosition(ccp(x, y));
}

void BaseScene::refreshCoinNumLabel(){
	CCLabelTTF* Label = (CCLabelTTF*)(this->getChildByTag(COINNUM_TAG));
	char str[100];
	sprintf(str, "金币：%i", coinNum);

	if (!Label){
		Label = CCLabelTTF::create(UTEXT(str), "Arial", 50);
		this->addChild(Label, 20, COINNUM_TAG);
	}
	else {
		Label->setString(UTEXT(str));
	}

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSize lSize = Label->getContentSize();
	float x = winsize.width / 3 * 2;
	float y = winsize.height - lSize.height / 3 * 2;
	Label->setPosition(ccp(x, y));
}

CCArray* BaseScene::getRopeArray(){
	return ropeArray;
}