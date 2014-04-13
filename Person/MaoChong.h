#pragma once
#include "Hero.h"
#include "Controller/DirectController.h"
#include "Scene/Rope.h"

class FactoryScene;

using namespace cocos2d;
using namespace cocos2d::extension;

class MaoChong :
	public Hero
{
public:
	// ����״̬��������Ϸ�����еĿ������Լ�����֡
	virtual void statusChangeTo(int mStatus);

	// ���ý�ɫ״̬
	void setStatus(int mStatus);
	bool initWithTileMap(CCTMXTiledMap* map);

	virtual void setSimplePosition(CCPoint c);
	static MaoChong* createWithTiledMap(CCTMXTiledMap* map);
	int getCurLine();
	void setCurLine(int c);
	void moveFinishedCallFunc();

	/* ���ë����ײ���� */
	CCRect getCollideRect();
	Rope* getCurRope();
	void setCurRope(Rope* r);
private:
	// ���ö�Ӧ״̬��animation
	void runStatusAnimation();
	// ��ǰ������ ������������Ϊ��0 - 5
	int curLine;
	/*������������,���������ٶȣ�directcontroller*/
	Rope* curRope;
};

