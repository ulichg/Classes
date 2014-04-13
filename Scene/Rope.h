#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Rope : public CCNode
{
public:
	Rope(bool isDown, float minLength, float maxLength);
	// ������ӵ���ײ����
	CCRect getCollideRect();
	// ���Ӿ�Ч��ʵ��
	void rollAction();
	// ��������Ч��
	void update(float delta);
	// ������ʾ
	void setShowLength();
	// ������ӳ���
	float getCurLength();
	// �Ƿ�����
	bool is_Down();
	/*���ʵ��λ��*/
	CCPoint getRealPosition();
protected:
	CCSprite* mSprite;
	// ��ǰ�˶������Ƿ�����
	bool isDown;
	// ��ǰ����
	float curLength;
	float minLength;
	float maxLength;
};