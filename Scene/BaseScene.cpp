#include "BaseScene.h"
#include "Data/GlobalVar.h"
#include "Person/MaoChong.h"
#include "CodeConvert.h"

bool BaseScene::init(){
	this->ropeArray = CCArray::create();
	setMap(NULL);
	return true;
}

CCScene* BaseScene::scene(){
	CCScene* mScene = CCScene::create();
	BaseScene* mLayer = BaseScene::create();
	mScene->addChild(mLayer);

	return mScene;
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

void BaseScene::refreshSiNumLabel(){
	CCLabelTTF* Label = (CCLabelTTF*)(this->getChildByTag(SINUM_TAG));
	char str[100];
	sprintf(str, "丝数：%i", hero->getSiNum());
	
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

CCArray* BaseScene::getRopeArray(){
	return ropeArray;
}