#pragma once

// BaseScene层，node tag设置
const int MAP_TAG = 10000; // in scene
const int HERO_TAG = 10001; // in map
const int CONTROLLER_TAG = 10002; // in map
const int SINUM_TAG = 10003; // in scene
const int COINNUM_TAG = 10004; // in scene
const int DIS_TAG = 10005; // in scene

// 绳子配置信息
const float MAXLINE = 400;
const float MINLINE = 120;

const float SPEED = 1;
const float THREELINES[3] = { 130, 323, 515 };
const float PNG_HEIGHT = 960;
const float PNG_WIDTH = 16;

// 蝴蝶信息
const float FLY_SPEED = 20.0f;

// 毛虫信息
const float TIME_HOR = 0.3f;
const float FALL_DOWN_SPEED = 5;
const int HERO_LEVEL = 10;
const int SI_START_NUM = ( HERO_LEVEL + 1);
const float SI_LENGTH = 640;
const float BACK_TIME = 0.2f; // 毛虫掉落返回绳子时间
const int START_LINE = 0; 

// 地图信息
const float WIDTH = 640;
const float HEIGHT = 960;
const float DOWN_LENGTH = HEIGHT / 2;
const int MAP_TYPE_NUM = 2;
const int MAP_CACHE = 3; // 地图缓存个数
const int SCORE_PER_DIS = 50; // 每SCORE_PER_DIS 算一分