#pragma once

class HeroStatus
{
public:
	static const int LEFT_PA = 0;
	static const int RIGHT_PA = 1;
	static const int LEFT_FLY = 2;
	static const int RIGHT_FLY = 3;
	static const int LEFT_FALL_DOWN = 4;
	static const int RIGHT_FALL_DOWN = 5;
	static const int BUTTERFLY = 6;
	static const int DISAPPEAR = 7;
	static const int DIE = 8;
	static const int APPEAR = 9;
	static const int WAIT = 10;

	static CCString* getName(int i){
		CCString* s = CCString::create("");
		switch (i)
		{
		case LEFT_PA:
			s->m_sString = "LEFT_PA";
			break;
		case RIGHT_PA:
			s->m_sString = "RIGHT_PA";
			break;
		case LEFT_FLY:
			s->m_sString = "LEFT_FLY";
			break;
		case RIGHT_FLY:
			s->m_sString = "RIGHT_FLY";
			break;
		case LEFT_FALL_DOWN:
			s->m_sString = "LEFT_FALL_DOWN";
			break;
		case RIGHT_FALL_DOWN:
			s->m_sString = "RIGHT_FALL_DOWN";
			break;
		case BUTTERFLY:
			s->m_sString = "BUTTERFLY";
			break;
		case DISAPPEAR:
			s->m_sString = "DISAPPEAR";
			break;
		case DIE:
			s->m_sString = "DIE";
			break;
		case APPEAR:
			s->m_sString = "APPEAR";
			break;
		case WAIT:
			s->m_sString = "WAIT";
			break;
		default:
			break;
		}
		return s;
	}

};
