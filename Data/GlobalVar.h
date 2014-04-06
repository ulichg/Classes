#pragma once

// BaseScene层，node tag设置
const int MAP_TAG = 10000; // in scene
const int HERO_TAG = 10001; // in map
const int CONTROLLER_TAG = 10002; // in map
const int SINUM_TAG = 10003; // in map

// 绳子配置信息
const float MAXLINE = 400;
const float MINLINE = 120;
const float RODE_WIDTH = 32;
const float SPEED = 0.8f;
const float THREELINES[3] = { 130, 323, 515 };

// 毛虫信息
const float TIME_HOR = 0.3f;
const float FALL_DOWN_SPEED = 5;
const int HERO_LEVEL = 10;
const int SI_START_NUM = (HERO_LEVEL / 2 + 1);
const float SI_LENGTH = 640;
const float BACK_TIME = 0.3f; // 毛虫掉落返回绳子时间