#include "BaseScene.h"
#include "Data/GlobalVar.h"
#include "Person/MaoChong.h"
#include "CodeConvert.h"

bool BaseScene::init(){
	this->ropeArray = CCArray::create();
	this->roundArray = CCArray::create();
	this->coinArray = CCArray::create();
	this->mapArray = CCArray::create();
	setMap(NULL);
	return true;
}

CCScene* BaseScene::scene(){
	CCScene* mScene = CCScene::create();
	BaseScene* mLayer = BaseScene::create();
	mScene->addChild(mLayer);

	return mScene;
}

void BaseScene::setViewPoint(CCPoint c){
	CCObject* o = NULL;
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

void BaseScene::addMap(CCTMXTiledMap* map){

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