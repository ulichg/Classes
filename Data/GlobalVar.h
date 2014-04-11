#pragma once

// BaseScene�㣬node tag����
const int MAP_TAG = 10000; // in scene
const int HERO_TAG = 10001; // in map
const int CONTROLLER_TAG = 10002; // in map
const int SINUM_TAG = 10003; // in map
const int COINNUM_TAG = 10004; // in map

// ����������Ϣ
const float MAXLINE = 400;
const float MINLINE = 120;

const float SPEED = 0.6f;
const float THREELINES[3] = { 130, 323, 515 };
const float PNG_HEIGHT = 960;
const float PNG_WIDTH = 16;

// ë����Ϣ
const float TIME_HOR = 0.3f;
const float FALL_DOWN_SPEED = 5;
const int HERO_LEVEL = 10;
const int SI_START_NUM = (HERO_LEVEL / 2 + 1);
const float SI_LENGTH = 640;
const float BACK_TIME = 0.2f; // ë����䷵������ʱ��

const float WIDTH = 640;
const float HEIGHT = 960;
